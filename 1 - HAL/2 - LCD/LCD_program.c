

#include <stdlib.h>
#include <stdio.h>

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/STK/STK_interface.h"
#include "../Inc/HAL/LCD/LCD_INTERFACE.h"
#include "../Inc/HAL/LCD/LCD_configuration.h"
#include "../Inc/HAL/LCD/LCD_private.h"


#if   LCD_MODE == LCD_4_BIT_MODE
   #define LCD_DATA_PINS          4
#elif LCD_MODE == LCD_8_BIT_MODE
   #define LCD_DATA_PINS          8
#endif

#if   LCD_DATA_PINS == 4
   static u8 Static_u8DataPins[LCD_DATA_PINS] = {LCD_D4,LCD_D5,LCD_D6,LCD_D7};
#elif LCD_DATA_PINS == 8
   static u8 Static_u8DataPins[LCD_DATA_PINS] = {LCD_D0,LCD_D1,LCD_D2,LCD_D3,LCD_D4,LCD_D5,LCD_D6,LCD_D7};
#endif

#define LCD_COL_16        16
#define LCD_COL_32        32
static void HLCD_voidkick(u8 Copy_u8Character)
{
   /**
	* Assign Data on the pins of the confg
	* Make pulse to make lcd working
	**/
	for(u8 Local_u8Counter = 0;Local_u8Counter < LCD_DATA_PINS;Local_u8Counter++)
	{
		if(Copy_u8Character & (SET << Local_u8Counter))
		{
			MGPIO_voidSetPinValue(LCD_DATA_PORT,Static_u8DataPins[Local_u8Counter], GPIO_HIGH);
		}
		else
		{
			MGPIO_voidSetPinValue(LCD_DATA_PORT,Static_u8DataPins[Local_u8Counter], GPIO_LOW);
		}
	}

	MGPIO_voidSetPinValue(LCD_EN , GPIO_HIGH);
    MSTK_voidSetBusyWait(10);
	MGPIO_voidSetPinValue(LCD_EN , GPIO_LOW);
}

void HLCD_voidInit(void)
{
   /**
	* Set dirction output for data and control pins
	* Config the lcd to start working
	**/
	MGPIO_voidSetPinDirection(LCD_EN , GPIO_OUTPUT_PP_10MHZ);
	MGPIO_voidSetPinDirection(LCD_RS , GPIO_OUTPUT_PP_10MHZ);

   for(u8 Local_u8Counter = 0;Local_u8Counter < LCD_DATA_PINS;Local_u8Counter++)
	{
	   MGPIO_voidSetPinDirection(LCD_DATA_PORT, Static_u8DataPins[Local_u8Counter], GPIO_OUTPUT_PP_10MHZ);
	}
   #if   LCD_MODE == LCD_4_BIT_MODE
   HLCD_voidCMD(LCD_4BIT_MODE_CMD);
   HLCD_voidCMD(LCD_4BIT_MODE_2_LINE_CMD);
   #elif LCD_MODE == LCD_8_BIT_MODE
   HLCD_voidCMD(LCD_8BIT_MODE_2_LINE_CMD);
   #endif
   HLCD_voidSetCursor(0, 0);
   HLCD_voidCMD(LCD_ENTRY_MODE_CMD);
   HLCD_voidCMD(LCD_CURSOR_BLINK_CMD);
   HLCD_voidCMD(LCD_CLEAR_SCREEN_CMD);
}

void HLCD_voidCMD(u8 Copy_u8Command)
{
   /**
	* Select the register "command || data " in this case command
	* Sent the command
	**/

   MGPIO_voidSetPinValue(LCD_RS, GPIO_LOW);
   #if   LCD_MODE == LCD_4_BIT_MODE
   HLCD_voidkick((Copy_u8Command) >> 4);
   HLCD_voidkick(Copy_u8Command);
   #elif LCD_MODE == LCD_8_BIT_MODE
   HLCD_voidkick(Copy_u8Command);
   #endif
   MSTK_voidSetBusyWait(20);

}

void HLCD_voidSetCursor(u8 Copy_u8Row, u8 Copy_u8Col)
{
   switch(Copy_u8Row)
   {
      case 0 :
         HLCD_voidCMD((unsigned)(LCD_BEGIN_AT_FIRST_RAW_CMD  | Copy_u8Col));
      break;
      case 1 :
         HLCD_voidCMD((unsigned)(LCD_BEGIN_AT_SECOND_RAW_CMD | Copy_u8Col));
      break;
      #if LCD_TYPE == LCD_16_4
      case 2 :
         HLCD_voidCMD((unsigned)(LCD_BEGIN_AT_THIRD_RAW_CMD  | Copy_u8Col));
      break;
      case 3 :
         HLCD_voidCMD((unsigned)(LCD_BEGIN_AT_FOURTH_RAW_CMD | Copy_u8Col));
      break;
      #endif
   }
}

void HLCD_void_ClearSreen(void)
{
   HLCD_voidCMD(LCD_CLEAR_SCREEN_CMD);
}

void HLCD_voidTurnOffDisplay(void)
{
   HLCD_voidCMD(LCD_DISPLAY_OFF_CMD);
}

void HLCD_voidWriteChar(u8 Copy_u8Character, u8 Copy_u8Row, u8 Copy_u8Col)
{
	HLCD_void_GO_TO_POS(Copy_u8Row, Copy_u8Col);
	MGPIO_voidSetPinValue(LCD_RS, GPIO_HIGH);
   #if   LCD_MODE == LCD_4_BIT_MODE
   HLCD_voidkick((Copy_u8Character) >> 4);
   HLCD_voidkick(Copy_u8Character);
   #elif LCD_MODE == LCD_8_BIT_MODE
   HLCD_voidkick(Copy_u8Character);
   #endif
   MSTK_voidSetBusyWait(20);

}

void HLCD_voidWriteString(u8 * Copy_u8String,  u8 Copy_u8Row, u8 Copy_u8Col)
{
   u8 Local_u8Counter = 0;
   while(Copy_u8String[Local_u8Counter] != '\0')
   {
      HLCD_voidWriteChar(Copy_u8String[Local_u8Counter], Copy_u8Row, Copy_u8Col );
      Local_u8Counter++;
      Copy_u8Col++;
	  if(Local_u8Counter == LCD_COL_16)
      {
         HLCD_voidSetCursor(1, 0);
      }
      else if(Local_u8Counter == LCD_COL_32)
      {
         HLCD_void_ClearSreen();
         HLCD_voidSetCursor(1, 0);
         Local_u8Counter = 0;
      }
   }
}


void HLCD_voidWriteIntNum(u8 Copy_u8Number, u8 Copy_u8Row, u8 Copy_u8Col)
{
   u8 * Local_u8Buffer[16];
   itoa(Copy_u8Number, Local_u8Buffer, LCD_DECIMAL);
   HLCD_voidWriteString(Local_u8Buffer, Copy_u8Row, Copy_u8Col);
}

 void HLCD_void_GO_TO_POS(u8 Copy_uoRow, u8 Copy_u8Col)
{
	u8 address = 0;
	if (Copy_uoRow <= 1 && Copy_u8Col <= 15)
	{
		// get DDRAM address
		address = (Copy_uoRow * 0x40) + Copy_u8Col;  // (row == 0)?row1:row2
		/* Set DDRAM address :
			 * 				RS RW  DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
			 * 				0	0	1  AC6 AC5 AC4 AC3 AC2 AC1 AC0			 */
		address = SET_BIT(address, 7);
		//set DDRAM adderss
		HLCD_voidCMD(address);

	}
}
