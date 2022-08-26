/*
 * Push_Button_interface.h
 *
 *  Created on: Aug 24, 2022
 *      Author: ELKHOLY
 */

#ifndef HAL_PUSH_PUTTON_PUSH_BUTTON_INTERFACE_H_
#define HAL_PUSH_PUTTON_PUSH_BUTTON_INTERFACE_H_

#include "../Inc/LIB/STD_TYPES.h"

#define MAXIMUM_NUM_OF_PB 1

// pull deown
#define PRESSED_VOLT  1
#define RELEASED_VOLT 0

typedef enum
{
	pressed,
	pre_pressed,
	pre_released,
	released

}PB_Status_T;

typedef enum
{
	PB_0
}PB_t;

typedef struct
{
	u8 port;
	u8 pin;
	PB_Status_T state;
	u8 sample[2];

}PB_Info_t;

extern PB_Info_t PB_config[MAXIMUM_NUM_OF_PB];

void HPush_Button_voidInit (PB_t Pb ,PB_Status_T init_status);
PB_Status_T HPB_PB_t_tGetStatus (PB_t PB);
void HPB_Update (void);

#endif /* HAL_PUSH_PUTTON_PUSH_BUTTON_INTERFACE_H_ */
