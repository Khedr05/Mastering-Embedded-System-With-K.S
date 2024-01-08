/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : Atmega32_Drivers
// File          : kp_interface.h
// Date          : 10 Aug 2023 */ GitHub        : https://github.com/sherifkhadr
/*************************************************************************/
#ifndef HAL_KEYPAD_KP_INTERFACE_H_
#define HAL_KEYPAD_KP_INTERFACE_H_

#include "../../COMMON/std_types.h"
#include "../../HAL/keypad/kp_config.h"

EN_EKP_systemStatus_t EKP_init(ST_EKP_cfg_t const *ST_ptrKeypadInstance);

EN_EKP_systemStatus_t
EKP_scanningForPressedBtn(ST_EKP_cfg_t const *ST_ptrKeypadInstance , uint8_t *pressedBtnVal);

#endif /* HAL_KEYPAD_KP_INTERFACE_H_ */
