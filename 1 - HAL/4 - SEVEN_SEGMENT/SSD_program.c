/*
 * SSD_program.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Asmaa Hashim
 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/DIO/DIO_interface.h"


#include "../Inc/HAL/SSD_private.h"
#include "../Inc/HAL/SSD_config.h"
#include "../Inc/HAL/SSD_interface.h"


void  HSSD_init(tSSDs  ssd,  u8  init_data ,tSSD_states init_state )
{
	for(int i = 0 ; i < 7 ; i++)
	{

		MGPIO_voidSetPinDirection( SSD_config[ssd].port ,  SSD_config[ssd].pins[i] , OUTPUT_SPEED_2MHZ_PP);
	}

	MGPIO_voidSetPinDirection( SSD_config[ssd].port ,  SSD_config[ssd].enable_pin , OUTPUT_SPEED_2MHZ_PP);
	HSSD_set_data(  ssd ,  init_data);
	HSSD_set_State(ssd , init_state );


}

void HSSD_Update(void)
{
	static tSSDs current_ssd = SSD_1;

	tSSDs ssd_id ;

	for(ssd_id = SSD_1  ; ssd_id < MAX_NUM_SSD ; ssd_id++)
	{
		HSSD_set_State( ssd_id , ssd_disable );
	}

	for(int i= 0 ; i< 7 ; i++)
	{

		MGPIO_voidSetPinValue( SSD_config[current_ssd].port , SSD_config[current_ssd].pins[i] ,
				               GET_BIT(ssd_data[SSD_config[current_ssd].data] , i));
	}

	HSSD_set_State( current_ssd , ssd_enable );

	current_ssd++;

	if(current_ssd  == MAX_NUM_SSD)
	{
		current_ssd = SSD_1;
	}

}

void HSSD_set_data(tSSDs  ssd ,  u8  data)
{
	SSD_config[ssd].data = data ;
}

void HSSD_set_State(tSSDs  ssd ,tSSD_states state )
{
	MGPIO_voidSetPinValue(SSD_config[ssd].port , SSD_config[ssd].enable_pin , state);
	SSD_config[ssd].state  = state ;
}





