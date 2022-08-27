/*
 * EXTI_interface.h
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٢
 *      Author: ELKHOLY
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"


#define MEXTI_RISING_EDGE	  0
#define MEXTI_FALLING_EDGE    1
#define MEXTI_OnChange_EDGE   2

typedef void (*EXTI_voidPtrToFunction)(void *);
typedef void* EXTI_voidPtrToParameter;


typedef enum
{
	EXTI_LINE_0 ,
	EXTI_LINE_1 ,
	EXTI_LINE_2 ,
	EXTI_LINE_3 ,
	EXTI_LINE_4 ,
	EXTI_LINE_5 ,
	EXTI_LINE_6 ,
	EXTI_LINE_7 ,
	EXTI_LINE_8 ,
	EXTI_LINE_9 ,
	EXTI_LINE_10,
	EXTI_LINE_11,
	EXTI_LINE_12,
	EXTI_LINE_13,
	EXTI_LINE_14,
	EXTI_LINE_15

}EXTI_LINE_t;

typedef enum
{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC

}IntPort_T;

void	MEXTI_voidInit(EXTI_LINE_t ,IntPort_T);
void	MEXTI_voidEnableEXTI(u8 Copy_u8Line);
void	MEXTI_voidDisableEXTI(u8 Copy_u8Line);
void	MEXTI_voidSetEdge(u8 Copy_u8Line, u8 Copy_u8Edge);
void	MEXTI_voidEnableSWI(u8 v);
void    MEXTI_voidClearPending(u8 Copy_u8Line);
void    MEXTI_voidSetCallBack_EXTI(EXTI_LINE_t Copy_u8EXTI_Line, void(*Copy_vFuncPtr)(void));
#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
