/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : SPI.h
// Date          : Jan 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef MCAL_INC_SPI_H_
#define MCAL_INC_SPI_H_


#include "stm32f103x6.h"
#include "GPIO.h"
#include "NVIC.h"
#include "RCC.h"

//---------------------------------------------------
//================ Generic Macros ===================
//---------------------------------------------------

#define MSPI_SR_TXE			((uint8)0x02)
#define MSPI_SR_RXNE		((uint8)0x01)

//---------------------------------------------------
//============ Configuration Structure ==============
//---------------------------------------------------


typedef struct
{
	uint8 TXE:1; 	   /* TX buffer is empty interrupt */
	uint8 RXNE:1; 	   /* RX buffer is not empty interrupt */
	uint8 ERRI:1; 	   /* error interrupt */
	uint8 reserved:5;
}MSPI_IRQ_SRC;

/* Configuration structure */

typedef struct
{
	SPI_registerMap_t		*SPIx;
	uint16 		u16DeviceMode; 			/* @REF DeviceMode Define */
	uint16		u16BusMode;				/* @REF BusMode Define */
	uint16		u16FrameFormat;			/* @REF FrameFormat Define */
	uint16		u16DataSize;			/* @REF DataSize Define */
	uint16		u16ClkPolarity;			/* @REF ClkPolarity Define */
	uint16	    u16ClkPhase;			/* @REF ClkPhase Define */
	uint16		u16NSS;					/* @REF NSS Define */
	uint16		u16Prescaler;			/* @REF Prescaler Define */
	uint16		u16IRQStatus;			/* @REF IRQStatus Define */

	void(*P_IRQ_Callback)(MSPI_IRQ_SRC uddtIRQCfg);

}MSPI_uddtCfg_t;

//---------------------------------------------------
//=============== Reference Macros ==================
//---------------------------------------------------


/* @REF DeviceMode Define */

#define MSPI_DEVICE_MODE_SLAVE			(0x00000000U)
#define MSPI_DEVICE_MODE_MASTER			(0x1U<<2)

/* @REF BusMode Define */

#define MSPI_BUS_MODE_2LINES  			(0x00000000U)
#define MSPI_BUS_MODE_2LINES_RX			(0x1U<<10)
#define MSPI_BUS_MODE_1LINES_RX			(0x1U<<15)
#define MSPI_BUS_MODE_1LINES_TX			((0x1U<<15)|(0x1U<<14))

/* @REF FrameFormat Define */

#define MSPI_FRAME_FORMAT_MSB			(0x00000000U)
#define MSPI_FRAME_FORMAT_LSB			(0x1U<<7)

/* @REF DataSize Define */

#define MSPI_DATA_SIZE_8B				(0x00000000U)
#define MSPI_DATA_SIZE_16B				(0x1U<<11)

/* @REF ClkPolarity Define */

#define MSPI_CLKPOLARITY_IDLE_LOW		(0x00000000U)
#define MSPI_CLKPOLARITY_IDLE_HIGH		(0x1U<<1)

/* @REF ClkPhase Define */

#define MSPI_CLKPHASE_EDGE1				(0x00000000U)
#define MSPI_CLKPHASE_EDGE2				(0x1U<<0)

/* @REF NSS Define */

// Hardware
#define MSPI_NSS_HW_SLAVE						(0x00000000U)
#define MSPI_NSS_HW_MASTER_ENABLE_SS_OUTPUT		(0x1U<<2)
#define MSPI_NSS_HW_MASTER_DISABLE_SS_OUTPUT	~(0x1U<<2)
//Software
#define MSPI_NSS_SW_RESET				(0x1U<<9)
#define MSPI_NSS_SW_SET					((0x1U<<9)|(0x1U<<8))

/* @REF Prescaler Define */

#define MSPI_PRESCALER_BY_2				(0x00000000U)
#define MSPI_PRESCALER_BY_4				(0b001U<<3)
#define MSPI_PRESCALER_BY_8				(0b010U<<3)
#define MSPI_PRESCALER_BY_16			(0b011U<<3)
#define MSPI_PRESCALER_BY_32			(0b100U<<3)
#define MSPI_PRESCALER_BY_64			(0b101U<<3)
#define MSPI_PRESCALER_BY_128			(0b110U<<3)
#define MSPI_PRESCALER_BY_256			(0b111U<<3)

/* @REF IRQStatus Define */

#define MSPI_IRQ_MASKED					(0x00000000U)
#define MSPI_IRQ_TXEIE					(0x1U<<7)
#define MSPI_IRQ_RXNEIE					(0x1U<<6)
#define MSPI_IRQ_ERRIE					(0x1U<<5)


//---------------------------------------------------
//================ APIs Supported ===================
//---------------------------------------------------

/*=============================================================================================
* @Function Name : MSPI_uddtInit
* @Brief         : Initializes the SPI module with the specified configuration.
* @Param [in]    : SPIcfg - Pointer to the configuration structure for SPI initialization.
* @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MSPI_uddtInit(MSPI_uddtCfg_t *SPIcfg);

/*=============================================================================================
* @Function Name : MSPI_uddtReset
* @Brief         : Resets the SPI module.
* @Param [in]    : SPIx - Pointer to the SPI register map for the target SPI module.
* @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MSPI_uddtReset(SPI_registerMap_t *SPIx);

/*=============================================================================================
* @Function Name : MSPI_uddtGpioSetPins
* @Brief         : Sets the GPIO pins for the SPI module.
* @Param [in]    : SPIcfg - Pointer to the configuration structure for SPI GPIO pins.
* @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MSPI_uddtGpioSetPins(MSPI_uddtCfg_t *SPIcfg);

/*=============================================================================================
* @Function Name : MSPI_uddtSendData
* @Brief         : Sends data using SPI communication.
* @Param [in]    : SPIcfg - Pointer to the configuration structure for SPI communication.
* @Param [in]    : pu16Buffer - Pointer to the data buffer to be sent.
* @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MSPI_uddtSendData(MSPI_uddtCfg_t *SPIcfg, uint16 *pu16Buffer);

/*=============================================================================================
* @Function Name : MSPI_uddtReceiveData
* @Brief         : Receives data using SPI communication.
* @Param [in]    : SPIcfg - Pointer to the configuration structure for SPI communication.
* @Param [out]   : pu16Buffer - Pointer to the buffer to store received data.
* @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MSPI_uddtReceiveData(MSPI_uddtCfg_t *SPIcfg, uint16 *pu16Buffer);

/*=============================================================================================
* @Function Name : MSPI_uddtTxRxData
* @Brief         : Transmits and receives data simultaneously using SPI communication.
* @Param [in]    : SPIcfg - Pointer to the configuration structure for SPI communication.
* @Param [in]    : pu16Buffer - Pointer to the data buffer to be transmitted and received.
* @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MSPI_uddtTxRxData(MSPI_uddtCfg_t *SPIcfg, uint16 *pu16Buffer);




#endif /* MCAL_INC_SPI_H_ */
