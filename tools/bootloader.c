#include <stdbool.h>
#include <string.h>
#include "hw_memmap.h"
#include "sys_ctrl.h"
#include "flash.h"
#include "class_cdc/usb_cdc.h"
#include "library/usb_firmware_library_headers.h"
#include "library/usb_in_buffer.h"
#include "library/usb_out_buffer.h"

#define MESSAGE_SUCCESS 0

//*****************************************************************************
//
// Implementations of function that are required by usb framework.
//
//*****************************************************************************
void usbsuspHookEnteringSuspend(bool remoteWakeupAllowed) {
    if (remoteWakeupAllowed) {}
}


void usbsuspHookExitingSuspend(void) {

}
//*****************************************************************************
//
// End of implementations of functions that are required by usb framework.
//
//*****************************************************************************

#define PAGE_SIZE               2048
#define PAGE_AS_ADDRESS(page)   (FLASH_BASE + (page * PAGE_SIZE))
#define NUMBER_OF_FLASH_PAGES   256


USB_EPIN_RINGBUFFER_DATA usbCdcInBufferData;
USB_EPOUT_RINGBUFFER_DATA usbCdcOutBufferData;
static uint8_t inBuffer[128];
static uint8_t outBuffer[128];
static uint8_t data[128];

/**
 * @brief Send a message through serial communication.
*/
void sendUsbMessage(char* message) {
    // Variable to store number of free bytes
    uint16_t count;

    // Get maximum number of bytes that can be written with usbibufPush
    count = usbibufGetMaxPushCount(&usbCdcInBufferData);

    // Push data to the buffer
    usbibufPush(&usbCdcInBufferData, (uint8_t* )message, count);
    
    // Send bytes to the connected USB
    usbCdcProcessEvents();
}

/**
 * @brief Receive a message through serial communication.
*/
void receiveUsbMessage() {
    // Variable to store number of free bytes
    uint16_t count;

    // Receive bytes from the connected USB
    usbCdcProcessEvents();
    
    // Get number of bytes on the buffer
    count = usbobufGetMaxPopCount(&usbCdcOutBufferData);

    // Pull data from the buffer
    usbobufPop(&usbCdcOutBufferData, data, count);
}

/**
 * @brief Record a new program on the Mote's flash memory.
*/
bool recordProgram(void) {
    // Flag for flash operations results
    int32_t successFlag; 
    // Counter for number of tries of a specific operation
    uint8_t tries = 0;

    //************************** Program a page of the flash **************************//
    for (uint16_t currentPage = 0; currentPage < NUMBER_OF_FLASH_PAGES; currentPage++) {
        // Zero tries of the erasing operation were made
        tries = 0;
        do {
            //** Erase the current flash block **//
            successFlag = FlashMainPageErase(PAGE_AS_ADDRESS(currentPage));

            // If it has tried to erase this block 10 times and it still hasn't worked
            if(++tries == 10 && successFlag != MESSAGE_SUCCESS) {
                // Send a message to USB to signal failure
                sendUsbMessage("Failure on programming operation!");
                
                // Signal to the function caller that the process was faulty
                return false;
            }

            // If erasing operation wasn't successful, try it again 
        } while(successFlag != MESSAGE_SUCCESS);

        //**************************** Record on the page ****************************//
        // Zero tries of the recording operation were made
        tries = 0;
        // Ask for the current page's data
        sendUsbMessage("Send page");
        // Receive the current page's data
        receiveUsbMessage();

        do {
            // Record the new chunk of data
            successFlag = FlashMainPageProgram((uint32_t* )data, PAGE_AS_ADDRESS(currentPage), PAGE_SIZE);
            
            // If it has tried to record this chunk 10 times and it still hasn't worked
            if(++tries == 10 && successFlag != MESSAGE_SUCCESS) {
                // Send a message to USB to signal failure
                sendUsbMessage("Failure on programming operation!");
                
                // Signal to the function caller that the process was faulty
                return false;
            }

            // If recording operation wasn't successful, try it again 
        } while(successFlag != MESSAGE_SUCCESS);
        
        // Send a message that this page's content was recorded
        sendUsbMessage("Page recorded successfully!");
    }

    // Send a USB message to signal success
    sendUsbMessage("Program recorded successfully!");
    
    // Signal to the function caller that the process was successful
    return true;
}

/**
 * @brief Shell function that calls the function responsible for actually recording the program
*/
void bootloader(void) {
    // Counter for number of tries of the whole process
    uint8_t processTries = 0; 

    // Keep attempting to record the new program
    while (!recordProgram()) {
        // If it has tried to do this process 10 times and it still hasn't worked
        if(++processTries == 10) {
            // Send a USB message to signal that the programming operation was faulty
            sendUsbMessage("Panic! Reset all!");
        }
    }
    
    // Restart the Mote to start the new program
    SysCtrlReset(); 
}

/**
 * @brief Initializes the USB interface as a CDC device to emulate serial communication
*/
void prepareBootloader(void) {
    //******************** Initialize USB interface ********************//

    // Initialize USB data buffers
    memset(&usbCdcInBufferData, 0x00, sizeof(USB_EPIN_RINGBUFFER_DATA));
    usbCdcInBufferData.pBuffer = inBuffer;
    usbCdcInBufferData.size = sizeof(inBuffer);
    usbCdcInBufferData.endpointReg = USB_F4;
    usbCdcInBufferData.endpointIndex = 4;
    usbCdcInBufferData.endpointSize = 64;
    memset(&usbCdcOutBufferData, 0x00, sizeof(USB_EPOUT_RINGBUFFER_DATA));
    usbCdcOutBufferData.pBuffer = outBuffer;
    usbCdcOutBufferData.size = sizeof(outBuffer);
    usbCdcOutBufferData.endpointReg = USB_F4;
    usbCdcOutBufferData.endpointIndex = 4;

    // Initialize COM port emulation at 115200
    usbCdcInit(115200);
}