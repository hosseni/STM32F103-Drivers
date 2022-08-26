/*
 * DMA_interface.h
 *
 *  Created on: Aug 24, 2022
 *      Author: ELKHOLY
 */

#ifndef MCAL_DMA_DMA_INTERFACE_H_
#define MCAL_DMA_DMA_INTERFACE_H_

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/MCAL/DMA/DMA_private.h"

void DMA_voidInit(Channel_T Copy_u8DMA_Channel);

void DMA_voidClearFlag(Channel_T Copy_u8DMA_Channel , Flag_T Copy_u8Flag );

u8   DMA_u8ReadFlag(Channel_T Copy_u8DMA_Channel , Flag_T Copy_u8Flag );

void DMA_voidChannelEnable(Channel_T Copy_u8DMA_Channel);

void DMA_voidChannelDisable(Channel_T Copy_u8DMA_Channel);

void DMA_voidSetNumOfSentData(Channel_T Copy_u8DMA_Channel , u16 Copy_u16NumOfData);

void DMA_voidSetPreAddress(Channel_T Copy_u8DMA_Channel , u32 * Copy_u32PeripheralAdd, u32 * Copy_u32MemoryAdd);

void DMA_voidInterruptEnable(Channel_T Copy_u8DMA_Channel , Interrupt_T Copy_u8DMAIntType);

void DMA_voidInterruptDisable(Channel_T Copy_u8DMA_Channel , Interrupt_T Copy_u8DMAIntType);

void DMA_SetCallBack(Channel_T Copy_u8DMA_Channel  , void (*pf)(void));

#endif /* MCAL_DMA_DMA_INTERFACE_H_ */
