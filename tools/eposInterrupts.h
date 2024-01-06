/**
 * @file Interrupts.h
 * @author Lucas Yukio Yotsui de Carvalho (lucas.yotsui@gmail.com)
 * @brief All usable interrupt handlers used by the STM32 microcontroller
 * @version 0.1
 * @date 2024-01-02
 * @copyright Copyright (c) 2024 
 * 
 * @details In this file are declared all the interrupt handlers available to the
 * user. All of these handlers are defined as weak alias symbols such that they 
 * can either be overridden by the user or fallback to a default behavior. To 
 * override these handlers one must only include this file provide and their 
 * own declaration of the desired handler. In that case, just make sure to copy
 * the function's signature properly or it won't work. 
*/

#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

// * ---------------------------------------------------------------------------------------- * //
// |                                Default interrupt handler                                 | //
// * ---------------------------------------------------------------------------------------- * //
void systick_handler(void);
void GPIOA_handler(void);
void GPIOB_handler(void);
void GPIOC_handler(void);
void GPIOD_handler(void);
void UART0_handler(void);
void UART1_handler(void);
void SSI0_handler(void);
void I2C_handler(void);
void ADC_handler(void);
void watchdog_handler(void);
void timer0A_handler(void);
void timer0B_handler(void);
void timer1A_handler(void);
void timer1B_handler(void);
void timer2A_handler(void);
void timer2B_handler(void);
void analog_comparator_handler(void);
void RF_Core_Rx_Tx_handler(void);
void RF_Core_error_handler(void);
void system_control_handler(void);
void flash_control_handler(void);
void AES_handler(void);
void PKA_handler(void);
void sleep_timer_handler(void);
void MAC_timer_handler(void);
void SSI1_handler(void);
void timer3A_handler(void);
void timer3B_handler(void);
void uDMA_handler(void);
void uDMA_error_handler(void);
void USB_handler(void);

// * ---------------------------------------------------------------------------------------- * //
// |                                System interrupt handlers                                 | //
// * ---------------------------------------------------------------------------------------- * //
void NMI_handler(void);
void hard_fault_handler(void);
void mem_manage_fault_handler(void);
void bus_fault_handler(void);
void usage_fault_handler(void);
void sv_call_handler(void);
void debug_monitor_handler(void);
void pend_sv_call_handler(void);

#endif