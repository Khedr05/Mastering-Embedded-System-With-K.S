/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : EEPROM.h
// Date          : Feb 1, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef HAL_INC_EEPROM_H_
#define HAL_INC_EEPROM_H_

#include "I2C.h"


#define HEEPROM_SLA_ADDR		0x2A

COMMON_uddtApiState_t HEEPROM_uddtInit(void);
COMMON_uddtApiState_t HEEPROM_uddtWriteNbytes(uint8 u8MemoryAddr,uint8 *u8Bytes,uint8 u8DataLength);
COMMON_uddtApiState_t HEEPROM_uddtReadByte(uint8 u8Addr,uint8 *u8DataOut,uint8 u8DataLength);























#endif /* HAL_INC_EEPROM_H_ */
