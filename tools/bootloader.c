#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "gpio.h"
#include "class_cdc/usb_cdc.h"
#include "library/usb_firmware_library_headers.h"
#include "library/usb_in_buffer.h"
#include "library/usb_out_buffer.h"

/**
 * @brief Initializes the USB interface
*/
void prepareBootloader(void) {
    //******************** Initialize USB interface ********************//
    // Initialize the USB library
    usbfwInit();

    // Activate the USB D+ pull-up resistor
    //! In the usblib provided by TI, they set the PC0 pin as the pull-up resistor, but 
    //! the schematic for EPOSMoteIII shows the D+ line connected to PC2
    GPIODirModeSet(GPIO_C_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIO_C_BASE, GPIO_PIN_2, GPIO_PIN_2);
}