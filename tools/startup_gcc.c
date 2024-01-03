#include <stdint.h>
#include "eposInterrupts.h" 

#define FLASH_START_ADDR            0x00200000  //* Flash start address *//
#define FLASH_IMAGE_VALID           0x00000000  //* Identifies that the image in flash is valid *//
#define BOOTLOADER_BACKDOOR_ENABLE  0xFFFFFFF9  //* Enables the Bootloader Backdoor on GPIOA1 *//

#define SRAM_START  0x20000000                  //* SRAM starting location *//
#define SRAM_LENGTH (16 * 1024)                 //* 16 kB *//
#define STACK_START (SRAM_START + SRAM_LENGTH)  //* Stack starts right after SRAM ends *//

#define HWREG(x) (*((volatile uint32_t *)(x)))  //* Macro for direct register access *//
#define SYS_CTRL_I_MAP  0x400D2098              //* Register that selects whether to use regular or alternate interrupt map *//
#define ALTERNATE_I_MAP 0x00000001              //* Value to write on SYS_CTRL_I_MAP to select alternate interrupt map *//

//*****************************************************************************
//
// Customer Configuration Area in Lock Page
// Holds Image Vector table address (bytes 2012 - 2015) and
// Image Valid bytes (bytes 2008 -2011)
//
//*****************************************************************************
typedef struct {
	uint32_t bootloaderCfg;
    uint32_t imageValid;
    uint32_t vectorAddr;
} lockPageCCA_t;

__attribute__((section(".flashcca")))
lockPageCCA_t __cca =
{
  BOOTLOADER_BACKDOOR_ENABLE,   // Bootloader backdoor enabled in PA7
  FLASH_IMAGE_VALID,            // Image valid bytes
  FLASH_START_ADDR 		    	// Vector table located at flash start address
};


void resetHandler(void);
extern void bootloader(void);

//*****************************************************************************
// Reserve space for the system stack.
//*****************************************************************************
uint32_t __STACK_TOP;

__attribute__ ((section(".vectors"), used))
void (* const vectors[])(void) =
{
   (void (*)(void))STACK_START,     // 0 Stack pointer
   resetHandler,                    // 1 Reset handler
   NMI_handler,                     // 2 The NMI handler
   hard_fault_handler,              // 3 The hard fault handler
   mem_manage_fault_handler,        // 4 The MPU fault handler
   bus_fault_handler,               // 5 The bus fault handler
   usage_fault_handler,             // 6 The usage fault handler
   0,                               // 7 Reserved
   0,                               // 8 Reserved
   0,                               // 9 Reserved
   0,                               // 10 Reserved
   sv_call_handler,                 // 11 SVCall handler
   debug_monitor_handler,           // 12 Debug monitor handler
   0,                               // 13 Reserved
   pend_sv_call_handler,            // 14 The PendSV handler
   systick_handler,                 // 15 The SysTick handler
   GPIOA_handler,                   // 16 GPIO Port A
   GPIOB_handler,                   // 17 GPIO Port B
   GPIOC_handler,                   // 18 GPIO Port C
   GPIOD_handler,                   // 19 GPIO Port D
   0,                               // 20 none
   UART0_handler,                   // 21 UART0 Rx and Tx
   UART1_handler,                   // 22 UART1 Rx and Tx
   SSI0_handler,                    // 23 SSI0 Rx and Tx
   I2C_handler,                     // 24 I2C Master and Slave
   0,                               // 25 Reserved
   0,                               // 26 Reserved
   0,                               // 27 Reserved
   0,                               // 28 Reserved
   0,                               // 29 Reserved
   ADC_handler,                     // 30 ADC Sequence 0
   0,                               // 31 Reserved
   0,                               // 32 Reserved
   0,                               // 33 Reserved
   watchdog_handler,                // 34 Watchdog timer, timer 0
   timer0A_handler,                 // 35 Timer 0 subtimer A
   timer0B_handler,                 // 36 Timer 0 subtimer B
   timer1A_handler,                 // 37 Timer 1 subtimer A
   timer1B_handler,                 // 38 Timer 1 subtimer B
   timer2A_handler,                 // 39 Timer 2 subtimer A
   timer2B_handler,                 // 40 Timer 2 subtimer B
   analog_comparator_handler,       // 41 Analog Comparator 0
   RF_Core_Rx_Tx_handler,           // 42 RFCore Rx/Tx
   RF_Core_error_handler,           // 43 RFCore Error
   system_control_handler,          // 44 IcePick
   flash_control_handler,           // 45 FLASH Control
   AES_handler,                     // 46 AES
   PKA_handler,                     // 47 PKA
   sleep_timer_handler,             // 48 Sleep Timer
   MAC_timer_handler,               // 49 MacTimer
   SSI1_handler,                    // 50 SSI1 Rx and Tx
   timer3A_handler,                 // 51 Timer 3 subtimer A
   timer3B_handler,                 // 52 Timer 3 subtimer B
   0,                               // 53 Reserved
   0,                               // 54 Reserved
   0,                               // 55 Reserved
   0,                               // 56 Reserved
   0,                               // 57 Reserved
   0,                               // 58 Reserved
   0,                               // 59 Reserved
   //! * ------------------------------------------------- * !//
   //! |  PRESTA MUITA ATENÇÃO, NÃO MEXE NESSA INTERRUPÇÃO | !//
   //! |       AQUI OU O BOOTLOADER N FUNCIONA MAIS        | !//
   //! * ------------------------------------------------- * !//
   bootloader,                      // 60 USB 2538
   //* * ------------------------------------------------- * *//
   //* |      A partir daqui pode mexer como quiser...     | *//
   //* * ------------------------------------------------- * *//
   0,                               // 61 Reserved
   uDMA_handler,                    // 62 uDMA
   uDMA_error_handler,              // 63 uDMA Error
};

extern int main(void);
extern void prepareBootloader(void);

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void resetHandler (void) {
	uint32_t *source, *destination;

	// Copy the data segment initializers from flash to SRAM.
	source = &_etext;
	for(destination = &_sdata; destination < &_edata; ) {
		*destination++ = *source++;
	}

	// Zero fill the bss segment.

    for(destination = &_sbss; destination < &_ebss; ) {
        *destination++ = 0;
    }

    // Enable alternate interrupt mapping
    HWREG(SYS_CTRL_I_MAP) = ALTERNATE_I_MAP;

   // Initialize usb interface for bootloader
   // prepareBootloader();
          
   // Call the application's entry point.
   main();

   // End here if return from main()
   while(1);
}