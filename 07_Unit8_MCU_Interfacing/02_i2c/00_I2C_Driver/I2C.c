/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : I2C.c
// Date          : Jan 30, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#include "I2C.h"

#define I2C1_INDEX	0
#define I2C2_INDEX	1

static MI2C_uddtCfg_t Global_I2C_Config[2];



COMMON_uddtApiState_t  MI2C_uddtInit(MI2C_uddtCfg_t *uddtI2cCfg)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(uddtI2cCfg != NULL_PTR)
	{
		uint16 u16TempReg=0,u16FreqRange=0,u16Res=0;
		uint32 u32Pclk=0;
		if(uddtI2cCfg->I2Cx == I2C1)
		{
			ret = MRCC_uddtEnablePeripheral(MRCC_I2C1);
			if(ret != UAPI_OK) return ret;
			Global_I2C_Config[I2C1_INDEX] = *uddtI2cCfg;
		}
		else if(uddtI2cCfg->I2Cx == I2C2)
		{
			ret = MRCC_uddtEnablePeripheral(MRCC_I2C2);
			if(ret != UAPI_OK) return ret;
			Global_I2C_Config[I2C2_INDEX] = *uddtI2cCfg;
		}
		else {ret = UAPI_INVALID_PARM; return ret;}

		if(uddtI2cCfg->u32I2cMode == MI2C_MODE_I2C)
		{
			/*----------------------- INIT Timing ------------------*/

			u16TempReg = uddtI2cCfg->I2Cx->CR2;
			u16TempReg &= ~(I2C_CR2_FREQ_Msk);
			ret = MRCC_uddtGetAbp1Freq(&u32Pclk);
			if(ret != UAPI_OK) return ret;
			u16FreqRange = (uint16)(u32Pclk/1000000);
			u16TempReg |= u16FreqRange;
			uddtI2cCfg->I2Cx->CR2 = u16TempReg;

			// configure the clock control register
			// disable the selected I2C peripheral to configure time

			uddtI2cCfg->I2Cx->CR1 &= ~(I2C_CR1_PE);

			u16TempReg = 0;

			// configure speed in standard mode

			if( (uddtI2cCfg->u32ClkSpeed == MI2C_SCLK_SM_50K) || (uddtI2cCfg->u32ClkSpeed == MI2C_SCLK_SM_100K))
			{
				// standard mode speed calculate
				// Tclk/2 = CRR * Tpclk1
				// CRR = Tclk / (2 * Tpclk1)
				// CRR = Fpclk1 / (2 * I2C_ClockFrequency)

				u16Res = (uint16)(u32Pclk / (uddtI2cCfg->u32ClkSpeed << 1));
				u16TempReg |= u16Res;

				// Write to I2Cx CCR
				uddtI2cCfg->I2Cx->CCR = u16TempReg;

				/*----------------------- I2C_TRISE Configuration ------------------*/
				// for instance : in SM mode the maximum allowed SCL rise time is 1000 ns
				// if in the I2C_CR2 register the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
				// therefore the TRISE[5:0] bits must be programmed with 09h

				uddtI2cCfg->I2Cx->TRISE = u16FreqRange + 1;
			}
			else {ret = UAPI_INVALID_PARM; return ret;}

			/*----------------------- I2Cx CR1 Configuration ------------------*/

			// Get the I2Cx CR1 value
			u16TempReg = uddtI2cCfg->I2Cx->CR1;

			u16TempReg |=(uint16)(uddtI2cCfg->u32AckCtrl | uddtI2cCfg->u32GenralCallAddrDetection
					| uddtI2cCfg->u32ClkStretchStates | uddtI2cCfg->u32I2cMode);

			// write I2Cx CR1
			uddtI2cCfg->I2Cx->CR1 = u16TempReg;

			/*----------------------- I2Cx OAR1 & OAR2 Configuration ------------------*/

			u16TempReg = 0;
			if(uddtI2cCfg->uddtSlaveAddr.u16EnableDualAddr == 1)
			{
				u16TempReg = I2C_OAR2_ENDUAL;
				u16TempReg |= uddtI2cCfg->uddtSlaveAddr.u16SecondarySlaveAddr << I2C_OAR2_ADD2_Pos;
				uddtI2cCfg->I2Cx->OAR2 = u16TempReg;
			}

			u16TempReg = 0;
			u16TempReg |= uddtI2cCfg->uddtSlaveAddr.u16PrimarySlaveAddr << 1;
			u16TempReg |= uddtI2cCfg->uddtSlaveAddr.u32I2cSlaveAddrMode;
			uddtI2cCfg->I2Cx->OAR1 = u16TempReg;
		}
		else {ret = UAPI_INVALID_PARM; return ret;}

		// Interrupt mode (slave mode)
		// check callback pointer != null
		if(uddtI2cCfg->P_IRQCallback != NULL_PTR)
		{
			// Enable IRQ
			uddtI2cCfg->I2Cx->CR2 |= (I2C_CR2_ITERREN);
			uddtI2cCfg->I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
			uddtI2cCfg->I2Cx->CR2 |= (I2C_CR2_ITBUFEN);

			if(uddtI2cCfg->I2Cx == I2C1)
			{
				ret = MNVIC_uddtEnableIRQ(MNVIC_I2C1_EV_IRQ);
				if(ret != UAPI_OK) return ret;
				ret = MNVIC_uddtEnableIRQ(MNVIC_I2C1_ER_IRQ);
				if(ret != UAPI_OK) return ret;
			}
			else if(uddtI2cCfg->I2Cx == I2C2)
			{
				ret = MNVIC_uddtEnableIRQ(MNVIC_I2C2_EV_IRQ);
				if(ret != UAPI_OK) return ret;
				ret = MNVIC_uddtEnableIRQ(MNVIC_I2C2_ER_IRQ);
				if(ret != UAPI_OK) return ret;
			}
			else{ret = UAPI_INVALID_PARM; return ret;}

			uddtI2cCfg->I2Cx->SR1 = 0;
			uddtI2cCfg->I2Cx->SR2 = 0;
		}

		// enable the selected I2C peripheral
		uddtI2cCfg->I2Cx->CR1 |= I2C_CR1_PE;

	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t  MI2C_uddtReset(I2C_registerMap_t *I2Cx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(I2Cx != NULL_PTR)
	{
		if(I2Cx == I2C1)
		{
			ret = MRCC_uddtResetPeripheral(MRCC_I2C1);
			if(ret != UAPI_OK) return ret;
			ret = MNVIC_uddtDisableIRQ(MNVIC_I2C1_EV_IRQ);
			if(ret != UAPI_OK) return ret;
			ret = MNVIC_uddtDisableIRQ(MNVIC_I2C1_ER_IRQ);
			if(ret != UAPI_OK) return ret;
		}
		else if(I2Cx == I2C2)
		{
			ret = MRCC_uddtResetPeripheral(MRCC_I2C2);
			if(ret != UAPI_OK) return ret;
			ret = MNVIC_uddtDisableIRQ(MNVIC_I2C2_EV_IRQ);
			if(ret != UAPI_OK) return ret;
			ret = MNVIC_uddtDisableIRQ(MNVIC_I2C2_ER_IRQ);
			if(ret != UAPI_OK) return ret;
		}
		else {ret = UAPI_INVALID_PARM; return ret;}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t  MI2C_uddtGpioSetPins(I2C_registerMap_t *I2Cx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(I2Cx != NULL_PTR)
	{
		MGPIO_uddtPinConfig_t PinCfg;
		if(I2Cx == I2C1)
		{
			// PB6 : I2C_SCL
			// PB7 : I2C_SDA

			PinCfg.uddtPinNumber = MGPIO_PIN6;
			PinCfg.GPIOx = GPIOB;
			PinCfg.uddtPinMode = MGPIO_OUTPUT_AF_OD_MODE;
			PinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
			ret = MGPIO_uddtInitPin(&PinCfg);
			if(ret != UAPI_OK) return ret;
			PinCfg.uddtPinNumber = MGPIO_PIN7;
			ret = MGPIO_uddtInitPin(&PinCfg);
			if(ret != UAPI_OK) return ret;
		}
		else if(I2Cx == I2C2)
		{
			// PB10 : I2C_SCL
			// PB11 : I2C_SDA

			PinCfg.uddtPinNumber = MGPIO_PIN10;
			PinCfg.GPIOx = GPIOB;
			PinCfg.uddtPinMode = MGPIO_OUTPUT_AF_OD_MODE;
			PinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
			ret = MGPIO_uddtInitPin(&PinCfg);
			if(ret != UAPI_OK) return ret;
			PinCfg.uddtPinNumber = MGPIO_PIN11;
			ret = MGPIO_uddtInitPin(&PinCfg);
			if(ret != UAPI_OK) return ret;
		}
		else {ret = UAPI_INVALID_PARM; return ret;}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t MI2C_uddtMasterTx(I2C_registerMap_t  *I2Cx , uint16 u16DesAddr , uint8 *u8Data , uint32 u32DataLen,
		MI2C_uddtStopBitCtrl_t uddtStopCtrl , MI2C_uddtStartBitCtrl_t uddtStartCtrl)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR) && (u8Data != NULL_PTR))
	{
		uint32 i;
		ret = MI2C_uddtGenrateStart(I2Cx,uddtStartCtrl,MI2C_ENABLE);
		if(ret != UAPI_OK) return ret;
		while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EV5));
		ret = MI2C_uddtSendSlaveAddr(I2Cx,MI2C_DIRECTION_TX,u16DesAddr);
		if(ret != UAPI_OK) return ret;
		while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EV6));
		while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EVENT_MASTER_BYTE_TX));

		for(i=0;i<u32DataLen;i++)
		{
			I2Cx->DR = u8Data[i];
			while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EV8));
		}
		while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EV8_1));

		if(uddtStopCtrl == MI2C_WITH_STOP)
		{
			ret = MI2C_uddtGenrateStop(I2Cx,MI2C_ENABLE);
			if(ret != UAPI_OK) return ret;
		}else{/*Do Nothing*/}

	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}

COMMON_uddtApiState_t MI2C_uddtMasterRx(I2C_registerMap_t  *I2Cx , uint16 u16DesAddr , uint8 *u8Data , uint32 u32DataLen,
		MI2C_uddtStopBitCtrl_t uddtStopCtrl , MI2C_uddtStartBitCtrl_t uddtStartCtrl)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR) && (u8Data != NULL_PTR))
	{
		uint32 i;
		ret = MI2C_uddtGenrateStart(I2Cx,uddtStartCtrl,MI2C_ENABLE);
		if(ret != UAPI_OK) return ret;
		while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EV5));
		ret = MI2C_uddtSendSlaveAddr(I2Cx,MI2C_DIRECTION_RX,u16DesAddr);
		if(ret != UAPI_OK) return ret;
		while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EV6));
		ret = MI2C_uddtAckCtrl(I2Cx,MI2C_ENABLE);
		if(ret != UAPI_OK) return ret;
		if(u32DataLen)
		{
			for(i=u32DataLen;i>1;i--)
			{
				while(!MI2C_uddtGetFlagStatus(I2Cx,MI2C_EV7));
				*u8Data = I2Cx->DR;
				u8Data++;
			}

			ret = MI2C_uddtAckCtrl(I2Cx,MI2C_DISABLE);
			if(ret != UAPI_OK) return ret;
		}else{ret = UAPI_INVALID_PARM;}

		if(uddtStopCtrl == MI2C_WITH_STOP)
		{
			ret = MI2C_uddtGenrateStop(I2Cx, MI2C_ENABLE);
			if(ret != UAPI_OK) return ret;
		}else{/*Do Nothing*/}

		uint8 u8Index = (I2C1 == I2Cx) ? I2C1_INDEX : I2C2_INDEX;

		if(Global_I2C_Config[u8Index].u32AckCtrl == MI2C_ACK_ENABLE){
			ret = MI2C_uddtAckCtrl(I2Cx,MI2C_ENABLE);
			if(ret != UAPI_OK) return ret;
		}
		else{/*Do Nothing*/}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}

COMMON_uddtApiState_t MI2C_uddtGenrateStart(I2C_registerMap_t  *I2Cx ,MI2C_uddtStartBitCtrl_t uddtStartCtrl,MI2C_uddtFunctionStatus_t uddtState)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR))
	{
		if(uddtStartCtrl != MI2C_REPEATED_START)
		{
			// Check if the bus is idle
			while(MI2C_uddtGetFlagStatus(I2Cx,MI2C_FLAG_BUSY));
		}

		if(uddtState != MI2C_DISABLE)
		{
			I2Cx->CR1 |= I2C_CR1_START;
			ret = UAPI_OK;
		}
		else
		{
			I2Cx->CR1 &= ~(I2C_CR1_START);
			ret = UAPI_OK;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}

MI2C_uddtFlagStatus_t MI2C_uddtGetFlagStatus(I2C_registerMap_t  *I2Cx ,MI2C_uddtFlags_t uddtFlag)
{
	MI2C_uddtFlagStatus_t uddtFlagStatus = MI2C_RESET;
	uint32 u32Flag1=0,u32Flag2=0,u32LastEvent=0;

	if(I2Cx != NULL_PTR)
	{
		switch(uddtFlag)
		{
		case MI2C_FLAG_BUSY:
		{
			if((I2Cx->SR2) & (I2C_SR2_BUSY))
				uddtFlagStatus = MI2C_SET;
			else
				uddtFlagStatus = MI2C_RESET;
			break;
		}
		case MI2C_EV5:
		{
			if((I2Cx->SR1) & (I2C_SR1_SB))
				uddtFlagStatus = MI2C_SET;
			else
				uddtFlagStatus = MI2C_RESET;
			break;
		}
		case MI2C_EV6:
		{
			if((I2Cx->SR1) & (I2C_SR1_ADDR))
				uddtFlagStatus = MI2C_SET;
			else
				uddtFlagStatus = MI2C_RESET;
			break;
		}
		case MI2C_EV7:
		{
			if((I2Cx->SR1) & (I2C_SR1_RXNE))
				uddtFlagStatus = MI2C_SET;
			else
				uddtFlagStatus = MI2C_RESET;
			break;
		}
		case MI2C_EV8:
		case MI2C_EV8_1:
		{
			if((I2Cx->SR1) & (I2C_SR1_TXE))
				uddtFlagStatus = MI2C_SET;
			else
				uddtFlagStatus = MI2C_RESET;
			break;
		}
		case MI2C_EVENT_MASTER_BYTE_TX:
		{
			u32Flag1 = I2Cx->SR1;
			u32Flag2 = I2Cx->SR2;
			u32Flag2 = u32Flag2 << 16;
			u32LastEvent = (u32Flag1 | u32Flag2) & ((uint32)0x00FFFFFF);
			if((u32LastEvent & uddtFlag) == uddtFlag)
				uddtFlagStatus = MI2C_SET;
			else
				uddtFlagStatus = MI2C_RESET;
			break;
		}

		}

	}
	else{/*Do Nothing*/}

	return uddtFlagStatus;
}


COMMON_uddtApiState_t MI2C_uddtSendSlaveAddr(I2C_registerMap_t  *I2Cx ,MI2C_uddtDirection_t uddtDirection , uint16 u16SlaAddr)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR))
	{
		u16SlaAddr = (u16SlaAddr << 1);
		if(uddtDirection != MI2C_DIRECTION_TX)
		{
			u16SlaAddr |= 1<<0;
			ret = UAPI_OK;
		}
		else
		{
			u16SlaAddr &= ~(1<<0);
			ret = UAPI_OK;
		}

		if(ret == UAPI_OK)
			I2Cx->DR = u16SlaAddr;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}


COMMON_uddtApiState_t MI2C_uddtGenrateStop (I2C_registerMap_t  *I2Cx ,MI2C_uddtFunctionStatus_t uddtState)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR))
	{
		if(uddtState != MI2C_DISABLE)
		{
			I2Cx->CR1 |= I2C_CR1_STOP;
			ret = UAPI_OK;
		}
		else
		{
			I2Cx->CR1 &= ~(I2C_CR1_STOP);
			ret = UAPI_OK;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}

COMMON_uddtApiState_t MI2C_uddtAckCtrl(I2C_registerMap_t *I2Cx,MI2C_uddtFunctionStatus_t uddtState)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR))
	{
		if(uddtState != MI2C_DISABLE)
		{
			I2Cx->CR1 |= I2C_CR1_ACK;
			ret = UAPI_OK;
		}
		else
		{
			I2Cx->CR1 &= ~(I2C_CR1_ACK_Msk);
			ret = UAPI_OK;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}



COMMON_uddtApiState_t MI2C_uddtSlaveTx(I2C_registerMap_t  *I2Cx , uint8 u8Data)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR))
	{
		I2Cx->DR = u8Data;
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}

COMMON_uddtApiState_t MI2C_uddtSlaveRx(I2C_registerMap_t  *I2Cx , uint8 *u8Data)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((I2Cx != NULL_PTR) && (u8Data != NULL_PTR))
	{
		*u8Data = (uint8)I2Cx->DR;
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}

void I2C1_EV_IRQHandler(void)
{

}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}
