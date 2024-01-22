/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : UART.h
// Date          : Jan 21, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef MCAL_INC_UART_H_
#define MCAL_INC_UART_H_

#include "stm32f103x6.h"
#include "RCC.h"
#include "NVIC.h"
#include "GPIO.h"


//---------------------------------------------------
//================ Generic Macros ===================
//---------------------------------------------------

#define USARTDIV(_PCLK_,_BAUD_)			    (uint32)(_PCLK_/(16*_BAUD_))
#define USARTDIV_MUL100(_PCLK_,_BAUD_)		(uint32)((25 * _PCLK_) / (4*_BAUD_))
#define MANTISSA_MUL100(_PCLK_,_BAUD_)		(uint32)(USARTDIV(_PCLK_,_BAUD_)*100)
#define MANTISSA(_PCLK_,_BAUD_)				(uint32)(USARTDIV(_PCLK_,_BAUD_))
#define DIV_FRACTION(_PCLK_,_BAUD_)			(uint32)(((USARTDIV_MUL100(_PCLK_,_BAUD_) - MANTISSA_MUL100(_PCLK_,_BAUD_)) *16)/100)
#define UART_BRR_REG(_PCLK_,_BAUD_)			((MANTISSA(_PCLK_,_BAUD_)) << 4)|((DIV_FRACTION(_PCLK_,_BAUD_)) &0xF)

//---------------------------------------------------
//============ Configuration Structure ==============
//---------------------------------------------------


typedef struct
{
	USART_registerMap_t    *UARTx;
	uint8				   u8TransferCtl; /* @ref : TransferCtl Define */
	uint32  			   u32BaudRate; /* @ref : BaudRate Define */
	uint8         		   u8PayloadLength; /* @ref : PayloadLength Define */
	uint8				   u8Parity; /* @ref : Parity Define */
	uint8  			       u8StopBits; /* @ref : StopBits Define */
	uint8			       u8HwFlowCtl; /* @ref : HwFlowCtl Define */
	uint8      	           u8IRQStatus; /* @ref : IRQStatus Define */
	void(*pIRQCallback)(void); /* IRQ Callback Function Pointer */
}MUSART_uddtCfg_t;


//---------------------------------------------------
//=============== Reference Macros ==================
//---------------------------------------------------

/* @ref : TransferCtl Define */

#define  MUSART_RX_ONLY     (uint32)(1<<3)
#define  MUSART_TX_ONLY		(uint32)(1<<2)
#define  MUSART_TX_RX       ((uint32)(1<<2|1<<3))

/* @ref : BaudRate Define */

#define MUSART_BAUDRATE_2400          2400
#define MUSART_BAUDRATE_9600          9600
#define MUSART_BAUDRATE_19200         19200
#define MUSART_BAUDRATE_57600         57600
#define MUSART_BAUDRATE_115200        115200
#define MUSART_BAUDRATE_230400        230400
#define MUSART_BAUDRATE_460800        460800
#define MUSART_BAUDRATE_921600        921600
#define MUSART_BAUDRATE_2250000       2250000
#define MUSART_BAUDRATE_4500000       4500000

/* @ref : PayloadLength Define */

#define MUSART_PAYLOAD_LEN_8B   (uint32)(0)
#define MUSART_PAYLOAD_LEN_9B	(uint32)(1<<12)

/* @ref : Parity Define */

#define MUSART_PARITY_NONE	   (uint32)(0)
#define MUSART_PARITY_EVEN	   (uint32)(1<<10)
#define MUSART_PARITY_ODD	   ((uint32)(1<<10|1<<9))

/* @ref : StopBits Define */

#define MUSART_STOPBITS_HALF     (uint32)(1<<12)
#define MUSART_STOPBITS_ONE	     (uint32)(0)
#define MUSART_STOPBITS_ONE_HALF (uint32)(3<<12)
#define MUSART_STOPBITS_TWO		 (uint32)(2<<12)

/* @ref : HwFlowCtl Define */

#define MUSART_HWFLOW_NONE		(uint32)(0)
#define MUSART_HWFLOW_RTS		(uint32)(1<<8)
#define MUSART_HWFLOW_CTS		(uint32)(1<<9)
#define MUSART_HWFLOW_RTS_CTS	(uint32)(1<<8 | 1<<9)

/* @ref : IRQStatus Define */

#define MUSART_IRQ_MASKED		 (uint32)(0)
#define MUSART_IRQ_UNMASK_TXE    (uint32)(1<<7)
#define MUSART_IRQ_UNMASK_TC     (uint32)(1<<6)
#define MUSART_IRQ_UNMASK_RXNEIE (uint32)(1<<5)
#define MUSART_IRQ_UNMASK_PE     (uint32)(1<<8)


//---------------------------------------------------
//================ APIs Supported ===================
//---------------------------------------------------

COMMON_uddtApiState_t  MUSART_uddtInit(MUSART_uddtCfg_t *UARTcfg);
COMMON_uddtApiState_t  MUSART_uddtReset(USART_registerMap_t *UARTx);
COMMON_uddtApiState_t  MUSART_uddtGpioSetPins(MUSART_uddtCfg_t *UARTcfg);

COMMON_uddtApiState_t  MUSART_uddtSendData(MUSART_uddtCfg_t *UARTcfg , uint16 *pu16Buffer);
COMMON_uddtApiState_t  MUSART_uddtReceiveData(MUSART_uddtCfg_t *UARTcfg, uint16 *pu16Buffer);

COMMON_uddtApiState_t MUSART_uddtWaitTc(USART_registerMap_t *UARTx);



#endif /* MCAL_INC_UART_H_ */
