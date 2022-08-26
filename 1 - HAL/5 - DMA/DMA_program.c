/*
 * DMA_program.c
 *
 *  Created on: Aug 24, 2022
 *      Author: ELHOSSENI
 */

#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/DMA/DMA_interface.h"
#include "../Inc/MCAL/DMA/DMA_private.h"
#include "../Inc/MCAL/DMA/DMA_configuration.h"

static void	(* DMA_CH1_CallBack)	(void) = NULL;
static void	(* DMA_CH2_CallBack)	(void) = NULL;
static void	(* DMA_CH3_CallBack)	(void) = NULL;
static void	(* DMA_CH4_CallBack)	(void) = NULL;
static void	(* DMA_CH5_CallBack)	(void) = NULL;
static void	(* DMA_CH6_CallBack)	(void) = NULL;
static void	(* DMA_CH7_CallBack)	(void) = NULL;

void DMA_voidInit (Channel_T Copy_u8DMAChannel)
{
#if Copy_u8DMAChannel == CH_2
	DMA1 -> channel[Copy_u8DMAChannel].CCR |= ((DataDir_1<<4)|(CircularMode_1<<5)|(MemIncMode_1<<7)|(PerIncMode_1<<6)
											    |(Peripheral_Size_1 <<8)|(Memory_Size_1<<10)|(Periority_Level_1<<12)
												|(Mem2Mem_1<<14));
#elif Copy_u8DMAChannel == CH_2
	DMA1 -> channel[Copy_u8DMAChannel].CCR |= ((DataDir_2<<4)|CircularMode_2<<5)|(MemIncMode_2<<7)|(PerIncMode_2<<6)
												|(Peripheral_Size_2 <<8)|(Memory_Size_2<<10)|(Periority_Level_2<<12)
											    |(Mem2Mem_2<<14));

#elif Copy_u8DMAChannel == CH_3
	DMA1 -> channel[Copy_u8DMAChannel].CCR |= ((DataDir_3<<4)|CircularMode_3<<5)|(MemIncMode_3<<7)|(PerIncMode_3<<6)
												|(Peripheral_Size_3 <<8)|(Memory_Size_3<<10)|(Periority_Level_3<<12)
											    |(Mem2Mem_3<<14));
#elif Copy_u8DMAChannel == CH_4
	DMA1 -> channel[Copy_u8DMAChannel].CCR |= ((DataDir_4<<4)|CircularMode_4<<5)|(MemIncMode_4<<7)|(PerIncMode_4<<6)
												|(Peripheral_Size_4 <<8)|(Memory_Size_4<<10)|(Periority_Level_4<<12)
											    |(Mem2Mem_4<<14));
#elif Copy_u8DMAChannel == CH_5
	DMA1 -> channel[Copy_u8DMAChannel].CCR |= ((DataDir_5<<4)|CircularMode_5<<5)|(MemIncMode_5<<7)|(PerIncMode_5<<6)
												|(Peripheral_Size_5 <<8)|(Memory_Size_5<<10)|(Periority_Level_5<<12)
											    |(Mem2Mem_5<<14));
#elif Copy_u8DMAChannel == CH_6
	DMA1 -> channel[Copy_u8DMAChannel].CCR |= ((DataDir_6<<4)|CircularMode_6<<5)|(MemIncMode_6<<7)|(PerIncMode_6<<6)
												|(Peripheral_Size_6 <<8)|(Memory_Size_6<<10)|(Periority_Level_6<<12)
											    |(Mem2Mem_6<<14));
#elif Copy_u8DMAChannel == CH_7
	DMA1 -> channel[Copy_u8DMAChannel].CCR |= ((DataDir_7<<4)|CircularMode_7<<5)|(MemIncMode_7<<7)|(PerIncMode_7<<6)
												|(Peripheral_Size_7 <<8)|(Memory_Size_7<<10)|(Periority_Level_7<<12)
											    |(Mem2Mem_7<<14));

#elif Copy_u8DMAChannel == CH_3
#endif
}


void DMA_voidClearFlag(Channel_T Copy_u8DMA_Channel , Flag_T Copy_u8Flag )
{
	SET_BIT(DMA1 -> IFCR , ((Copy_u8DMA_Channel*4)+ Copy_u8Flag));
}

u8   DMA_u8ReadFlag(Channel_T Copy_u8DMA_Channel , Flag_T Copy_u8Flag )
{
	return (GET_BIT(DMA1 -> IFCR , ((Copy_u8DMA_Channel*4)+ Copy_u8Flag)));
}

void DMA_voidChannelEnable(Channel_T Copy_u8DMA_Channel)
{
	SET_BIT(DMA1 -> channel[Copy_u8DMA_Channel].CCR , 0);
}

void DMA_voidChannelDisable(Channel_T Copy_u8DMA_Channel)
{
	CLR_BIT(DMA1 -> channel[Copy_u8DMA_Channel].CCR , 0);
}

void DMA_voidSetNumOfSentData(Channel_T Copy_u8DMA_Channel , u16 Copy_u16NumOfData)
{
	DMA1 -> channel[Copy_u8DMA_Channel].CNDTR = Copy_u16NumOfData;
}

void DMA_voidSetPreAddress(Channel_T Copy_u8DMA_Channel , u32 * Copy_u32PeripheralAdd, u32 * Copy_u32MemoryAdd)
{
	DMA1 -> channel[Copy_u8DMA_Channel].CPAR = Copy_u32PeripheralAdd;
	DMA1 -> channel[Copy_u8DMA_Channel].CMAR = Copy_u32MemoryAdd;

}

void DMA_voidInterruptEnable(Channel_T Copy_u8DMA_Channel , Interrupt_T Copy_u8DMAIntType)
{
	SET_BIT(DMA1->channel[Copy_u8DMA_Channel].CCR ,Copy_u8DMAIntType );
}

void DMA_voidInterruptDisable(Channel_T Copy_u8DMA_Channel , Interrupt_T Copy_u8DMAIntType)
{
	SET_BIT(DMA1 -> channel[Copy_u8DMA_Channel].CCR ,Copy_u8DMAIntType );
}

void DMA_SetCallBack(Channel_T Copy_u8DMA_Channel  , void (*pf)(void))
{	if(pf != NULL)
{
	switch(Copy_u8DMA_Channel)
	{
	case CH_1 :
		DMA_CH1_CallBack = pf ;
		break;
	case CH_2 :
		DMA_CH2_CallBack = pf ;
		break;
	case CH_3 :
		DMA_CH3_CallBack = pf ;
		break;
	case CH_4 :
		DMA_CH4_CallBack = pf ;
		break;
	case CH_5 :
		DMA_CH5_CallBack = pf ;
		break;
	case CH_6 :
		DMA_CH6_CallBack = pf ;
		break;
	case CH_7 :
		DMA_CH7_CallBack = pf ;
		break;
	}
}
}


void DMA1_Channel1_IRQHandler()
{
	DMA_voidClearFlag(CH_1, GIF);
	DMA_voidClearFlag(CH_1, HTIF);
	DMA_voidClearFlag(CH_1, TCIF);
	DMA_voidClearFlag(CH_1, TEIF);
	DMA_CH1_CallBack();
}

void DMA1_Channel2_IRQHandler()
{
	DMA_voidClearFlag(CH_2, GIF);
	DMA_voidClearFlag(CH_2, HTIF);
	DMA_voidClearFlag(CH_2, TCIF);
	DMA_voidClearFlag(CH_2, TEIF);
	DMA_CH2_CallBack();
}

void DMA1_Channel3_IRQHandler()
{
	DMA_voidClearFlag(CH_3, GIF);
	DMA_voidClearFlag(CH_3, HTIF);
	DMA_voidClearFlag(CH_3, TCIF);
	DMA_voidClearFlag(CH_3, TEIF);
	DMA_CH3_CallBack();
}

void DMA1_Channel4_IRQHandler()
{
	DMA_voidClearFlag(CH_4, GIF);
	DMA_voidClearFlag(CH_4, HTIF);
	DMA_voidClearFlag(CH_4, TCIF);
	DMA_voidClearFlag(CH_4, TEIF);
	DMA_CH4_CallBack();
}

void DMA1_Channel5_IRQHandler()
{
	DMA_voidClearFlag(CH_5, GIF);
	DMA_voidClearFlag(CH_5, HTIF);
	DMA_voidClearFlag(CH_5, TCIF);
	DMA_voidClearFlag(CH_5, TEIF);
	DMA_CH5_CallBack();
}

void DMA1_Channel6_IRQHandler()
{
	DMA_voidClearFlag(CH_6, GIF);
	DMA_voidClearFlag(CH_6, HTIF);
	DMA_voidClearFlag(CH_6, TCIF);
	DMA_voidClearFlag(CH_6, TEIF);
	DMA_CH6_CallBack();
}

void DMA_Channel7_IRQHandler()
{
	DMA_voidClearFlag(CH_7, GIF);
	DMA_voidClearFlag(CH_7, HTIF);
	DMA_voidClearFlag(CH_7, TCIF);
	DMA_voidClearFlag(CH_7, TEIF);
	DMA_CH7_CallBack();
}


