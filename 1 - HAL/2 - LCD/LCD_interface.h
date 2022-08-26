/*
 * LCD_interface.h
 *
 *  Created on: Aug 22, 2022
 *      Author: ELKHOLY
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_




#define LCD_DECIMAL                   10
#define LCD_NUMBER_TYPE_AFTER_POINT   100


void HLCD_voidInit(void);
void HLCD_voidCMD(u8 Copy_u8Command);
void HLCD_voidSetCursor(u8 Copy_u8Row, u8 Copy_u8Col);
void HLCD_void_ClearSreen(void);
void HLCD_voidTurnOffDisplay(void);
void HLCD_voidWriteChar(u8 Copy_u8Character, u8 Copy_u8Row, u8 Copy_u8Col);
void HLCD_voidWriteString(u8 * Copy_u8String, u8 Copy_u8Row, u8 Copy_u8Col);
void HLCD_voidWriteIntNum(u8 Copy_u8Number, u8 Copy_u8Row, u8 Copy_u8Col);
static void HLCD_void_GO_TO_POS(u8 Copy_uoRow, u8 Copy_u8Col);
#endif /* HAL_LCD_LCD_INTERFACE_H_ */
