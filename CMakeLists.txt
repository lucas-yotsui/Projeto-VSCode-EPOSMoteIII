  # ------------------------------------------------------------ #
#                                                              #
#   Este arquivo configura o seu projeto da forma necessária   #
#              para funcionar com o EposMoteIII.               #
#                                                              #
#    Alterar este arquivo incorretamente quebrará o projeto    #
#         Faça-o somente se souber o que está fazendo!         #
#                                                              #
# ------------------------------------------------------------ #

set(CMAKE_TOOLCHAIN_FILE "cmake/arm-none-eabi-toolchain.cmake")

cmake_minimum_required(VERSION 3.20)
project(projeto)

set(CMAKE_MAKE_PROGRAM mingw32-make)
# Path to Driverlib
set(DRIVER_LIBRARY_PATH "C:/ti/cc2538/driverlib/cc2538")
# Path to USBlib
set(USB_LIBRARY_PATH "C:/ti/cc2538/usblib/cc2538/source")

# Project source files
file(GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/source/*.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/source/*.c
    ${CMAKE_CURRENT_LIST_DIR}/app/*.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/app/*.c
    ${CMAKE_CURRENT_LIST_DIR}/tools/bootloader.c
  )

# Project header files
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/*.h)

# Set include folder as one of the include directories used by compiler
include_directories(BEFORE ${CMAKE_CURRENT_LIST_DIR}/include)

# Set Linker script to be used
set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/tools/linker.ld)

# Add the project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include the Driverlib and USBlib C SDK
target_include_directories(${PROJECT_NAME} PUBLIC ${DRIVER_LIBRARY_PATH} ${USB_LIBRARY_PATH})

# Platform specific flags
target_compile_options(${PROJECT_NAME} PRIVATE 
	-mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 
	-mfloat-abi=hard -ffunction-sections -fdata-sections
	-Wall -Wextra -pedantic -MD -fno-exceptions -fno-rtti
)

# Find the compiler specific libraries
get_target_property(COMPILE_FLAGS ${PROJECT_NAME} COMPILE_OPTIONS)
execute_process(COMMAND ${CMAKE_C_COMPILER} ${COMPILE_FLAGS} -print-libgcc-file-name OUTPUT_VARIABLE LIBGCC_PATH)
execute_process(COMMAND ${CMAKE_C_COMPILER} ${COMPILE_FLAGS} -print-file-name=libc.a OUTPUT_VARIABLE LIBC_PATH)
execute_process(COMMAND ${CMAKE_C_COMPILER} ${COMPILE_FLAGS} -print-file-name=libm.a OUTPUT_VARIABLE LIBM_PATH)
execute_process(COMMAND ${CMAKE_C_COMPILER} ${COMPILE_FLAGS} -print-file-name=libstdc++.a OUTPUT_VARIABLE LIBSTDCPP_PATH)
string(STRIP "${LIBGCC_PATH}" LIBGCC_PATH)
string(STRIP "${LIBSTDCPP_PATH}" LIBSTDCPP_PATH)
string(STRIP "${LIBC_PATH}" LIBC_PATH)
string(STRIP "${LIBM_PATH}" LIBM_PATH)

# Platform specific link definitions
target_link_options(${PROJECT_NAME} PRIVATE
  -T ${LINKER_SCRIPT} --entry ResetISR --gc-sections
)

# Include other libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
  ${DRIVER_LIBRARY_PATH}/bin/gcc/driverlib.lib
  ${LIBM_PATH}
  ${LIBC_PATH}
  ${LIBGCC_PATH}
  ${LIBSTDCPP_PATH}
)

# Objcopy to create a binary file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND 
  ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}>.axf
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin
)

# Custom target to perform a flash operation
add_custom_target(flash
  COMMAND  # Insert new command when flash program is ready
)

# Flash command depends on a successful build
add_dependencies(flash ${PROJECT_NAME})

# Enable C++20 and C17
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)