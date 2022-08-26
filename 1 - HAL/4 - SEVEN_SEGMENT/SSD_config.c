/*
 * SSD_config.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Asmaa Hashim
 */

#include "../Inc/HAL/SSD_config.h"
#include "../Inc/HAL/SSD_interface.h"

#include "../Inc/MCAL/DIO/DIO_interface.h"

 SSD_info SSD_config[MAX_NUM_SSD] = {

							 {GPIOA , {PIN0 , PIN1 , PIN2 , PIN3 , PIN4 , PIN5 , PIN6 } , PIN7 , NULL_Symbol , ssd_disable},
							 {GPIOB , {PIN7 , PIN8 , PIN9 , PIN10 , PIN11 , PIN12 , PIN13 } , PIN14 , NULL_Symbol , ssd_disable},
 };
