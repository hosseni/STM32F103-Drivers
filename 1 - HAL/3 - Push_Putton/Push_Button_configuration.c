/*
 * Push_Button_configuration.c
 *
 *  Created on: Aug 24, 2022
 *      Author: ELKHOLY
 */


#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/HAL/Push_Putton/Push_Button_interface.h"

PB_Info_t PB_config[MAXIMUM_NUM_OF_PB] = { {GPIO_U8_PORTB , GPIO_U8_PIN0, released, {RELEASED_VOLT ,RELEASED_VOLT } } };
