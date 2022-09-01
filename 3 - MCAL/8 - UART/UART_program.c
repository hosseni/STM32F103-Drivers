/*
 * UART_program.c
 *
 *  Created on: Aug 30, 2022
 *      Author: ELHOSSENI
 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/UART/UART_interface.h"
#include "../Inc/MCAL/UART/UART_private.h"
#include "../Inc/MCAL/UART/UART_configuration.h"

void 	MUART_voidInit 		(UART_Num_t UART_NUM)
{
	/*clear CR1 - CR2 - CR3 - SR */
	UARTChannel[UART_NUM] -> CR [0] = CLR_REGISTER;
	UARTChannel[UART_NUM] -> CR [1] = CLR_REGISTER;
	UARTChannel[UART_NUM] -> CR [2] = CLR_REGISTER;
	UARTChannel[UART_NUM] -> SR     = CLR_REGISTER;

	UARTChannel[UART_NUM] -> CR[0]     |=    ( (SEND_BREAK      << SPK)  | (RECEIVER_WAKEUP     <<RWU)| (PARITY_SELECTION << PS)
										     | (RECEIVER_ENABLE << RE)   | (TRANSMITTER_ENABLE  <<TE) | (PARITY_CONTROL << PCE)
										     | (WAKEUP_METHOD   << WAKE) | (WORD_LENGTH         <<M));

	UARTChannel[UART_NUM] -> CR[1]     |=    ( (NODE_ADDRESS 		 << ADD)  | (LIN_BREAK_DETEC_LENGTH << LBDL)| (LIN_BREAK_DETEC_INTERRUPT << LBDIE)
										     | (LAST_BIT_CLOCK_PULSE << LBCL) | (CLOCK_PHASE     		<< CPHA)| (CLOCK_POLARITY 			 << CPOL)
										     | (CLOCK_PIN_ENABLE 	 << CLKEN)| (STOP_BIT_NUMBER        << STOP)| (LIN_MODE 				 << LINEN));

	UARTChannel[UART_NUM] -> CR[2]     |=    ( (IRDA_MODE 	    << IREN) | (IRDA_LOW_POWER << IRLP)  | (HALF_DUPLEX  << HDSEL)
										     | (SMARTCARD_NACK  << NACK) | (SMARTCARD_MODE << SCEN)  | (DMA_RECEIVER <<  DMAR)
										     | (DMA_TRANSMITTER << DMAT) | (RTS_MODE       << RTSE)  | (CTS_MODE     <<  CTSE));

	/*set boudrate*/
	UARTChannel[UART_NUM] -> BRR  = UART_BAUDRATE;
	/*enable UART*/
	UARTChannel[UART_NUM] -> CR[0] |= (ENABLE_UART << UE);

}
void    MUART_voidTransmitChar (UART_Num_t UART_NUM, u8 Copy_u8Data)
{

	/*load data from user to Data Reg*/
	UARTChannel[UART_NUM] ->DR = Copy_u8Data;
	/*wait to transmit*/
	while ( (GET_BIT(UARTChannel[UART_NUM] -> SR, TC)) == 0);
if ((GET_BIT(UARTChannel[UART_NUM] -> SR, TC)) == 1)
	{
#if	TRANSMITTER_COMPLETE_INTERRUPT  == ENABLE_INTERRUPT
	SET_BIT(UARTChannel[UART_NUM] ->CR[0], TCIE);
#endif
	}

}
void 	MUART_voidTransmitSTR  (UART_Num_t UART_NUM, u8 Copy_u8Arr[])
{

	u8 Local_u8Counter = 0;
	while (Copy_u8Arr[Local_u8Counter] != '\0')
	{
		/*load data from user to Data Reg*/
		UARTChannel[UART_NUM] -> DR = Copy_u8Arr[Local_u8Counter];
		/*wait to transmit*/
		while ((GET_BIT(UARTChannel[UART_NUM] -> SR, TC)) == 0);
		Local_u8Counter++;
	}

#if	TRANSMITTER_COMPLETE_INTERRUPT  == ENABLE_INTERRUPT
	SET_BIT(UARTChannel[UART_NUM] ->CR[0], TCIE);
#endif

}
u8		MUART_u8Recive         (UART_Num_t UART_NUM)
{

	u32 Local_u8RecivedData = 0;
	/*wait to receive*/

	while ((GET_BIT(UARTChannel[UART_NUM]  -> SR, RXNE)) == 0);
	Local_u8RecivedData = UARTChannel[UART_NUM]  -> DR;

#if	RECEIVER_COMPLETE_INTERRUPT     == ENABLE_INTERRUPT
	SET_BIT(UARTChannel[UART_NUM] ->CR[0], RXNEIE);
#endif
	return Local_u8RecivedData;

}

void MUART_voidSetCallBack 	  (UART_Num_t UART_NUM, CallBack CallBackFunc, Interrupt_t Copy_Interrupt_t)
{
	/*Store the call back function address*/
	CallBackArray[UART_NUM][Copy_Interrupt_t] = CallBackFunc;

}

void USART1_IRQHandler (void)
{
#if IDLE_INTERRUPT                		== ENABLE_INTERRUPT
	/*check IDLE flag*/
	if (GET_BIT(UARTChannel[UART_1] -> SR, IDLE))
	{
		/*clear interrupt IDLEIE flag*/
		CLR_BIT(UARTChannel[UART_1] -> CR[0], IDLEIE);
		/*Call the Halndler*/
		CallBackArray[UART_1][IDLE_Interrupt_]();
	}
#elif	RECEIVER_COMPLETE_INTERRUPT     == ENABLE_INTERRUPT
	/*check RXNE : received reg not empty flag*/
	if (GET_BIT(UARTChannel[UART_1] -> SR, RXNE))
	{
		/*Call the Halndler*/
		CallBackArray[UART_1][RECEIVE_COMPLETE_Interrupt_]();
		/*clear interrupt RX flag*/
		CLR_BIT(UARTChannel[UART_1] -> CR[0], RXNEIE);

	}
#elif	TRANSMITTER_COMPLETE_INTERRUPT  == ENABLE_INTERRUPT
	/*check TC flag*/
	if (GET_BIT(UARTChannel[UART_1] -> SR, TC))
	{
		/*clear interrupt TCIE flag*/
		CLR_BIT(UARTChannel[UART_1] -> CR[0], TCIE);
		/*Call the Halndler*/
		CallBackArray[UART_1][TRANSMITTER_COMPLET_Interrupt_]();
	}
#elif	TRANSMITTER_EMPTY_INTERRUPT           == ENABLE_INTERRUPT
		/*check TXE flag*/
	if (GET_BIT(UARTChannel[UART_1] -> SR, TXE))
	{
		/*clear interrupt TXEIE flag*/
		CLR_BIT(UARTChannel[UART_1] -> CR[0], TXEIE);
		/*Call the Halndler*/
		CallBackArray[UART_1][TRANSMITTER_EMPTY_Interrupt_]();
	}
#elif	PARITY_INTERRUPT                == ENABLE_INTERRUP
	/*ceck PE */
	if (GET_BIT(UARTChannel[UART_1] -> SR, PE))
	{
		/*clear interrupt PEIE flag*/
		CLR_BIT(UARTChannel[UART_1] -> CR[0], PEIE);
		/*Call the Halndler*/
		CallBackArray[UART_1][PARITY_Interrupt_]();
	}
#elif	ERROR_INTERRUPT                 == ENABLE_INTERRUPT
				/*check NE, FE, ORE flag*/
	if (GET_BIT(UARTChannel[UART_1] -> SR, NE) || GET_BIT(UARTChannel[UART_1] -> SR, FE)||
		GET_BIT(UARTChannel[UART_1] -> SR, ORE) )
	{
		/*clear interrupt EIE flag*/
		CLR_BIT(UARTChannel[UART_1] -> SR, EIE);
		/*Call the Halndler*/
		CallBackArray[UART_1][ERROR_Interrupt_]();

	}
#elif	LIN_BREAK_DETEC_INTERRUPT       == ENABLE_INTERRUPT

#elif	CTS_INTERRUPT                   == ENABLE_INTERRUPT
		/*check CTS */
	if (GET_BIT(UARTChannel[UART_1] -> SR, CTS))
	{
	/*clear interrupt CTSIE flag*/
	CLR_BIT(UARTChannel[UART_1] -> SR, CTSIE);
	/*Call the Halndler*/
	CallBackArray[UART_1][CTS_Interrupt_]();
	}
#endif



}


void USART2_IRQHandler (void)
{

#if IDLE_INTERRUPT                		== ENABLE_INTERRUPT
	/*check IDLE flag*/
	if (GET_BIT(UARTChannel[UART_2] -> SR, IDLE))
	{
		/*clear interrupt IDLEIE flag*/
		CLR_BIT(UARTChannel[UART_2] -> CR[0], IDLEIE);
		/*Call the Halndler*/
		CallBackArray[UART_2][IDLE_Interrupt_]();
	}
#elif	RECEIVER_COMPLETE_INTERRUPT     == ENABLE_INTERRUPT
	/*check RXNE : received reg not empty flag*/
	if (GET_BIT(UARTChannel[UART_2] -> SR, RXNE))
	{
		/*Call the Halndler*/
		CallBackArray[UART_2][RECEIVE_COMPLETE_Interrupt_]();
		/*clear interrupt RX flag*/
		CLR_BIT(UARTChannel[UART_2] -> CR[0], RXNEIE);

	}
#elif	TRANSMITTER_COMPLETE_INTERRUPT  == ENABLE_INTERRUPT
	/*check TC flag*/
	if (GET_BIT(UARTChannel[UART_2] -> SR, TC))
	{
		/*clear interrupt TCIE flag*/
		CLR_BIT(UARTChannel[UART_2] -> CR[0], TCIE);
		/*Call the Halndler*/
		CallBackArray[UART_2][TRANSMITTER_COMPLET_Interrupt_]();
	}
#elif	TRANSMITTER_EMPTY_INTERRUPT           == ENABLE_INTERRUPT
		/*check TXE flag*/
	if (GET_BIT(UARTChannel[UART_2] -> SR, TXE))
	{
		/*clear interrupt TXEIE flag*/
		CLR_BIT(UARTChannel[UART_2] -> CR[0], TXEIE);
		/*Call the Halndler*/
		CallBackArray[UART_2][TRANSMITTER_EMPTY_Interrupt_]();
	}
#elif	PARITY_INTERRUPT                == ENABLE_INTERRUP
	/*ceck PE */
	if (GET_BIT(UARTChannel[UART_2] -> SR, PE))
	{
		/*clear interrupt PEIE flag*/
		CLR_BIT(UARTChannel[UART_2] -> CR[0], PEIE);
		/*Call the Halndler*/
		CallBackArray[UART_2][PARITY_Interrupt_]();
	}
#elif	ERROR_INTERRUPT                 == ENABLE_INTERRUPT
				/*check NE, FE, ORE flag*/
	if (GET_BIT(UARTChannel[UART_2] -> SR, NE) || GET_BIT(UARTChannel[UART_2] -> SR, FE)||
		GET_BIT(UARTChannel[UART_2] -> SR, ORE) )
	{
		/*clear interrupt EIE flag*/
		CLR_BIT(UARTChannel[UART_2] -> SR, EIE);
		/*Call the Halndler*/
		CallBackArray[UART_2][ERROR_Interrupt_]();

	}
#elif	LIN_BREAK_DETEC_INTERRUPT       == ENABLE_INTERRUPT

#elif	CTS_INTERRUPT                   == ENABLE_INTERRUPT
		/*check CTS */
	if (GET_BIT(UARTChannel[UART_2] -> SR, CTS))
	{
	/*clear interrupt CTSIE flag*/
	CLR_BIT(UARTChannel[UART_2] -> SR, CTSIE);
	/*Call the Halndler*/
	CallBackArray[UART_2][CTS_Interrupt_]();
	}
#endif

}

void USART3_IRQHandler (void)
{


#if IDLE_INTERRUPT                		== ENABLE_INTERRUPT
	/*check IDLE flag*/
	if (GET_BIT(UARTChannel[UART_3] -> SR, IDLE))
	{
		/*clear interrupt IDLEIE flag*/
		CLR_BIT(UARTChannel[UART_3] -> CR[0], IDLEIE);
		/*Call the Halndler*/
		CallBackArray[UART_3][IDLE_Interrupt_]();
	}
#elif	RECEIVER_COMPLETE_INTERRUPT     == ENABLE_INTERRUPT
	/*check RXNE : received reg not empty flag*/
	if (GET_BIT(UARTChannel[UART_3] -> SR, RXNE))
	{
		/*Call the Halndler*/
		CallBackArray[UART_3][RECEIVE_COMPLETE_Interrupt_]();
		/*clear interrupt RX flag*/
		CLR_BIT(UARTChannel[UART_3] -> CR[0], RXNEIE);

	}
#elif	TRANSMITTER_COMPLETE_INTERRUPT  == ENABLE_INTERRUPT
	/*check TC flag*/
	if (GET_BIT(UARTChannel[UART_3] -> SR, TC))
	{
		/*clear interrupt TCIE flag*/
		CLR_BIT(UARTChannel[UART_3] -> CR[0], TCIE);
		/*Call the Halndler*/
		CallBackArray[UART_3][TRANSMITTER_COMPLET_Interrupt_]();
	}
#elif	TRANSMITTER_EMPTY_INTERRUPT           == ENABLE_INTERRUPT
		/*check TXE flag*/
	if (GET_BIT(UARTChannel[UART_3] -> SR, TXE))
	{
		/*clear interrupt TXEIE flag*/
		CLR_BIT(UARTChannel[UART_3] -> CR[0], TXEIE);
		/*Call the Halndler*/
		CallBackArray[UART_3][TRANSMITTER_EMPTY_Interrupt_]();
	}
#elif	PARITY_INTERRUPT                == ENABLE_INTERRUP
	/*ceck PE */
	if (GET_BIT(UARTChannel[UART_3] -> SR, PE))
	{
		/*clear interrupt PEIE flag*/
		CLR_BIT(UARTChannel[UART_3] -> CR[0], PEIE);
		/*Call the Halndler*/
		CallBackArray[UART_3][PARITY_Interrupt_]();
	}
#elif	ERROR_INTERRUPT                 == ENABLE_INTERRUPT
				/*check NE, FE, ORE flag*/
	if (GET_BIT(UARTChannel[UART_3] -> SR, NE) || GET_BIT(UARTChannel[UART_3] -> SR, FE)||
		GET_BIT(UARTChannel[UART_3] -> SR, ORE) )
	{
		/*clear interrupt EIE flag*/
		CLR_BIT(UARTChannel[UART_3] -> SR, EIE);
		/*Call the Halndler*/
		CallBackArray[UART_3][ERROR_Interrupt_]();

	}
#elif	LIN_BREAK_DETEC_INTERRUPT       == ENABLE_INTERRUPT

#elif	CTS_INTERRUPT                   == ENABLE_INTERRUPT
		/*check CTS */
	if (GET_BIT(UARTChannel[UART_3] -> SR, CTS))
	{
	/*clear interrupt CTSIE flag*/
	CLR_BIT(UARTChannel[UART_3] -> SR, CTSIE);
	/*Call the Halndler*/
	CallBackArray[UART_3][CTS_Interrupt_]();
	}
#endif

}

void USART4_IRQHandler (void)
{


#if IDLE_INTERRUPT                		== ENABLE_INTERRUPT
	/*check IDLE flag*/
	if (GET_BIT(UARTChannel[UART_4] -> SR, IDLE))
	{
		/*clear interrupt IDLEIE flag*/
		CLR_BIT(UARTChannel[UART_4] -> CR[0], IDLEIE);
		/*Call the Halndler*/
		CallBackArray[UART_4][IDLE_Interrupt_]();
	}
#elif	RECEIVER_COMPLETE_INTERRUPT     == ENABLE_INTERRUPT
	/*check RXNE : received reg not empty flag*/
	if (GET_BIT(UARTChannel[UART_4] -> SR, RXNE))
	{
		/*Call the Halndler*/
		CallBackArray[UART_4][RECEIVE_COMPLETE_Interrupt_]();
		/*clear interrupt RX flag*/
		CLR_BIT(UARTChannel[UART_4] -> CR[0], RXNEIE);

	}
#elif	TRANSMITTER_COMPLETE_INTERRUPT  == ENABLE_INTERRUPT
	/*check TC flag*/
	if (GET_BIT(UARTChannel[UART_4] -> SR, TC))
	{
		/*clear interrupt TCIE flag*/
		CLR_BIT(UARTChannel[UART_4] -> CR[0], TCIE);
		/*Call the Halndler*/
		CallBackArray[UART_4][TRANSMITTER_COMPLET_Interrupt_]();
	}
#elif	TRANSMITTER_EMPTY_INTERRUPT           == ENABLE_INTERRUPT
		/*check TXE flag*/
	if (GET_BIT(UARTChannel[UART_4] -> SR, TXE))
	{
		/*clear interrupt TXEIE flag*/
		CLR_BIT(UARTChannel[UART_4] -> CR[0], TXEIE);
		/*Call the Halndler*/
		CallBackArray[UART_4][TRANSMITTER_EMPTY_Interrupt_]();
	}
#elif	PARITY_INTERRUPT                == ENABLE_INTERRUP
	/*ceck PE */
	if (GET_BIT(UARTChannel[UART_4] -> SR, PE))
	{
		/*clear interrupt PEIE flag*/
		CLR_BIT(UARTChannel[UART_4] -> CR[0], PEIE);
		/*Call the Halndler*/
		CallBackArray[UART_4][PARITY_Interrupt_]();
	}
#elif	ERROR_INTERRUPT                 == ENABLE_INTERRUPT
				/*check NE, FE, ORE flag*/
	if (GET_BIT(UARTChannel[UART_4] -> SR, NE) || GET_BIT(UARTChannel[UART_4] -> SR, FE)||
		GET_BIT(UARTChannel[UART_4] -> SR, ORE) )
	{
		/*clear interrupt EIE flag*/
		CLR_BIT(UARTChannel[UART_4] -> SR, EIE);
		/*Call the Halndler*/
		CallBackArray[UART_4][ERROR_Interrupt_]();

	}
#elif	LIN_BREAK_DETEC_INTERRUPT       == ENABLE_INTERRUPT

#elif	CTS_INTERRUPT                   == ENABLE_INTERRUPT
		/*check CTS */
	if (GET_BIT(UARTChannel[UART_4] -> SR, CTS))
	{
	/*clear interrupt CTSIE flag*/
	CLR_BIT(UARTChannel[UART_4] -> SR, CTSIE);
	/*Call the Halndler*/
	CallBackArray[UART_4][CTS_Interrupt_]();
	}
#endif

}

void USART5_IRQHandler (void)
{

#if IDLE_INTERRUPT                		== ENABLE_INTERRUPT
	/*check IDLE flag*/
	if (GET_BIT(UARTChannel[UART_5] -> SR, IDLE))
	{
		/*clear interrupt IDLEIE flag*/
		CLR_BIT(UARTChannel[UART_5] -> CR[0], IDLEIE);
		/*Call the Halndler*/
		CallBackArray[UART_5][IDLE_Interrupt_]();
	}
#elif	RECEIVER_COMPLETE_INTERRUPT     == ENABLE_INTERRUPT
	/*check RXNE : received reg not empty flag*/
	if (GET_BIT(UARTChannel[UART_5] -> SR, RXNE))
	{
		/*Call the Halndler*/
		CallBackArray[UART_5][RECEIVE_COMPLETE_Interrupt_]();
		/*clear interrupt RX flag*/
		CLR_BIT(UARTChannel[UART_5] -> CR[0], RXNEIE);

	}
#elif	TRANSMITTER_COMPLETE_INTERRUPT  == ENABLE_INTERRUPT
	/*check TC flag*/
	if (GET_BIT(UARTChannel[UART_5] -> SR, TC))
	{
		/*clear interrupt TCIE flag*/
		CLR_BIT(UARTChannel[UART_5] -> CR[0], TCIE);
		/*Call the Halndler*/
		CallBackArray[UART_5][TRANSMITTER_COMPLET_Interrupt_]();
	}
#elif	TRANSMITTER_EMPTY_INTERRUPT           == ENABLE_INTERRUPT
		/*check TXE flag*/
	if (GET_BIT(UARTChannel[UART_5] -> SR, TXE))
	{
		/*clear interrupt TXEIE flag*/
		CLR_BIT(UARTChannel[UART_5] -> CR[0], TXEIE);
		/*Call the Halndler*/
		CallBackArray[UART_5][TRANSMITTER_EMPTY_Interrupt_]();
	}
#elif	PARITY_INTERRUPT                == ENABLE_INTERRUP
	/*ceck PE */
	if (GET_BIT(UARTChannel[UART_5] -> SR, PE))
	{
		/*clear interrupt PEIE flag*/
		CLR_BIT(UARTChannel[UART_5] -> CR[0], PEIE);
		/*Call the Halndler*/
		CallBackArray[UART_5][PARITY_Interrupt_]();
	}
#elif	ERROR_INTERRUPT                 == ENABLE_INTERRUPT
				/*check NE, FE, ORE flag*/
	if (GET_BIT(UARTChannel[UART_5] -> SR, NE) || GET_BIT(UARTChannel[UART_5] -> SR, FE)||
		GET_BIT(UARTChannel[UART_5] -> SR, ORE) )
	{
		/*clear interrupt EIE flag*/
		CLR_BIT(UARTChannel[UART_5] -> SR, EIE);
		/*Call the Halndler*/
		CallBackArray[UART_5][ERROR_Interrupt_]();

	}
#elif	LIN_BREAK_DETEC_INTERRUPT       == ENABLE_INTERRUPT

#elif	CTS_INTERRUPT                   == ENABLE_INTERRUPT
		/*check CTS */
	if (GET_BIT(UARTChannel[UART_5] -> SR, CTS))
	{
	/*clear interrupt CTSIE flag*/
	CLR_BIT(UARTChannel[UART_5] -> SR, CTSIE);
	/*Call the Halndler*/
	CallBackArray[UART_5][CTS_Interrupt_]();
	}
#endif

}
