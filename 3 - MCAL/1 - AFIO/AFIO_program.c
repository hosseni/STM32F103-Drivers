/*
 * AFIO_program.c
 *
 *  Created on: ٢٤‏/٠٨‏/٢٠٢٢
 *      Author: ELHOSSENI
 */

#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/AFIO/AFIO_interface.h"
#include "../Inc/MCAL/AFIO/AFIO_private.h"
#include "../Inc/MCAL/AFIO/AFIO_configuration.h"

 void MAFIO_voidSetEXTIConfiguration(u8 copy_u8Line, u8 copy_u8Port)
 {
	 if(copy_u8Line < 4)
	 	 {
	 		 //AFIO_EXTICR1
	 		AFIO->EXTICR1  &=   ~((0b1111)<< (copy_u8Line * 4));
	 		AFIO->EXTICR1  |= ((copy_u8Port)<< (copy_u8Line * 4));
	 	 }
	 else if(copy_u8Line < 8)
 	 {
		 copy_u8Line -= 4;
 		 //AFIO_EXTICR2
 		AFIO->EXTICR2  &=   ~((0b1111)<< (copy_u8Line * 4));
 		AFIO->EXTICR2  |= ((copy_u8Port)<< (copy_u8Line * 4));
 	 }
	 else if(copy_u8Line < 12)
	 	 {
			 copy_u8Line -= 8;
	 		 //AFIO_EXTICR3
	 		AFIO->EXTICR3  &=     ~((0b1111)<< (copy_u8Line * 4));
	 		AFIO->EXTICR3  |= ((copy_u8Port)<< (copy_u8Line * 4));
	 	 }
	 else if(copy_u8Line < 16)
	 	 {
			 copy_u8Line -= 12;
	 		 //AFIO_EXTICR2
	 		AFIO->EXTICR4  &=   ~((0b1111)<< (copy_u8Line * 4));
	 		AFIO->EXTICR4  |= ((copy_u8Port)<< (copy_u8Line * 4));
	 	 }
 }
