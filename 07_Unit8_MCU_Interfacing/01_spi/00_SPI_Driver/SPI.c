/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : SPI.c
// Date          : Jan 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#include "SPI.h"

static void(*P_IRQ_Callback[2])(MSPI_IRQ_SRC uddtIRQCfg);

COMMON_uddtApiState_t  MSPI_uddtInit(MSPI_uddtCfg_t *SPIcfg)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(SPIcfg != NULL_PTR)
	{
		//temp variable for registers for safety
		uint16 u16CR1Temp = 0 , u16CR2Temp = 0;

		ret = MSPI_uddtReset(SPIcfg->SPIx);
		if(ret != UAPI_OK) return ret;

		if(SPIcfg->SPIx == SPI1)
		{
			ret = MRCC_uddtEnablePeripheral(MRCC_SPI1);
			if(ret != UAPI_OK) return ret;
		}
		else if(SPIcfg->SPIx == SPI2)
		{
			ret = MRCC_uddtEnablePeripheral(MRCC_SPI2);
			if(ret != UAPI_OK) return ret;
		}
		else{ret = UAPI_INVALID_PARM;}

		//master or slave
		u16CR1Temp |= SPIcfg->u16DeviceMode;

		//bus mode
		u16CR1Temp |= SPIcfg->u16BusMode;

		//frame mode
		u16CR1Temp |= SPIcfg->u16FrameFormat;

		//data size
		u16CR1Temp |= SPIcfg->u16DataSize;

		//clk polarity
		u16CR1Temp |= SPIcfg->u16ClkPolarity;

		//clk phase
		u16CR1Temp |= SPIcfg->u16ClkPhase;

		// nss
		if(SPIcfg->u16NSS == MSPI_NSS_HW_MASTER_ENABLE_SS_OUTPUT)
		{
			u16CR2Temp |= SPIcfg->u16NSS;
		}
		else if(MSPI_NSS_HW_MASTER_DISABLE_SS_OUTPUT)
		{
			u16CR2Temp &= SPIcfg->u16NSS;
		}
		else
		{
			u16CR1Temp |= SPIcfg->u16NSS;
		}

		//prescaler
		u16CR1Temp |= SPIcfg->u16Prescaler;

		if(SPIcfg->u16IRQStatus != MSPI_IRQ_MASKED)
		{
			//spi IRQ enable
			u16CR2Temp |= SPIcfg->u16IRQStatus;
			if(SPIcfg->SPIx == SPI1)
			{
				ret = MNVIC_uddtEnableIRQ(MNVIC_SPI1_IRQ);
				if(ret != UAPI_OK) return ret;
				P_IRQ_Callback[0] = SPIcfg->P_IRQ_Callback;
			}
			else if(SPIcfg->SPIx == SPI2)
			{
				ret = MNVIC_uddtEnableIRQ(MNVIC_SPI2_IRQ);
				if(ret != UAPI_OK) return ret;
				P_IRQ_Callback[1] = SPIcfg->P_IRQ_Callback;
			}
			else{ret = UAPI_INVALID_PARM;}
		}
		else{/* Do Nothing */};

		//enable spi
		u16CR1Temp |= (0x1U<<6);
		//assign registers with the values
		SPIcfg->SPIx->CR1 = u16CR1Temp;
		SPIcfg->SPIx->CR2 = u16CR2Temp;

	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}
COMMON_uddtApiState_t  MSPI_uddtReset(SPI_registerMap_t *SPIx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(SPIx != NULL_PTR)
	{
		if(SPIx == SPI1)
		{
			ret = MRCC_uddtResetPeripheral(MRCC_SPI1);
			if(ret != UAPI_OK) return ret;
			ret = MNVIC_uddtDisableIRQ(MNVIC_SPI1_IRQ);
			if(ret != UAPI_OK) return ret;
		}
		else if(SPIx == SPI2)
		{
			ret = MRCC_uddtResetPeripheral(MRCC_SPI2);
			if(ret != UAPI_OK) return ret;
			ret = MNVIC_uddtDisableIRQ(MNVIC_SPI2_IRQ);
			if(ret != UAPI_OK) return ret;
		}
		else{ret = UAPI_INVALID_PARM;}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}
COMMON_uddtApiState_t  MSPI_uddtGpioSetPins(MSPI_uddtCfg_t *SPIcfg)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(SPIcfg != NULL_PTR)
	{
		MGPIO_uddtPinConfig_t pinCfg;
		if(SPIcfg->SPIx == SPI1)
		{
			// PA4 : NSS
			// PA5 : SCK
			// PA6 : MISO
			// PA7 : MOSI
			pinCfg.GPIOx = GPIOA;
			pinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
			pinCfg.uddtPinNumber = MGPIO_PIN4;
			if(SPIcfg->u16DeviceMode == MSPI_DEVICE_MODE_MASTER)
			{
				//PA4 : NSS
				switch(SPIcfg->u16NSS)
				{
				case MSPI_NSS_HW_MASTER_ENABLE_SS_OUTPUT :
				{
					pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
					ret = MGPIO_uddtInitPin(&pinCfg);
					if(ret != UAPI_OK) return ret;
					break;
				}
				case (uint16)MSPI_NSS_HW_MASTER_DISABLE_SS_OUTPUT:
				{
					pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
					ret = MGPIO_uddtInitPin(&pinCfg);
					if(ret != UAPI_OK) return ret;
					break;
				}
				default : ret = UAPI_INVALID_PARM;
				}

				//PA5 : SCK
				pinCfg.uddtPinNumber = MGPIO_PIN5;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PA6 : MISO
				pinCfg.uddtPinNumber = MGPIO_PIN6;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PA7 : MOSI
				pinCfg.uddtPinNumber = MGPIO_PIN7;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

			}
			else if(SPIcfg->u16DeviceMode == MSPI_DEVICE_MODE_SLAVE)
			{
				//PA4 : NSS
				if(SPIcfg->u16NSS == MSPI_NSS_HW_SLAVE)
				{
					pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
					ret = MGPIO_uddtInitPin(&pinCfg);
					if(ret != UAPI_OK) return ret;
				}else{/*Do Nothing*/}

				//PA5 : SCK
				pinCfg.uddtPinNumber = MGPIO_PIN5;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PA6 : MISO
				pinCfg.uddtPinNumber = MGPIO_PIN6;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PA7 : MOSI
				pinCfg.uddtPinNumber = MGPIO_PIN7;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

			}
			else{ret = UAPI_INVALID_PARM;}


		}
		else if(SPIcfg->SPIx == SPI2)
		{
			// PB12 : NSS
			// PB13 : SCK
			// PB14 : MISO
			// PB15 : MOSI

			pinCfg.GPIOx = GPIOB;
			pinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
			pinCfg.uddtPinNumber = MGPIO_PIN12;
			if(SPIcfg->u16DeviceMode == MSPI_DEVICE_MODE_MASTER)
			{
				//PB12 : NSS
				switch(SPIcfg->u16NSS)
				{
				case MSPI_NSS_HW_MASTER_ENABLE_SS_OUTPUT :
				{
					pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
					ret = MGPIO_uddtInitPin(&pinCfg);
					if(ret != UAPI_OK) return ret;
					break;
				}
				case (uint16)MSPI_NSS_HW_MASTER_DISABLE_SS_OUTPUT :
				{
					pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
					ret = MGPIO_uddtInitPin(&pinCfg);
					if(ret != UAPI_OK) return ret;
					break;
				}
				default : ret = UAPI_INVALID_PARM;
				}

				//PB13 : SCK
				pinCfg.uddtPinNumber = MGPIO_PIN13;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PB14 : MISO
				pinCfg.uddtPinNumber = MGPIO_PIN14;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PB15 : MOSI
				pinCfg.uddtPinNumber = MGPIO_PIN15;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

			}
			else if(SPIcfg->u16DeviceMode == MSPI_DEVICE_MODE_SLAVE)
			{
				//PB12 : NSS
				if(SPIcfg->u16NSS == MSPI_NSS_HW_SLAVE)
				{
					pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
					ret = MGPIO_uddtInitPin(&pinCfg);
					if(ret != UAPI_OK) return ret;
				}else{/*Do Nothing*/}

				//PB13 : SCK
				pinCfg.uddtPinNumber = MGPIO_PIN13;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PB14 : MISO
				pinCfg.uddtPinNumber = MGPIO_PIN14;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

				//PB15 : MOSI
				pinCfg.uddtPinNumber = MGPIO_PIN15;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;

			}
			else{ret = UAPI_INVALID_PARM;}


		}
		else{ret = UAPI_INVALID_PARM;}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t  MSPI_uddtSendData(MSPI_uddtCfg_t *SPIcfg , uint16 *pu16Buffer)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((SPIcfg != NULL_PTR) && (pu16Buffer != NULL_PTR))
	{
		if(SPIcfg->u16IRQStatus == MSPI_IRQ_MASKED)
			while(!(SPIcfg->SPIx->SR & MSPI_SR_TXE));

		SPIcfg->SPIx->DR = *pu16Buffer;
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}
COMMON_uddtApiState_t  MSPI_uddtReceiveData(MSPI_uddtCfg_t *SPIcfg, uint16 *pu16Buffer)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((SPIcfg != NULL_PTR) && (pu16Buffer != NULL_PTR))
	{
		if(SPIcfg->u16IRQStatus == MSPI_IRQ_MASKED)
			while(!(SPIcfg->SPIx->SR & MSPI_SR_RXNE));

		*pu16Buffer = SPIcfg->SPIx->DR;
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t MSPI_uddtTxRxData(MSPI_uddtCfg_t *SPIcfg,uint16 *pu16Buffer)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((SPIcfg != NULL_PTR) && (pu16Buffer != NULL_PTR))
	{
		if(SPIcfg->u16IRQStatus == MSPI_IRQ_MASKED)
			while(!(SPIcfg->SPIx->SR & MSPI_SR_TXE));
		SPIcfg->SPIx->DR = *pu16Buffer;
		if(SPIcfg->u16IRQStatus == MSPI_IRQ_MASKED)
			while(!(SPIcfg->SPIx->SR & MSPI_SR_RXNE));

		*pu16Buffer = SPIcfg->SPIx->DR;
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

//----------------------------------------
//================ IRQ ===================
//----------------------------------------

void SPI1_IRQHandler(void)
{
	if(NULL_PTR != P_IRQ_Callback[0])
	{
		MSPI_IRQ_SRC   uddtIRQCfg;
		uddtIRQCfg.TXE  = ((SPI1->SR & (1<<1)) >> 1);
		uddtIRQCfg.RXNE = ((SPI1->SR & (1<<0)) >> 0);
		uddtIRQCfg.ERRI = ((SPI1->SR & (1<<4)) >> 4);
		P_IRQ_Callback[0](uddtIRQCfg);
	}
	else{/*Do Nothing*/}
}

void SPI2_IRQHandler(void)
{
	if(NULL_PTR != P_IRQ_Callback[1])
	{
		MSPI_IRQ_SRC   uddtIRQCfg;
		uddtIRQCfg.TXE  = ((SPI2->SR & (1<<1)) >> 1);
		uddtIRQCfg.RXNE = ((SPI2->SR & (1<<0)) >> 0);
		uddtIRQCfg.ERRI = ((SPI2->SR & (1<<4)) >> 4);
		P_IRQ_Callback[1](uddtIRQCfg);
	}
	else{/*Do Nothing*/}
}








