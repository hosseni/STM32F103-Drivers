/*
 * LCD_configuration.h
 *
 *  Created on: Aug 22, 2022
 *      Author: EHOSSENI
 */

#ifndef HAL_LCD_LCD_CONFIGURATION_H_
#define HAL_LCD_LCD_CONFIGURATION_H_

#define LCD_4_BIT_MODE     4
#define LCD_8_BIT_MODE     8
#define LCD_16_2           2
#define LCD_16_4           4

/**
 * LCD_4_BIT_MODE: For 4 Pins (D4,D5,D6,D7)
 * LCD_8_BIT_MODE: For 8 Pins (D0,D2,D3,D4,D5,D6,D7)
 *
**/
#define LCD_MODE           LCD_8_BIT_MODE

/**
 * LCD_16_2: For 16*2 LCD Character (16 COLOUMN, 2 ROW)
 * LCD_16_4: For 16*4 LCD Character (16 COLOUMN, 4 ROW)
**/
#define LCD_TYPE           LCD_16_2


#define LCD_RS  GPIO_U8_PORTA ,GPIO_U8_PIN9
#define LCD_EN  GPIO_U8_PORTA ,GPIO_U8_PIN8

#if LCD_MODE == LCD_8_BIT_MODE

#define LCD_DATA_PORT  GPIO_U8_PORTA
#define LCD_D0   GPIO_U8_PIN0
#define LCD_D1   GPIO_U8_PIN1
#define LCD_D2   GPIO_U8_PIN2
#define LCD_D3   GPIO_U8_PIN3
#endif
#define LCD_D4   GPIO_U8_PIN4
#define LCD_D5   GPIO_U8_PIN5
#define LCD_D6   GPIO_U8_PIN6
#define LCD_D7   GPIO_U8_PIN7

#endif /* HAL_LCD_LCD_CONFIGURATION_H_ */
