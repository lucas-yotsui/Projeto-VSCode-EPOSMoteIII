# ------------------------------------------------------------ #
#                                                              #
#   Este arquivo contém as configurações necessárias do CMake  #
#       para configurar o seu projeto da forma necessária      #
#                   para funcionar com o Tiva.                 #
#                                                              #
#    Alterar este arquivo incorretamente quebrará o projeto    #
#         Faça-o somente se souber o que está fazendo!         #
#                                                              #
# ------------------------------------------------------------ #

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_C_LINK_EXECUTABLE "arm-none-eabi-ld <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET>.axf <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "arm-none-eabi-ld <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET>.axf <LINK_LIBRARIES>")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)