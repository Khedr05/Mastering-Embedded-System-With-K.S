/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : Atmega32_Drivers
// File          : ssd_config.h
// Date          : 6 Aug 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/
#ifndef HAL_SSD_SSD_CONFIG_H_
#define HAL_SSD_SSD_CONFIG_H_

#include "../../MCAL/gpio/gpio_interface.h"

typedef enum { SSD_OK = 0, SSD_NOK, SSD_NULL_PTR } EN_SSD_systemState_t;

typedef enum { SSD_CATHODE_COMMON = 0, SSD_ANODE_COMMON } EN_SSD_typeOfCommon_t;

typedef enum {
  SSD_ZERO = 0,
  SSD_ONE,
  SSD_TWO,
  SSD_THREE,
  SSD_FOUR,
  SSD_FIVE,
  SSD_SIX,
  SSD_SEVEN,
  SSD_EGIHT,
  SSD_NINE,
  SSD_DOT
} EN_SSD_numbers_t;

typedef enum { SSD_FIRST = 0, SSD_SECOND } EN_SSD_index_t;

typedef struct {
  EN_SSD_typeOfCommon_t ssdCommonType;
  EN_GPIO_mcuPorts_t ssdPinAPortName;
  EN_GPIO_mcuPins_t ssdPinAPinNumber;
  EN_GPIO_mcuPorts_t ssdPinBPortName;
  EN_GPIO_mcuPins_t ssdPinBPinNumber;
  EN_GPIO_mcuPorts_t ssdPinCPortName;
  EN_GPIO_mcuPins_t ssdPinCPinNumber;
  EN_GPIO_mcuPorts_t ssdPinDPortName;
  EN_GPIO_mcuPins_t ssdPinDPinNumber;
  EN_GPIO_mcuPorts_t ssdPinEPortName;
  EN_GPIO_mcuPins_t ssdPinEPinNumber;
  EN_GPIO_mcuPorts_t ssdPinFPortName;
  EN_GPIO_mcuPins_t ssdPinFPinNumber;
  EN_GPIO_mcuPorts_t ssdPinGPortName;
  EN_GPIO_mcuPins_t ssdPinGPinNumber;
  EN_GPIO_mcuPorts_t ssdPinComPortName;
  EN_GPIO_mcuPins_t ssdPinComPinNumber;
  EN_GPIO_mcuPorts_t ssdPinDotPortName;
  EN_GPIO_mcuPins_t ssdPinDotPinNumber;
} ST_SSD_cfg_t;

typedef struct {
  EN_SSD_typeOfCommon_t ssdFirstCommonType;
  EN_SSD_typeOfCommon_t ssdSecondCommonType;
  EN_GPIO_mcuPorts_t ssdPinAPortName;
  EN_GPIO_mcuPins_t ssdPinAPinNumber;
  EN_GPIO_mcuPorts_t ssdPinBPortName;
  EN_GPIO_mcuPins_t ssdPinBPinNumber;
  EN_GPIO_mcuPorts_t ssdPinCPortName;
  EN_GPIO_mcuPins_t ssdPinCPinNumber;
  EN_GPIO_mcuPorts_t ssdPinDPortName;
  EN_GPIO_mcuPins_t ssdPinDPinNumber;
  EN_GPIO_mcuPorts_t ssdPinEPortName;
  EN_GPIO_mcuPins_t ssdPinEPinNumber;
  EN_GPIO_mcuPorts_t ssdPinFPortName;
  EN_GPIO_mcuPins_t ssdPinFPinNumber;
  EN_GPIO_mcuPorts_t ssdPinGPortName;
  EN_GPIO_mcuPins_t ssdPinGPinNumber;
  EN_GPIO_mcuPorts_t ssdPinDotPortName;
  EN_GPIO_mcuPins_t ssdPinDotPinNumber;
  EN_GPIO_mcuPorts_t ssdPinFirstComPortName;
  EN_GPIO_mcuPins_t ssdPinFirstComPinNumber;
  EN_GPIO_mcuPorts_t ssdPinSecondComPortName;
  EN_GPIO_mcuPins_t ssdPinSecondComPinNumber;
  EN_SSD_index_t ssdCurrentDisplay;
} ST_SSD_DualCfg_t;

#endif /* HAL_SSD_SSD_CONFIG_H_ */
