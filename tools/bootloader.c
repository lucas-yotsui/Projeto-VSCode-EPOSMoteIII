#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <source/sys_ctrl.h>
#include <source/flash.h>

//*****************************************************************************
//
// Implementations of function that are required by usb framework.
//
//*****************************************************************************
void usbsuspHookEnteringSuspend(bool remoteWakeupAllowed) {
    if (remoteWakeupAllowed) {
    }
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

bool recordProgram(void) {
    // Flag for flash operations results
    uint8_t successFlag; 
    // Counter for number of tries of a specific operation
    uint8_t tries = 0; 
    // Array to store program data fetched from USB
    char data[16];
    
    // USB message to start recording process
    // TODO: Implement USB start recording message

    // Record on a page of the flash
    for (uint16_t currentPage = 0; currentPage < NUMBER_OF_FLASH_PAGES; currentPage++) {
        // Zero tries of the erasing operation were made
        tries = 0;
        do {
            // Erase the current flash block
            successFlag = FlashMainPageErase(PAGE_AS_ADDRESS(currentPage));

            // If it has tried to erase this block 10 times and it still hasn't worked
            if(++tries == 10 && successFlag != 0) {
                // Send a message to USB to signal failure
                // TODO: Implement USB fail message
                
                // Signal to the function caller that the process was faulty
                return false;
            }

            // If erasing operation wasn't successful, try it again 
        } while(successFlag != 0);

        // Program a page in chunks
        for(uint16_t i = 0; i < PAGE_SIZE; i+= sizeof(data)) {
            // Zero tries of the recording operation were made
            tries = 0;
            // Fetch a program chunk from USB
            // TODO: Implement USB fetch
            // *data = ...

            do {
                // Record the new chunk of data
                successFlag = FlashMainPageProgram((uint32_t* )data, PAGE_AS_ADDRESS(currentPage) + i, sizeof(data));
                
                // If it has tried to record this chunk 10 times and it still hasn't worked
                if(++tries == 10 && successFlag != 0) {
                    // Send a message to USB to signal failure
                    // TODO: Implement USB fail message
                    
                    // Signal to the function caller that the process was faulty
                    return false;
                }

                // If recording operation wasn't successful, try it again 
            } while(successFlag != 0);
            
            // Send a message that this chunk of the program was recorded
            // TODO: Implement USB chunk recording success message
        }
    }

    // Send a USB message to signal success
    // TODO: Implement USB process success message
    
    // Signal to the function caller that the process was successful
    return true;
}

void bootloader(void) {
    // Counter for number of tries of the whole process
    uint8_t processTries = 0; 

    // Keep attempting to record the new program
    while (!recordProgram()) {
        // If it has tried to do this process 10 times and it still hasn't worked
        if(++processTries == 10) {
            // Send a USB message to signal that the programming operation was faulty
            // TODO: Implement USB programming failure message
        }
    }
    
    // Restart the Mote to start the new program
    SysCtrlReset(); 
}

void waitForBootloader(void) {
    // Set the clocking to run directly from the external crystal/oscillator.
    // (no ext 32k osc, no internal osc)
    SysCtrlClockSet(false, false, SYS_CTRL_SYSDIV_32MHZ);

    // Set IO clock to the same as system clock
    SysCtrlIOClockSet(SYS_CTRL_SYSDIV_32MHZ);

    // Initialize USB interface
    // TODO: Implement USB initial configuration

    // Flag for handshake detection
    bool usbHandshake = false; 

    // Wait for a couple seconds for a handshake
    for(uint32_t i = 0; i < 4000000; i++) {
        // Look for a handshake on the USB interface
        // TODO: Implement USB look for handshake
        // usbHandshake = ...

        // If usb handshake happens
        if(usbHandshake) {
            // Start bootloader
            bootloader();
        }
    }
}