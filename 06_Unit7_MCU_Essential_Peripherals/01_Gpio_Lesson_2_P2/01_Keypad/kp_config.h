/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : Atmega32_Drivers
// File          : kp_config.h
// Date          : 10 Aug 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/
#ifndef HAL_KEYPAD_KP_CONFIG_H_
#define HAL_KEYPAD_KP_CONFIG_H_

#include "../../MCAL/gpio/gpio_interface.h"

#define KEYPAD_ROWS_SIZE 4
#define KEYPAD_COLUMNS_SIZE 4
#define LOOP_STARTING_VALUE 0

typedef enum { EKP_OK = 0, EKP_NOK, EKP_PTR_NULL } EN_EKP_systemStatus_t;

typedef struct {
  ST_GPIO_cfg_t arrOfRows[KEYPAD_ROWS_SIZE];
  ST_GPIO_cfg_t arrOfColumns[KEYPAD_COLUMNS_SIZE];
} ST_EKP_cfg_t;

#endif /* HAL_KEYPAD_KP_CONFIG_H_ */
