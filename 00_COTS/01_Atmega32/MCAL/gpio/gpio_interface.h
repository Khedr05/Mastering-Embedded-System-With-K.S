/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : Atmega32_Drivers
// File          : gpio_interface.h
// Date          : 31 Jul 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/
#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

#include "../../COMMON/bit_math.h"
#include "../../COMMON/std_types.h"
#include "gpio_config.h"
#include "gpio_private.h"

EN_GPIO_systemState_t GPIO_initPin(ST_GPIO_cfg_t const *ST_ptrPinInstance);

EN_GPIO_systemState_t GPIO_changePinDir(ST_GPIO_cfg_t const *ST_ptrPinInstance,
                                        EN_GPIO_pinDir_t copyNewPinDir);

EN_GPIO_systemState_t GPIO_writePinLogic(ST_GPIO_cfg_t const *ST_ptrPinInstance,
                                         EN_GPIO_pinLogic_t copyNewPinLogic);

EN_GPIO_systemState_t GPIO_readPinLogic(ST_GPIO_cfg_t const *ST_ptrPinInstance,
                                        EN_GPIO_pinLogic_t *retCurrentPinLogic);

EN_GPIO_systemState_t
GPIO_togglePinLogic(ST_GPIO_cfg_t const *ST_ptrPinInstance);

EN_GPIO_systemState_t GPIO_initPort(EN_GPIO_mcuPorts_t copyPortName,
                                    EN_GPIO_pinDir_t copyPortDir,
                                    EN_GPIO_pinLogic_t copyPortLogic);

EN_GPIO_systemState_t GPIO_changePortDir(EN_GPIO_mcuPorts_t copyPortName,
                                         EN_GPIO_pinDir_t copyNewPortDir);

EN_GPIO_systemState_t GPIO_writePortLogic(EN_GPIO_mcuPorts_t copyPortName,
                                          EN_GPIO_pinLogic_t copyNewPortLogic);

EN_GPIO_systemState_t
GPIO_readPortLogic(EN_GPIO_mcuPorts_t copyPortName,
                   EN_GPIO_pinLogic_t *retCurrentPortLogic);

EN_GPIO_systemState_t GPIO_togglePortLogic(EN_GPIO_mcuPorts_t copyPortName);

EN_GPIO_systemState_t GPIO_set4msbValue(EN_GPIO_mcuPorts_t copyPortName,uint8_t value);

EN_GPIO_systemState_t GPIO_SetPortValue(EN_GPIO_mcuPorts_t copyPortName , uint32_t value);

#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
