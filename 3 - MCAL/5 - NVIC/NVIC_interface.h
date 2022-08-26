/*
 * NVIC_interface.h
 *
 *  Created on: ١٧‏/٠٨‏/٢٠٢٢
 *      Author: ELKHOLY
 */

#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_

#include "../Inc/LIB/STD_TYPES.h"

/*group priority*/
#define Group0  0
#define Group1  1
#define Group2  2
#define Group3  3
#define Group4  4
#define Group5  5
#define Group6  6
#define Group7  7
#define Group8  8
#define Group9  9
#define Group10 10
#define Group11 11
#define Group12 12
#define Group13 13
#define Group14 14
#define Group15 15

/*sub priority*/
#define Sub0  0
#define Sub1  1
#define Sub2  2
#define Sub3  3
#define Sub4  4
#define Sub5  5
#define Sub6  6
#define Sub7  7
#define Sub8  8
#define Sub9  9
#define Sub10 10
#define Sub11 11
#define Sub12 12
#define Sub13 13
#define Sub14 14
#define Sub15 15

/*EXTI FROM VECTOR TABLE*/
#define EXTI0 		    6
#define EXTI1 		    7
#define EXTI2           8
#define EXTI3           9
#define EXTI4           10
#define DMA1_Channel1   11
#define DMA1_Channel2   12
#define DMA1_Channel3   13
#define DMA1_Channel4   14
#define DMA1_Channel5   15
#define DMA1_Channel6   16
#define DMA1_Channel7   17
#define ADC1_2		    18
#define USB_HP_CAN_TX   19
#define USB_LP_CAN_RX   20
#define CAN_RX1         21
#define CAN_SCE         22
#define EXTI9_5		    23
#define TIM1_BRK        24
#define TIM1_UP		    25
#define TIM1_TRG_COM    26
#define TIM1_CC		    27
#define TIM2		    28
#define TIM3		    29
#define TIM4		    30
#define I2C1_EV		    31
#define I2C1_ER		    32
#define I2C2_EV		    33
#define I2C2_ER		    34
#define SPI1		    35
#define SPI2		    36
#define USART1		    37
#define USART2		    38
#define USART3		    39
#define EXTI15_10	    40
#define RTCAlarm		41
#define USBWakeup		42
#define TIM8_BRK		43
#define TIM8_UP			44
#define TIM8_TRG_COM    45
#define TIM8_CC			46
#define ADC3			47
#define FSMC			48
#define SDIO			49
#define TIM5			50
#define SPI3			51
#define UART4			52
#define UART5			53
#define TIM6		    54
#define TIM7		    55
#define DMA2_Channel1	56
#define DMA2_Channel2	57
#define DMA2_Channel3   58
#define DMA2_Channel4_5 59


void MNVIC_voidInit (void);

void MNVIC_voidEnableInterrupt  (u8 Copy_u8IntNum);
void MNVIC_voidDisableInterrupt (u8 Copy_u8IntNum);

void MNVIC_voidSetPendingFlag   (u8 Copy_u8IntNum);
void MNVIC_voidClearPendingFlag (u8 Copy_u8IntNum);

u8 MNVIC_u8GetAvticeFlag (u8 Copy_u8IntNum);
void MNVIC_voidSetPriority (u8 Copy_u8IntNum, u8 Copy_u8GroupNum, u8 Copy_u8SubNum);
#endif /* MCAL_NVIC_NVIC_INTERFACE_H_ */
