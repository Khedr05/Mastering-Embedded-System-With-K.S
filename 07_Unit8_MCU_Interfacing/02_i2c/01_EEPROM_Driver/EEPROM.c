/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : EEPROM.c
// Date          : Feb 1, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#include "EEPROM.h"

COMMON_uddtApiState_t HEEPROM_uddtInit(void)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	MI2C_uddtCfg_t I2C1CFG;

	I2C1CFG.I2Cx = I2C1;
	I2C1CFG.P_IRQCallback = NULL_PTR;
	I2C1CFG.u32AckCtrl = MI2C_ACK_ENABLE;
	I2C1CFG.u32ClkSpeed = MI2C_SCLK_SM_100K;
	I2C1CFG.u32ClkStretchStates = MI2C_STRETCHING_ENABLE;
	I2C1CFG.u32GenralCallAddrDetection = MI2C_ENGC_ENABLE;
	I2C1CFG.u32I2cMode = MI2C_MODE_I2C;

	ret = MI2C_uddtGpioSetPins(I2C1);
	if(ret != UAPI_OK) return ret;
	ret = MI2C_uddtInit(&I2C1CFG);

	return ret;
}

COMMON_uddtApiState_t HEEPROM_uddtWriteNbytes(uint8 u8MemoryAddr,uint8 *u8Bytes,uint8 u8DataLength)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(u8Bytes != NULL_PTR)
	{
		uint8 i=0,u8Buffer[256];
		u8Buffer[0] = (uint8)(u8MemoryAddr>>8);
		u8Buffer[1] = (uint8)(u8MemoryAddr);

		for(i=2;i<(u8DataLength + 2);i++)
			u8Buffer[i] = u8Bytes[i - 2];
		ret = MI2C_uddtMasterTx(I2C1,HEEPROM_SLA_ADDR,u8Buffer,(u8DataLength + 2),MI2C_WITH_STOP,MI2C_FIRST_START);
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t HEEPROM_uddtReadByte(uint8 u8Addr,uint8 *u8DataOut,uint8 u8DataLength)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(u8DataOut != NULL_PTR)
	{
		uint8 u8Buffer[2];
		u8Buffer[0] = (uint8)(u8Addr>>8);
		u8Buffer[1] = (uint8)(u8Addr);


		ret = MI2C_uddtMasterTx(I2C1,HEEPROM_SLA_ADDR,u8Buffer,2,MI2C_WITHOUT_STOP,MI2C_FIRST_START);
		//if(ret != UAPI_OK) return ret;
		ret = MI2C_uddtMasterRx(I2C1, HEEPROM_SLA_ADDR, u8DataOut, u8DataLength, MI2C_WITH_STOP, MI2C_REPEATED_START);
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}
