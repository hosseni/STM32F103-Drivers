/*
 * EXTI_program.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٢
 *      Author: ELHOSSENI
 */

#include "../Inc/MCAL/EXTI/EXTI_interface.h"
#include "../Inc/MCAL/EXTI/EXTI_private.h"
#include "../Inc/MCAL/EXTI/EXTI_configuration.h"

#include "../Inc/MCAL/NVIC/NVIC_interface.h"
#include "../Inc/MCAL/AFIO/AFIO_interface.h"


static void (*EXTI_vEXTI_CallBack[19])(void);

void	MEXTI_voidInit(EXTI_LINE_t  Copy_u8ExtiName , IntPort_T Copy_u8PortName)
{
	MAFIO_voidSetEXTIConfiguration(Copy_u8ExtiName, Copy_u8PortName);
}
void	MEXTI_voidEnableEXTI(EXTI_LINE_t Copy_u8Line)
{
	SET_BIT(EXTI->IMR, Copy_u8Line);
}
void	MEXTI_voidDisableEXTI(EXTI_LINE_t Copy_u8Line)
{
	CLR_BIT(EXTI->IMR, Copy_u8Line);

}
void	MEXTI_voidSetEdge(EXTI_LINE_t Copy_u8Line, u8 Copy_u8Edge)
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
void	MEXTI_voidEnableSWI(EXTI_LINE_t Copy_u8Line)
{
	SET_BIT(EXTI->SWIER, Copy_u8Line);
}

void   MEXTI_voidClearPending(EXTI_LINE_t Copy_u8Line)
{
	SET_BIT(EXTI->PR, Copy_u8Line);
}

void    MEXTI_voidSetCallBack_EXTI(EXTI_LINE_t Copy_u8EXTI_Line, void(*Copy_vFuncPtr)(void))
{
	EXTI_vEXTI_CallBack[Copy_u8EXTI_Line] = Copy_vFuncPtr;
}


void EXTI0_IRQHandler(void)
{
	EXTI_vEXTI_CallBack[EXTI_LINE_0]();
	MEXTI_voidClearPending(EXTI_LINE_0);
}

void EXTI1_IRQHandler(void)
{
	EXTI_vEXTI_CallBack[EXTI_LINE_1]();
	MEXTI_voidClearPending(EXTI_LINE_1);
}
void EXTI2_IRQHandler(void)
{
	EXTI_vEXTI_CallBack[EXTI_LINE_2]();
	MEXTI_voidClearPending(EXTI_LINE_2);
}
void EXTI3_IRQHandler(void)
{
	EXTI_vEXTI_CallBack[EXTI_LINE_3]();
	MEXTI_voidClearPending(EXTI_LINE_3);
}
void EXTI4_IRQHandler(void)
{
	EXTI_vEXTI_CallBack[EXTI_LINE_4]();
	MEXTI_voidClearPending(EXTI_LINE_4);
}
void EXTI9_5_IRQHandler  (void)
{
	if (GET_BIT(EXTI->PR, EXTI_LINE_5) == 1)
	{
		EXTI_vEXTI_CallBack[EXTI_LINE_5]();
	MEXTI_voidClearPending(EXTI_LINE_5);
	}
	if (GET_BIT(EXTI->PR, EXTI_LINE_6) == 1)
	{
		EXTI_vEXTI_CallBack[EXTI_LINE_6]();
	MEXTI_voidClearPending(EXTI_LINE_6);
	}
	if (GET_BIT(EXTI->PR, EXTI_LINE_7) == 1)
	{
		EXTI_vEXTI_CallBack[EXTI_LINE_7]();
	MEXTI_voidClearPending(EXTI_LINE_7);
	}
	if (GET_BIT(EXTI->PR, EXTI_LINE_8) == 1)
	{
		EXTI_vEXTI_CallBack[EXTI_LINE_8]();
	MEXTI_voidClearPending(EXTI_LINE_8);
	}
	if (GET_BIT(EXTI->PR, EXTI_LINE_9) == 1)
	{
		EXTI_vEXTI_CallBack[EXTI_LINE_9]();
	MEXTI_voidClearPending(EXTI_LINE_9);
}
}
	void EXTI15_10_IRQHandler    (void)
{
		if (GET_BIT(EXTI->PR, EXTI_LINE_10) == 1)
		{
			EXTI_vEXTI_CallBack[EXTI_LINE_10]();
		MEXTI_voidClearPending(EXTI_LINE_10);
		}
		if (GET_BIT(EXTI->PR, EXTI_LINE_11) == 1)
		{
			EXTI_vEXTI_CallBack[EXTI_LINE_11]();
		MEXTI_voidClearPending(EXTI_LINE_11);
		}
		if (GET_BIT(EXTI->PR, EXTI_LINE_12) == 1)
		{
			EXTI_vEXTI_CallBack[EXTI_LINE_12]();
		MEXTI_voidClearPending(EXTI_LINE_12);
		}
		if (GET_BIT(EXTI->PR, EXTI_LINE_13) == 1)
		{
			EXTI_vEXTI_CallBack[EXTI_LINE_13]();
		MEXTI_voidClearPending(EXTI_LINE_13);
		}
		if (GET_BIT(EXTI->PR, EXTI_LINE_14) == 1)
		{
			EXTI_vEXTI_CallBack[EXTI_LINE_14]();
		MEXTI_voidClearPending(EXTI_LINE_14);
		}
		if (GET_BIT(EXTI->PR, EXTI_LINE_15) == 1)
		{
			EXTI_vEXTI_CallBack[EXTI_LINE_15]();
		MEXTI_voidClearPending(EXTI_LINE_15);
		}
}
