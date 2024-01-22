/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : UART.c
// Date          : Jan 21, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#include "UART.h"


static void(*p_IRQCallback[3])(void);

/*=============================================================================================
 * @Function Name : MUSART_uddtInit
 * @Brief         : Initializes the USART module with the specified configuration.
 * @Param [in]    : UARTcfg - Pointer to the configuration structure for USART initialization.
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MUSART_uddtInit(MUSART_uddtCfg_t *UARTcfg)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(UARTcfg != NULL_PTR)
	{
		uint32 pclk=0,BRR=0;
		if(UARTcfg->UARTx == USART1)
		{
			ret = MRCC_uddtEnablePeripheral(MRCC_USART1);
			if(ret != UAPI_OK) return ret;
		}
		else if(UARTcfg->UARTx == USART2)
		{
			ret = MRCC_uddtEnablePeripheral(MRCC_USART2);
			if(ret != UAPI_OK) return ret;
		}
		else if(UARTcfg->UARTx == USART3)
		{
			ret = MRCC_uddtEnablePeripheral(MRCC_USART3);
			if(ret != UAPI_OK) return ret;

		}
		else
		{
			ret = UAPI_INVALID_PARM; return ret;
		}

		UARTcfg->UARTx->CR1 |=(1<<13);
		UARTcfg->UARTx->CR1 |= UARTcfg->u8TransferCtl;
		UARTcfg->UARTx->CR1 |= UARTcfg->u8PayloadLength;
		UARTcfg->UARTx->CR1 |= UARTcfg->u8Parity;
		UARTcfg->UARTx->CR2 |= UARTcfg->u8StopBits;
		UARTcfg->UARTx->CR3 |= UARTcfg->u8HwFlowCtl;

		if(UARTcfg->UARTx == USART1)
		{
			ret = MRCC_uddtGetAbp2Freq(&pclk);
			if(ret != UAPI_OK) return ret;
		}
		else
		{
			ret = MRCC_uddtGetAbp1Freq(&pclk);
			if(ret != UAPI_OK) return ret;
		}

		BRR = UART_BRR_REG(pclk,UARTcfg->u32BaudRate);
		UARTcfg->UARTx->BRR = BRR;

		if(UARTcfg->u8IRQStatus != MUSART_IRQ_MASKED)
		{
			UARTcfg->UARTx->CR1 |= (UARTcfg->u8IRQStatus);
			if(UARTcfg->UARTx == USART1)
			{
				ret = MNVIC_uddtEnableIRQ(MNVIC_USART1_IRQ);
				if(ret != UAPI_OK) return ret;
				p_IRQCallback[0] = UARTcfg->pIRQCallback;
			}
			else if(UARTcfg->UARTx == USART2)
			{
				ret = MNVIC_uddtEnableIRQ(MNVIC_USART2_IRQ);
				if(ret != UAPI_OK) return ret;
				p_IRQCallback[1] = UARTcfg->pIRQCallback;
			}
			else if(UARTcfg->UARTx == USART3)
			{
				ret= MNVIC_uddtEnableIRQ(MNVIC_USART3_IRQ);
				if(ret != UAPI_OK) return ret;
				p_IRQCallback[2] = UARTcfg->pIRQCallback;
			}
			else
			{
				ret = UAPI_INVALID_PARM; return ret;
			}
		}
		else
		{
			ret = UAPI_OK;
		}

	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MUSART_uddtReset
 * @Brief         : Resets the USART module.
 * @Param [in]    : UARTx - Pointer to the USART register map for the target USART module.
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MUSART_uddtReset(USART_registerMap_t *UARTx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(UARTx != NULL_PTR)
	{
		if(UARTx == USART1)
		{
			ret = MNVIC_uddtDisableIRQ(MNVIC_USART1_IRQ);
			if(ret != UAPI_OK) return ret;
			ret = MRCC_uddtResetPeripheral(MRCC_USART1);
			if(ret != UAPI_OK) return ret;
		}
		else if(UARTx == USART2)
		{
			ret = MNVIC_uddtDisableIRQ(MNVIC_USART2_IRQ);
			if(ret != UAPI_OK) return ret;
			ret = MRCC_uddtResetPeripheral(MRCC_USART2);
			if(ret != UAPI_OK) return ret;
		}
		else if(UARTx == USART3)
		{
			ret = MNVIC_uddtDisableIRQ(MNVIC_USART3_IRQ);
			if(ret != UAPI_OK) return ret;
			ret = MRCC_uddtResetPeripheral(MRCC_USART3);
			if(ret != UAPI_OK) return ret;
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MUSART_uddtGpioSetPins
 * @Brief         : Sets the GPIO pins for the USART module.
 * @Param [in]    : UARTcfg - Pointer to the configuration structure for USART initialization.
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MUSART_uddtGpioSetPins(MUSART_uddtCfg_t *UARTcfg)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(UARTcfg != NULL_PTR)
	{
		MGPIO_uddtPinConfig_t pinCfg;
		if(UARTcfg->UARTx == USART1)
		{
			pinCfg.GPIOx = GPIOA;
			pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
			pinCfg.uddtPinNumber = MGPIO_PIN9;
			pinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
			ret = MGPIO_uddtInitPin(&pinCfg);
			if(ret != UAPI_OK) return ret;
			pinCfg.uddtPinMode = MGPIO_INPUT_AF_MODE;
			pinCfg.uddtPinNumber = MGPIO_PIN10;
			ret = MGPIO_uddtInitPin(&pinCfg);
			if(ret != UAPI_OK) return ret;

			if(UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_CTS || UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS_CTS)
			{
				pinCfg.uddtPinNumber = MGPIO_PIN11;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;
			}
			else{/* Do Nothing */};

			if(UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS || UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS_CTS)
			{
				pinCfg.uddtPinNumber = MGPIO_PIN12;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;
			}
			else{/* Do Nothing */};
		}
		else if(UARTcfg->UARTx == USART2)
		{
			pinCfg.GPIOx = GPIOA;
			pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
			pinCfg.uddtPinNumber = MGPIO_PIN2;
			pinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
			ret = MGPIO_uddtInitPin(&pinCfg);
			if(ret != UAPI_OK) return ret;
			pinCfg.uddtPinMode = MGPIO_INPUT_AF_MODE;
			pinCfg.uddtPinNumber = MGPIO_PIN3;
			ret = MGPIO_uddtInitPin(&pinCfg);
			if(ret != UAPI_OK) return ret;

			if(UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_CTS || UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS_CTS)
			{
				pinCfg.uddtPinNumber = MGPIO_PIN0;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;
			}
			else{/* Do Nothing */};

			if(UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS || UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS_CTS)
			{
				pinCfg.uddtPinNumber = MGPIO_PIN1;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;
			}
			else{/* Do Nothing */};
		}
		else if(UARTcfg->UARTx == USART3)
		{
			pinCfg.GPIOx = GPIOB;
			pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
			pinCfg.uddtPinNumber = MGPIO_PIN10;
			pinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
			ret = MGPIO_uddtInitPin(&pinCfg);
			if(ret != UAPI_OK) return ret;
			pinCfg.uddtPinMode = MGPIO_INPUT_AF_MODE;
			pinCfg.uddtPinNumber = MGPIO_PIN11;
			ret = MGPIO_uddtInitPin(&pinCfg);
			if(ret != UAPI_OK) return ret;

			if(UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_CTS || UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS_CTS)
			{
				pinCfg.uddtPinNumber = MGPIO_PIN13;
				pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;
			}
			else{/* Do Nothing */};

			if(UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS || UARTcfg->u8HwFlowCtl == MUSART_HWFLOW_RTS_CTS)
			{
				pinCfg.uddtPinNumber = MGPIO_PIN14;
				pinCfg.uddtPinMode = MGPIO_OUTPUT_AF_PP_MODE;
				ret = MGPIO_uddtInitPin(&pinCfg);
				if(ret != UAPI_OK) return ret;
			}
			else{/* Do Nothing */};
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MUSART_uddtSendData
 * @Brief         : Sends data using USART communication.
 * @Param [in]    : UARTcfg - Pointer to the configuration structure for USART initialization.
 * @Param [in]    : pu16Buffer - Pointer to the data buffer to be sent.
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MUSART_uddtSendData(MUSART_uddtCfg_t *UARTcfg, uint16 *pu16Buffer)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if( (UARTcfg != NULL_PTR) && (pu16Buffer != NULL_PTR))
	{
		if(UARTcfg->u8IRQStatus == MUSART_IRQ_MASKED)
			while(!(UARTcfg->UARTx->SR & 1<< 7));

		if(UARTcfg->u8PayloadLength == MUSART_PAYLOAD_LEN_9B)
		{
			UARTcfg->UARTx->DR = (*pu16Buffer &(uint16)0x01FF);
			ret = UAPI_OK;
		}
		else
		{
			UARTcfg->UARTx->DR = (*pu16Buffer &(uint8)0xFF);
			ret = UAPI_OK;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MUSART_uddtReceiveData
 * @Brief         : Receives data using USART communication.
 * @Param [in]    : UARTcfg - Pointer to the configuration structure for USART initialization.
 * @Param [out]   : pu16Buffer - Pointer to the buffer to store received data.
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MUSART_uddtReceiveData(MUSART_uddtCfg_t *UARTcfg, uint16 *pu16Buffer)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if( (UARTcfg != NULL_PTR) && (pu16Buffer != NULL_PTR))
	{
		if(UARTcfg->u8IRQStatus == MUSART_IRQ_MASKED)
			while(!(UARTcfg->UARTx->SR & 1<< 5));
		if(UARTcfg->u8PayloadLength == MUSART_PAYLOAD_LEN_9B)
		{
			if(UARTcfg->u8Parity == MUSART_PARITY_NONE)
			{
				*((uint16 *)pu16Buffer) = UARTcfg->UARTx->DR;
			}
			else
			{
				*((uint16 *)pu16Buffer) = (UARTcfg->UARTx->DR&(uint8)0xFF);
			}
			ret = UAPI_OK;
		}
		else
		{
			if(UARTcfg->u8Parity == MUSART_PARITY_NONE)
			{
				*((uint16 *)pu16Buffer) = (UARTcfg->UARTx->DR&(uint8)0xFF);
			}
			else
			{
				*((uint16 *)pu16Buffer) = (UARTcfg->UARTx->DR&(uint8)0x7F);
			}
			ret = UAPI_OK;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MUSART_uddtWaitTc
 * @Brief         : Waits until transmission is complete (TC flag is set).
 * @Param [in]    : UARTx - Pointer to the USART register map for the target USART module.
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MUSART_uddtWaitTc(USART_registerMap_t *UARTx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(UARTx != NULL_PTR)
	{
		while(!(UARTx->SR & 1<<6));
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}


/*IRQ*/


void USART1_IRQHandler(void){

	MNVIC_uddtResetPendingIRQ(MNVIC_USART1_IRQ);
	if(p_IRQCallback[0] != NULL_PTR){
		p_IRQCallback[0]();
	}
	else{ /* Do Nothing */ }
}

void USART2_IRQHandler(void){
	MNVIC_uddtResetPendingIRQ(MNVIC_USART2_IRQ);
	if(p_IRQCallback[1] != NULL_PTR){
		p_IRQCallback[1]();
	}
	else{ /* Do Nothing */ }
}

void USART3_IRQHandler(void){
	MNVIC_uddtResetPendingIRQ(MNVIC_USART3_IRQ);
	if(p_IRQCallback[2] != NULL_PTR){
		p_IRQCallback[2]();
	}
	else{ /* Do Nothing */ }
}



