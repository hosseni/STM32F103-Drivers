/*
 * EXTI_program.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٢
 *      Author: ELHOSSENI
 */
#include <stdio.h>

#include "../Inc/MCAL/EXTI/EXTI_interface.h"
#include "../Inc/MCAL/EXTI/EXTI_private.h"
#include "../Inc/MCAL/EXTI/EXTI_configuration.h"

#include "../Inc/MCAL/NVIC/NVIC_interface.h"

static void (*EXTI0_CallBack)  (void) = NULL;
static void (*EXTI1_CallBack)  (void) = NULL;
static void (*EXTI2_CallBack)  (void) = NULL;


void	MEXTI_voidInit(void)
{
	/*initialize interrupts "set edges"*/
	/**/
}
void	MEXTI_voidEnableEXTI(u8 Copy_u8Line)
{
	SET_BIT(EXTI->IMR, Copy_u8Line);
}
void	MEXTI_voidDisableEXTI(u8 Copy_u8Line)
{
	CLR_BIT(EXTI->IMR, Copy_u8Line);

}
void	MEXTI_voidSetEdge(u8 Copy_u8Line, u8 Copy_u8Edge)
{
switch(Copy_u8Edge)
{
	case MEXTI_RISING_EDGE:		SET_BIT(EXTI->RTSR, Copy_u8Line);
								CLR_BIT(EXTI->FTSR, Copy_u8Line);	break;

	case MEXTI_FALLING_EDGE: 	SET_BIT(EXTI->FTSR, Copy_u8Line);
								CLR_BIT(EXTI->RTSR, Copy_u8Line);	break;

	case MEXTI_OnChange_EDGE:	SET_BIT(EXTI->RTSR, Copy_u8Line);
								SET_BIT(EXTI->FTSR, Copy_u8Line); 	break;
}
}
void	MEXTI_voidEnableSWI(u8 Copy_u8Line)
{
	SET_BIT(EXTI->SWIER, Copy_u8Line);
}

void   MEXTI_voidClearPending(u8 Copy_u8Line)
{
	SET_BIT(EXTI->PR, Copy_u8Line);
}

void    MEXTI_voidSetCallBack_EXTI0 (void (*ptr) (void))
{
	if (ptr != NULL)
	{
		EXTI0_CallBack = ptr;
	}
}

void    MEXTI_voidSetCallBack_EXTI1 (void (*ptr) (void))
{
	if (ptr != NULL)
	{
		EXTI1_CallBack = ptr;
	}
}

void    MEXTI_voidSetCallBack_EXTI2 (void (*ptr) (void))
{
	if (ptr != NULL)
	{
		EXTI2_CallBack = ptr;
	}
}

void EXTI0_IRQHandler ()
{
	EXTI0_CallBack ();
}

void EXTI1_IRQHandler ()
{
	EXTI1_CallBack();
}

void EXTI2_IRQHandler ()
{
	EXTI2_CallBack();
}
