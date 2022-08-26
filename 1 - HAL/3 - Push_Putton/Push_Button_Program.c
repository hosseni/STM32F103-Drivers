/*
 * Push_Button_Program.c
 *
 *  Created on: Aug 24, 2022
 *      Author: ELHOSSENI
 */

#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/HAL/Push_Putton/Push_Button_interface.h"
#include "../Inc/HAL/Push_Putton/Push_Button_private.h"
#include "../Inc/HAL/Push_Putton/Push_Button_configuration.h"

#include "../Inc/MCAL/GPIO/GPIO_interface.h"

void HPush_Button_voidInit (PB_t PB ,PB_Status_T init_status)
{
	MGPIO_voidSetPinDirection(PB_config[PB].port, PB_config[PB].pin, GPIO_INPUT_FLOATING);
	PB_config[PB].state = init_status;
}
PB_Status_T HPB_PB_t_tGetStatus (PB_t PB)
{
	return (PB_config[PB].state);
}
void HPB_Update (void)
{
	PB_t current_PB = PB_0;
	while(current_PB < MAXIMUM_NUM_OF_PB)
	{
		PB_config[current_PB].sample[0] = PB_config[current_PB].sample[1];
		PB_config[current_PB].sample[1] = MGPIO_u8GetPinValue(PB_config[current_PB].port, PB_config[current_PB].pin);

		switch (PB_config[current_PB].state)
		{
		case released :
			if (PB_config[current_PB].sample[0] == PRESSED_VOLT &&
				PB_config[current_PB].sample[1] == PRESSED_VOLT)
			{
				PB_config[current_PB].state = pre_pressed;
			}
			break;

		case pre_pressed :
			if (PB_config[current_PB].sample[0] == PRESSED_VOLT )
			{
				PB_config[current_PB].state = pressed;
			}
			break;
		case pressed :

			if (PB_config[current_PB].sample[0] == RELEASED_VOLT &&
				PB_config[current_PB].sample[1] == RELEASED_VOLT)
			{
				PB_config[current_PB].state = pre_released;
			}
			break;
		case pre_released :

			if (PB_config[current_PB].sample[0] == RELEASED_VOLT )
			{
				PB_config[current_PB].state = released;
			}
			break;
		}

		current_PB++;
	}
}
