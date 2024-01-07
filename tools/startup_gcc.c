#include <stdint.h>
#include "eposInterrupts.h" 

#define FLASH_START_ADDR            0x00200000  //* Flash start address *//
#define FLASH_IMAGE_VALID           0x00000000  //* Identifies that the image in flash is valid *//
#define BOOTLOADER_BACKDOOR_DISABLE 0xEFFFFFFF  //* Disables the Bootloader Backdoor *//

#define STACK_TOP                   0x20008000

void reset_handler(void);

__attribute__ ((section(".vectors"), used))
void (* const vectors[])(void) = {
   (void (*)(void))STACK_TOP,                               // 0 Stack pointer
   reset_handler,                                           // 1 Reset handler
   NMI_handler,                                             // 2 The NMI handler
   hard_fault_handler,                                      // 3 The hard fault handler
   mem_manage_fault_handler,                                // 4 The MPU fault handler
   bus_fault_handler,                                       // 5 The bus fault handler
   usage_fault_handler,                                     // 6 The usage fault handler
   0,                                                       // 7 Reserved
   0,                                                       // 8 Reserved
   0,                                                       // 9 Reserved
   0,                                                       // 10 Reserved
   sv_call_handler,                                         // 11 SVCall handler
   debug_monitor_handler,                                   // 12 Debug monitor handler
   0,                                                       // 13 Reserved
   pend_sv_call_handler,                                    // 14 The PendSV handler
   systick_handler,                                         // 15 The SysTick handler
   GPIOA_handler,                                           // 16 GPIO Port A
   GPIOB_handler,                                           // 17 GPIO Port B
   GPIOC_handler,                                           // 18 GPIO Port C
   GPIOD_handler,                                           // 19 GPIO Port D
   0,                                                       // 20 none
   UART0_handler,                                           // 21 UART0 Rx and Tx
   UART1_handler,                                           // 22 UART1 Rx and Tx
   SSI0_handler,                                            // 23 SSI0 Rx and Tx
   I2C_handler,                                             // 24 I2C Master and Slave
   0,                                                       // 25 Reserved
   0,                                                       // 26 Reserved
   0,                                                       // 27 Reserved
   0,                                                       // 28 Reserved
   0,                                                       // 29 Reserved
   ADC_handler,                                             // 30 ADC Sequence 0
   0,                                                       // 31 Reserved
   0,                                                       // 32 Reserved
   0,                                                       // 33 Reserved
   watchdog_handler,                                        // 34 Watchdog timer 
   timer0A_handler,                                         // 35 Timer 0 subtimer A
   timer0B_handler,                                         // 36 Timer 0 subtimer B
   timer1A_handler,                                         // 37 Timer 1 subtimer A
   timer1B_handler,                                         // 38 Timer 1 subtimer B
   timer2A_handler,                                         // 39 Timer 2 subtimer A
   timer2B_handler,                                         // 40 Timer 2 subtimer B
   analog_comparator_handler,                               // 41 Analog Comparator 0
   RF_Core_Rx_Tx_handler,                                   // 42 RFCore Rx/Tx (Alternate)
   RF_Core_error_handler,                                   // 43 RFCore Error (Alternate)
   system_control_handler,                                  // 44 IcePick
   flash_control_handler,                                   // 45 FLASH Control
   AES_handler,                                             // 46 AES (Alternate)
   PKA_handler,                                             // 47 PKA (Alternate)
   sleep_timer_handler,                                     // 48 Sleep Timer (Alternate)
   MAC_timer_handler,                                       // 49 MacTimer (Alternate)
   SSI1_handler,                                            // 50 SSI1 Rx and Tx
   timer3A_handler,                                         // 51 Timer 3 subtimer A
   timer3B_handler,                                         // 52 Timer 3 subtimer B
   0,                                                       // 53 Reserved
   0,                                                       // 54 Reserved
   0,                                                       // 55 Reserved
   0,                                                       // 56 Reserved
   0,                                                       // 57 Reserved
   0,                                                       // 58 Reserved
   0,                                                       // 59 Reserved
   0,                                                       // 60 Reserved
   0,                                                       // 61 Reserved
   uDMA_handler,                                            // 62 uDMA
   uDMA_error_handler,                                      // 63 uDMA Error
   0,                                                       // 64 Unused
   0,                                                       // 65 Unused
   0,                                                       // 66 Unused
   0,                                                       // 67 Unused
   0,                                                       // 68 Unused
   0,                                                       // 69 Unused
   0,                                                       // 70 Unused
   0,                                                       // 71 Unused
   0,                                                       // 72 Unused
   0,                                                       // 73 Unused
   0,                                                       // 74 Unused
   0,                                                       // 75 Unused
   0,                                                       // 76 Unused
   0,                                                       // 77 Unused
   0,                                                       // 78 Unused
   0,                                                       // 79 Unused
   0,                                                       // 80 Unused
   0,                                                       // 81 Unused
   0,                                                       // 82 Unused
   0,                                                       // 83 Unused
   0,                                                       // 84 Unused
   0,                                                       // 85 Unused
   0,                                                       // 86 Unused
   0,                                                       // 87 Unused
   0,                                                       // 88 Unused
   0,                                                       // 89 Unused
   0,                                                       // 90 Unused
   0,                                                       // 91 Unused
   0,                                                       // 92 Unused
   0,                                                       // 93 Unused
   0,                                                       // 94 Unused
   0,                                                       // 95 Unused
   0,                                                       // 96 Unused
   0,                                                       // 97 Unused
   0,                                                       // 98 Unused
   0,                                                       // 99 Unused
   0,                                                       // 100 Unused
   0,                                                       // 101 Unused
   0,                                                       // 102 Unused
   0,                                                       // 103 Unused
   0,                                                       // 104 Unused
   0,                                                       // 105 Unused
   0,                                                       // 106 Unused
   0,                                                       // 107 Unused
   0,                                                       // 108 Unused
   0,                                                       // 109 Unused
   0,                                                       // 110 Unused
   0,                                                       // 111 Unused
   0,                                                       // 112 Unused
   0,                                                       // 113 Unused
   0,                                                       // 114 Unused
   0,                                                       // 115 Unused
   0,                                                       // 116 Unused
   0,                                                       // 117 Unused
   0,                                                       // 118 Unused
   0,                                                       // 119 Unused
   0,                                                       // 120 Unused
   0,                                                       // 121 Unused
   0,                                                       // 122 Unused
   0,                                                       // 123 Unused
   0,                                                       // 124 Unused
   0,                                                       // 125 Unused
   0,                                                       // 126 Unused
   0,                                                       // 127 Unused
   0,                                                       // 128 Unused
   0,                                                       // 129 Unused
   0,                                                       // 130 Unused
   0,                                                       // 131 Unused
   0,                                                       // 132 Unused
   0,                                                       // 133 Unused
   0,                                                       // 134 Unused
   0,                                                       // 135 Unused
   0,                                                       // 136 Unused
   0,                                                       // 137 Unused
   0,                                                       // 138 Unused
   0,                                                       // 139 Unused
   0,                                                       // 140 Unused
   0,                                                       // 141 Unused
   0,                                                       // 142 Unused
   0,                                                       // 143 Unused
   0,                                                       // 144 Unused
   0,                                                       // 145 Unused
   0,                                                       // 146 Unused
   0,                                                       // 147 Unused
   0,                                                       // 148 Unused
   0,                                                       // 149 Unused
   0,                                                       // 150 Unused
   0,                                                       // 151 Unused
   0,                                                       // 152 Unused
   0,                                                       // 153 Unused
   0,                                                       // 154 Unused
   0,                                                       // 155 Unused
   //! * ------------------------------------------------- * !//
   //! |  PRESTA MUITA ATENÇÃO, NÃO MEXE NESSA INTERRUPÇÃO | !//
   //! |       AQUI OU O BOOTLOADER N FUNCIONA MAIS        | !//
   //! * ------------------------------------------------- * !//
   USB_handler,                                              // 156 USB 2538
   //* * ------------------------------------------------- * *//
   //* |      A partir daqui pode mexer como quiser...     | *//
   //* * ------------------------------------------------- * *//
   RF_Core_Rx_Tx_handler,                                   // 157 RFCore Rx/Tx
   RF_Core_error_handler,                                   // 158 RFCore Error
   AES_handler,                                             // 159 AES
   PKA_handler,                                             // 160 PKA
   sleep_timer_handler,                                     // 161 Sleep Timer
   MAC_timer_handler,                                       // 162 MacTimer
};

//*****************************************************************************
// Customer Configuration Area in Lock Page
//*****************************************************************************
typedef struct {
	uint32_t bootloaderCfg;     // Bootloader backdoor
  uint32_t imageValid;        // Image valid bytes
  uint32_t vectorAddr;        // Vector table located at flash start address
  uint8_t  pageLockBits[32];  // Unlock all flash pages and debug access
} lockPageCCA_t;

__attribute__((section(".flashcca"), used))
const lockPageCCA_t cca_lock_page =
{
  BOOTLOADER_BACKDOOR_DISABLE,
  FLASH_IMAGE_VALID,
  (uint32_t)&vectors, 
  { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  }
};

extern int main(void);
extern void prepareBootloader(void);

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void reset_handler (void) {
  uint32_t* source;
  uint32_t* destination;

	// Copy the data segment initializers from flash to SRAM.
	source = &_etext;
	for(destination = &_sdata; destination < &_edata; ) {
		*destination++ = *source++;
	}

	// Zero fill the bss segment.

  for(destination = &_sbss; destination < &_ebss; ) {
      *destination++ = 0;
  }

  // Prepare bootloader
  prepareBootloader();
          
  // Call the application's entry point.
  main();

  // End here if return from main()
  while(1);
}