/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : I2C.h
// Date          : Jan 30, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef MCAL_INC_I2C_H_
#define MCAL_INC_I2C_H_

#include "stm32f103x6.h"
#include "RCC.h"
#include "NVIC.h"
#include "GPIO.h"

//---------------------------------------------------
//================ Generic Macros ===================
//---------------------------------------------------





//---------------------------------------------------
//============ Configuration Structure ==============
//---------------------------------------------------


typedef struct
{
	uint16  u16EnableDualAddr;
	uint16  u16PrimarySlaveAddr;
	uint16  u16SecondarySlaveAddr;
	uint32  u32I2cSlaveAddrMode;	/* @REF : I2cSlaveAddrMode */
}MI2C_uddtSlaveAddr_t;


typedef enum
{
  	MI2C_EV_Stop,
	MI2C_ERROR_AF,
	MI2C_EV_ADDR_MATCHED,
	MI2C_EV_DATA_REQ, // the APP layer should send the data (I2C slave send data) in this state
	MI2C_EV_DATA_RCV  // the APP layer should read the data (I2C slave receive data) in this state
}MI2C_uddtSlaveState_t;


typedef enum
{
	MI2C_WITH_STOP,
	MI2C_WITHOUT_STOP
}MI2C_uddtStopBitCtrl_t;

typedef enum
{
	MI2C_FIRST_START,
	MI2C_REPEATED_START
}MI2C_uddtStartBitCtrl_t;

typedef enum
{
	MI2C_DISABLE,
	MI2C_ENABLE
}MI2C_uddtFunctionStatus_t;

typedef enum
{
	MI2C_RESET,
	MI2C_SET
}MI2C_uddtFlagStatus_t;

typedef enum
{
	MI2C_FLAG_BUSY,
	MI2C_EV5, 	// EV5:   SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	MI2C_EV6, 	// EV6:   ADDR=1, cleared by reading SR1 register followed by reading SR2
	MI2C_EV7,	// EV7:   RxNE=1 cleared by reading DR register
	MI2C_EV8,  	// EV8:   TxE=1, shift register not empty, data register empty, cleared by writing DR register
	MI2C_EV8_1, // EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR
	MI2C_EVENT_MASTER_BYTE_TX = ((uint32)0x00070080) /* TRA, BUSY, MSL, TXE flags */
}MI2C_uddtFlags_t;


typedef enum
{
	MI2C_DIRECTION_TX = 0,
	MI2C_DIRECTION_RX
}MI2C_uddtDirection_t;

typedef struct
{
	uint32						u32ClkSpeed; 				/* @REF : ClkSpeed 				  */
	uint32						u32ClkStretchStates;    	/* @REF : ClkStretchStates		  */
    uint32						u32I2cMode;					/* @REF : I2cMode		  		  */
    uint32						u32AckCtrl;					/* @REF : AckCtrl			      */
    uint32						u32GenralCallAddrDetection;	/* @REF : GenralCallAddrDetection */
    MI2C_uddtSlaveAddr_t		uddtSlaveAddr;
    I2C_registerMap_t			*I2Cx;
    void(*P_IRQCallback)(MI2C_uddtSlaveState_t state);

}MI2C_uddtCfg_t;


//---------------------------------------------------
//=============== Reference Macros ==================
//---------------------------------------------------

/* @REF : ClkSpeed
 * standard speed up to 100 KHZ
 * fast speed up to 400 KHZ
 * - to configure clock before enable the peripheral
 * I2C_CR2.FREQ[5:0]: peripheral clock frequency
 * - configure the clock control registers
 * 			thigh = CCR * TPCLK1
 * 			SM or FM
 * - configure the rise time register I2C_TRISE
 *
*/

#define MI2C_SCLK_SM_50K			(0x50000U)
#define MI2C_SCLK_SM_100K			(100000U)
#define MI2C_SCLK_SM_200K			(200000U) // Fast Mode Not Supported Yet
#define MI2C_SCLK_SM_400K			(400000U)

/* @REF : ClkStretchStates
 * I2C_CR1
 * BIT 7 NOSTRETCH : clock stretching disable (Slave Mode)
 * 0 : clock stretching enabled
 * 1 : clock stretching disabled
 *
*/

#define MI2C_STRETCHING_ENABLE			0x00000000U
#define MI2C_STRETCHING_DISABLE			I2C_CR1_NOSTRETCH

/* @REF : I2cMode
 * I2C_CR1
 * BIT 1 SMBUS : smbus mode
 * 0 : I2C Mode
 * 1 : SMBUS Mode
*/

#define MI2C_MODE_I2C					0
#define MI2C_MODE_SMBUS					I2C_CR1_SMBUS

/* @REF : I2cSlaveAddrMode
 * I2C_OARADDMODE
 * BIT 15 ADDMODE addressing mode (slave mode)
 * 0 : 7-bit slave address (10-bit address not acknowledged)
 * 1 : 10-bit slave address (7-bit address not acknowledged)
*/

#define MI2C_ADDR_SLAVE_MODE_7BIT		0x00000000U
#define MI2C_ADDR_SLAVE_MODE_10BIT		((uint16)(1<<15))

/* @REF : AckCtrl
 * I2C_CR1
 * 0 : no acknowledge returned
 * 1 : acknowledge returned after a byte is received (matched address or data)
*/

#define MI2C_ACK_ENABLE				I2C_CR1_ACK
#define MI2C_ACK_DISABLE			((uint16)0x0000)

/* @REF : GenralCallAddrDetection
 * I2C_CR1
 * BIT 6 ENGC : general call enbal
 * 0 : general call disabled address 00h is NACKed
 * 1 : general call enabled address 00h is ACKed
*/

#define MI2C_ENGC_ENABLE		   I2C_CR1_ENGC
#define MI2C_ENGC_DISABLE		   0x00000000U


//---------------------------------------------------
//================ APIs Supported ===================
//---------------------------------------------------

COMMON_uddtApiState_t  MI2C_uddtInit(MI2C_uddtCfg_t *uddtI2cCfg);
COMMON_uddtApiState_t  MI2C_uddtReset(I2C_registerMap_t  *I2Cx);

COMMON_uddtApiState_t  MI2C_uddtGpioSetPins(I2C_registerMap_t  *I2Cx);

COMMON_uddtApiState_t MI2C_uddtMasterTx(I2C_registerMap_t  *I2Cx , uint16 u16DesAddr , uint8 *u8Data , uint32 u32DataLen,
		MI2C_uddtStopBitCtrl_t uddtStopCtrl , MI2C_uddtStartBitCtrl_t uddtStartCtrl);

COMMON_uddtApiState_t MI2C_uddtMasterRx(I2C_registerMap_t  *I2Cx , uint16 u16DesAddr , uint8 *u8Data , uint32 u32DataLen,
		MI2C_uddtStopBitCtrl_t uddtStopCtrl , MI2C_uddtStartBitCtrl_t uddtStartCtrl);


COMMON_uddtApiState_t MI2C_uddtGenrateStart(I2C_registerMap_t  *I2Cx ,MI2C_uddtStartBitCtrl_t uddtStartCtrl,MI2C_uddtFunctionStatus_t uddtState);

MI2C_uddtFlagStatus_t MI2C_uddtGetFlagStatus(I2C_registerMap_t  *I2Cx ,MI2C_uddtFlags_t uddtFlag);

COMMON_uddtApiState_t MI2C_uddtSendSlaveAddr(I2C_registerMap_t  *I2Cx ,MI2C_uddtDirection_t uddtDirection , uint16 u16SlaAddr);

COMMON_uddtApiState_t MI2C_uddtGenrateStop (I2C_registerMap_t  *I2Cx ,MI2C_uddtFunctionStatus_t uddtState);
COMMON_uddtApiState_t MI2C_uddtAckCtrl(I2C_registerMap_t *I2Cx,MI2C_uddtFunctionStatus_t uddtState);

COMMON_uddtApiState_t MI2C_uddtSlaveTx(I2C_registerMap_t  *I2Cx , uint8 u8Data);
COMMON_uddtApiState_t MI2C_uddtSlaveRx(I2C_registerMap_t  *I2Cx , uint8 *u8Data);




#endif /* MCAL_INC_I2C_H_ */
