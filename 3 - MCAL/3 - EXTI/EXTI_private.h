/*
 * EXTI_private.h
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٢
 *      Author: ELHOSSENI
 */

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

#include "../Inc/LIB/STD_TYPES.h"

#define EXTI ((volatile EXTI_t*)0x40010400)

typedef struct
{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;

}EXTI_t;

/*
_estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word	MemManage_Handler
  .word	BusFault_Handler
  .word	UsageFault_Handler
  .word	0
  .word	0
  .word	0
  .word	0
  .word	SVC_Handler
  .word	DebugMon_Handler
  .word	0
  .word	PendSV_Handler
  .word	SysTick_Handler
  .word	WWDG_IRQHandler           			 Window Watchdog interrupt
  .word	PVD_IRQHandler            			 PVD through EXTI line detection interrupt
  .word	TAMPER_IRQHandler         			 Tamper interrupt
  .word	RTC_IRQHandler            			 RTC global interrupt
  .word	FLASH_IRQHandler          			 Flash global interrupt
  .word	RCC_IRQHandler            			 RCC global interrupt
  .word	EXTI0_IRQHandler          			 EXTI Line0 interrupt
  .word	EXTI1_IRQHandler          			 EXTI Line1 interrupt
  .word	EXTI2_IRQHandler          			 EXTI Line2 interrupt
  .word	EXTI3_IRQHandler          			 EXTI Line3 interrupt
  .word	EXTI4_IRQHandler          			 EXTI Line4 interrupt
  .word	DMA1_Channel1_IRQHandler  			 DMA1 Channel1 global interrupt
  .word	DMA1_Channel2_IRQHandler  			 DMA1 Channel2 global interrupt
  .word	DMA1_Channel3_IRQHandler  			 DMA1 Channel3 global interrupt
  .word	DMA1_Channel4_IRQHandler  			 DMA1 Channel4 global interrupt
  .word	DMA1_Channel5_IRQHandler  			 DMA1 Channel5 global interrupt
  .word	DMA1_Channel6_IRQHandler  			 DMA1 Channel6 global interrupt
  .word	DMA1_Channel7_IRQHandler  			 DMA1 Channel7 global interrupt
  .word	ADC1_2_IRQHandler         			 ADC1 and ADC2 global interrupt
  .word	USB_HP_CAN_TX_IRQHandler  			 USB High Priority or CAN TX interrupts
  .word	USB_LP_CAN_RX0_IRQHandler 			 USB Low Priority or CAN RX0 interrupts
  .word	CAN_RX1_IRQHandler        			 CAN RX1 interrupt
  .word	CAN_SCE_IRQHandler        			 CAN SCE interrupt
  .word	EXTI9_5_IRQHandler        			 EXTI Line[9:5] interrupts
  .word	TIM1_BRK_IRQHandler       			 TIM1 Break interrupt
  .word	TIM1_UP_IRQHandler        			 TIM1 Update interrupt
  .word	TIM1_TRG_COM_IRQHandler   			 TIM1 Trigger and Commutation interrupts
  .word	TIM1_CC_IRQHandler        			 TIM1 Capture Compare interrupt
  .word	TIM2_IRQHandler           			 TIM2 global interrupt
  .word	TIM3_IRQHandler           			 TIM3 global interrupt
  .word	TIM4_IRQHandler           			 TIM4 global interrupt
  .word	I2C1_EV_IRQHandler        			 I2C1 event interrupt
  .word	I2C1_ER_IRQHandler        			 I2C1 error interrupt
  .word	I2C2_EV_IRQHandler        			 I2C2 event interrupt
  .word	I2C2_ER_IRQHandler        			 I2C2 error interrupt
  .word	SPI1_IRQHandler           			 SPI1 global interrupt
  .word	SPI2_IRQHandler           			 SPI2 global interrupt
  .word	USART1_IRQHandler         			 USART1 global interrupt
  .word	USART2_IRQHandler         			 USART2 global interrupt
  .word	USART3_IRQHandler         			 USART3 global interrupt
  .word	EXTI15_10_IRQHandler      			 EXTI Line[15:10] interrupts
  .word	RTCAlarm_IRQHandler       			 RTC Alarms through EXTI line interrupt
  .word	0                         			 Reserved
  .word	TIM8_BRK_IRQHandler       			 TIM8 Break interrupt
  .word	TIM8_UP_IRQHandler        			 TIM8 Update interrupt
  .word	TIM8_TRG_COM_IRQHandler   			 TIM8 Trigger and Commutation interrupts
  .word	TIM8_CC_IRQHandler        			 TIM8 Capture Compare interrupt
  .word	ADC3_IRQHandler           			 ADC3 global interrupt
  .word	FSMC_IRQHandler           			 FSMC global interrupt
  .word	SDIO_IRQHandler           			 SDIO global interrupt
  .word	TIM5_IRQHandler           			 TIM5 global interrupt
  .word	SPI3_IRQHandler           			 SPI3 global interrupt
  .word	UART4_IRQHandler          			 UART4 global interrupt
  .word	UART5_IRQHandler          			 UART5 global interrupt
  .word	TIM6_IRQHandler           			 TIM6 global interrupt
  .word	TIM7_IRQHandler           			 TIM7 global interrupt
  .word	DMA2_Channel1_IRQHandler  			 DMA2 Channel1 global interrupt
  .word	DMA2_Channel2_IRQHandler  			 DMA2 Channel2 global interrupt
  .word	DMA2_Channel3_IRQHandler  			 DMA2 Channel3 global interrupt
  .word	DMA2_Channel4_5_IRQHandler			 DMA2 Channel4 and DMA2 Channel5 global interrupt

******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
******************************************************************************

  	 	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

  	 	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

  	 	MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler

  	 	BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler

	 	UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler

	 	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	 	DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler

	 	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	 	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	 	WWDG_IRQHandler
	.thumb_set WWDG_IRQHandler,Default_Handler

	 	PVD_IRQHandler
	.thumb_set PVD_IRQHandler,Default_Handler

	 	TAMPER_IRQHandler
	.thumb_set TAMPER_IRQHandler,Default_Handler

	 	RTC_IRQHandler
	.thumb_set RTC_IRQHandler,Default_Handler

	 	FLASH_IRQHandler
	.thumb_set FLASH_IRQHandler,Default_Handler

	 	RCC_IRQHandler
	.thumb_set RCC_IRQHandler,Default_Handler

	 	EXTI0_IRQHandler
	.thumb_set EXTI0_IRQHandler,Default_Handler

	 	EXTI1_IRQHandler
	.thumb_set EXTI1_IRQHandler,Default_Handler

	 	EXTI2_IRQHandler
	.thumb_set EXTI2_IRQHandler,Default_Handler

	 	EXTI3_IRQHandler
	.thumb_set EXTI3_IRQHandler,Default_Handler

	 	EXTI4_IRQHandler
	.thumb_set EXTI4_IRQHandler,Default_Handler

	 	DMA1_Channel1_IRQHandler
	.thumb_set DMA1_Channel1_IRQHandler,Default_Handler

	 	DMA1_Channel2_IRQHandler
	.thumb_set DMA1_Channel2_IRQHandler,Default_Handler

	 	DMA1_Channel3_IRQHandler
	.thumb_set DMA1_Channel3_IRQHandler,Default_Handler

	 	DMA1_Channel4_IRQHandler
	.thumb_set DMA1_Channel4_IRQHandler,Default_Handler

	 	DMA1_Channel5_IRQHandler
	.thumb_set DMA1_Channel5_IRQHandler,Default_Handler

	 	DMA1_Channel6_IRQHandler
	.thumb_set DMA1_Channel6_IRQHandler,Default_Handler

	 	DMA1_Channel7_IRQHandler
	.thumb_set DMA1_Channel7_IRQHandler,Default_Handler

	 	ADC1_2_IRQHandler
	.thumb_set ADC1_2_IRQHandler,Default_Handler

	 	USB_HP_CAN_TX_IRQHandler
	.thumb_set USB_HP_CAN_TX_IRQHandler,Default_Handler

	 	USB_LP_CAN_RX0_IRQHandler
	.thumb_set USB_LP_CAN_RX0_IRQHandler,Default_Handler

	 	CAN_RX1_IRQHandler
	.thumb_set CAN_RX1_IRQHandler,Default_Handler

	 	CAN_SCE_IRQHandler
	.thumb_set CAN_SCE_IRQHandler,Default_Handler

	 	EXTI9_5_IRQHandler
	.thumb_set EXTI9_5_IRQHandler,Default_Handler

	 	TIM1_BRK_IRQHandler
	.thumb_set TIM1_BRK_IRQHandler,Default_Handler

	 	TIM1_UP_IRQHandler
	.thumb_set TIM1_UP_IRQHandler,Default_Handler

	 	TIM1_TRG_COM_IRQHandler
	.thumb_set TIM1_TRG_COM_IRQHandler,Default_Handler

	 	TIM1_CC_IRQHandler
	.thumb_set TIM1_CC_IRQHandler,Default_Handler

	 	TIM2_IRQHandler
	.thumb_set TIM2_IRQHandler,Default_Handler

	 	TIM3_IRQHandler
	.thumb_set TIM3_IRQHandler,Default_Handler

	 	TIM4_IRQHandler
	.thumb_set TIM4_IRQHandler,Default_Handler

	 	I2C1_EV_IRQHandler
	.thumb_set I2C1_EV_IRQHandler,Default_Handler

	 	I2C1_ER_IRQHandler
	.thumb_set I2C1_ER_IRQHandler,Default_Handler

	 	I2C2_EV_IRQHandler
	.thumb_set I2C2_EV_IRQHandler,Default_Handler

	 	I2C2_ER_IRQHandler
	.thumb_set I2C2_ER_IRQHandler,Default_Handler

	 	SPI1_IRQHandler
	.thumb_set SPI1_IRQHandler,Default_Handler

	 	SPI2_IRQHandler

	 	USART1_IRQHandler

	 	USART2_IRQHandler

	 	USART3_IRQHandler

	 	EXTI15_10_IRQHandler

	 	RTCAlarm_IRQHandler

	 	TIM8_BRK_IRQHandler

	 	TIM8_UP_IRQHandler

		TIM8_TRG_COM_IRQHandler

	 	TIM8_CC_IRQHandler

	 	ADC3_IRQHandler

	 	FSMC_IRQHandler

	 	SDIO_IRQHandler

	 	TIM5_IRQHandler

	 	SPI3_IRQHandler

	 	UART4_IRQHandler

	 	UART5_IRQHandler

	 	TIM6_IRQHandler

	 	TIM7_IRQHandler

	 	DMA2_Channel1_IRQHandler

	 	DMA2_Channel2_IRQHandler

	 	DMA2_Channel3_IRQHandler

	 	DMA2_Channel4_5_IRQHandler

	 	SystemInit*/

#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
