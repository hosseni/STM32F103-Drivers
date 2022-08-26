/*
 * SSD_interface.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Asmaa Hashim
 */

#ifndef HAL_SSD_INTERFACE_H_
#define HAL_SSD_INTERFACE_H_

//#define "SSD"

#include "../LIB/STD_TYPES.h"
#include "SSD_config.h"
#define NULL_Symbol 10

typedef enum
{
	SSD_1,
	SSD_2

}tSSDs;

typedef enum
{
	ssd_enable   = ENABLE_VOLT ,
	ssd_disable  = DISABLE_VOLT

}tSSD_states;

typedef struct
{
	u8 port;
	u8 pins[7];
	u8 enable_pin;
	u8 data ;
	tSSD_states state ;
}SSD_info;

extern SSD_info  SSD_config[MAX_NUM_SSD];

void  HSSD_init(tSSDs  ssd ,  u8  init_data ,tSSD_states init_state );

void HSSD_Update(void);

void HSSD_set_data(tSSDs  ssd ,  u8  data);

void HSSD_set_State(tSSDs  ssd ,tSSD_states state );







#endif /* HAL_SSD_INTERFACE_H_ */
