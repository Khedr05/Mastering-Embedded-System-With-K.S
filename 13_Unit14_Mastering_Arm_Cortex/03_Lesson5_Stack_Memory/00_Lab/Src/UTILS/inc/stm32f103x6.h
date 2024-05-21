/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : stm32f103x6.h
// Date          : Jan 5, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef STM32F103X6_H_
#define STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------

#include "common.h"

/*_________________________________________________________________*/

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define  FLASH_MEMORY_BUS						0x08000000UL
#define  SYSTEM_MEMORY_BUS						0x1FFFF000UL
#define  SRAM_MEMORY_BUS						0x20000000UL

#define  PERIPHERALS_BASE						0x40000000UL
#define  CORTEX_M3_INTERNAL_PERIPHERALS_BASE    0xE0000000UL

/*___________________________________________________________________*/


//-----------------------------
//Base addresses for Core Peripherals
//-----------------------------

#define NVIC_BASE						0xE000E100UL
#define SCB_BASE						0xE000ED00UL

//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------



//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

// RCC

#define RCC_BASE					0x40021000UL

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

// USART

#define USART2_BASE				    0x40004400UL
#define USART3_BASE				    0x40004800UL

// SPI

#define SPI2_BASE					0x40003800UL

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

// GPIO

// A,B fully included in LQFP48 package

#define GPIOA_BASE				    0x40010800UL
#define GPIOB_BASE					0x40010C00UL

// C,D partial included in LQFP48 package

#define GPIOC_BASE				    0x40011000UL
#define GPIOD_BASE					0x40011400UL

// E not included in LQFP48 package

#define GPIOE_BASE				    0x40011800UL

// EXTI

#define EXTI_BASE					0x40010400UL

// AFIO

#define AFIO_BASE					0x40010000UL

// USART

#define USART1_BASE				    0x40013800UL

// SPI

#define SPI1_BASE					0x40013000UL

// I2C

#define I2C1_BASE					0x40005400UL
#define I2C2_BASE					0x40005800UL

/*______________________________________________________________________*/


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : Core Peripheral
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
  vuint32    ISERx[3];
  vuint32    RESERVED0[29];
  vuint32    ICERx[3];
  vuint32    RESERVED1[29];
  vuint32	 ISPRx[3];
  vuint32    RESERVED2[29];
  vuint32    ICPRx[3];
  vuint32    RESERVED3[29];
  vuint32    IABRx[3];
  vuint32    RESERVED4[61];
  vuint8     IPRx[80];
  vuint32    RESERVED5[695];
  vuint32    STIR;
}NVIC_registerMap_t;


typedef struct
{
	vuint32  CPUID;
	vuint32  ICSR;
	vuint32  VTOR;
	vuint32  AIRCR;
	vuint32  SCR;
	vuint32  CCR;
	vuint32  SHPRx[3];
	vuint32  SHCRS;
	vuint32  CFSR;
	vuint32  HFSR;
	vuint32  RESERVED;
	vuint32  MMAR;
	vuint32  BFAR;
}SCB_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   CR;
	vuint32   CFGR;
	vuint32   CIR;
	vuint32   APB2RSTR;
	vuint32   APB1RSTR;
	vuint32   AHBENR;
	vuint32   APB2ENR;
	vuint32   APB1ENR;
	vuint32   BDCR;
	vuint32   CSR;
}RCC_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   CRL;
	vuint32   CRH;
	vuint32   IDR;
	vuint32   ODR;
	vuint32   BSRR;
	vuint32   BRR;
	vuint32   LCKR;
}GPIO_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   IMR;
	vuint32   EMR;
	vuint32   RTSR;
	vuint32   FTSR;
	vuint32   SWIER;
	vuint32   PR;
}EXTI_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   EVCR;
	vuint32   MAPR;
	vuint32   EXTICRx[4];
	vuint32   RESERVED0;
	vuint32   MAPR2;
}AFIO_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   SR;
	vuint32   DR;
	vuint32   BRR;
	vuint32   CR1;
	vuint32   CR2;
	vuint32   CR3;
	vuint32   GTPR;
}USART_registerMap_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : SPI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   CR1;
	vuint32   CR2;
	vuint32   SR;
	vuint32   DR;
	vuint32   CRCPR;
	vuint32   RXCRCR;
	vuint32   TXCRCR;
	vuint32   I2SCFGR;
	vuint32   I2SPR;
}SPI_registerMap_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : I2C
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   CR1;
	vuint32   CR2;
	vuint32   OAR1;
	vuint32   OAR2;
	vuint32   DR;
	vuint32   SR1;
	vuint32   SR2;
	vuint32   CCR;
	vuint32   TRISE;
}I2C_registerMap_t;

/*__________________________________________________________________________*/


//-*-*-*-*-*-*-*-*-*-*-*-
//Core Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*


#define NVIC		  ((NVIC_registerMap_t*)NVIC_BASE)
#define SCB			  ((SCB_registerMap_t*)SCB_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*


#define  GPIOA       ((GPIO_registerMap_t*)GPIOA_BASE)
#define  GPIOB       ((GPIO_registerMap_t*)GPIOB_BASE)
#define  GPIOC       ((GPIO_registerMap_t*)GPIOC_BASE)
#define  GPIOD       ((GPIO_registerMap_t*)GPIOD_BASE)
#define  GPIOE       ((GPIO_registerMap_t*)GPIOE_BASE)

#define RCC			 ((RCC_registerMap_t*)RCC_BASE)

#define EXTI  		 ((EXTI_registerMap_t*)EXTI_BASE)

#define AFIO  		 ((AFIO_registerMap_t*)AFIO_BASE)

#define USART1       ((USART_registerMap_t*)USART1_BASE)
#define USART2       ((USART_registerMap_t*)USART2_BASE)
#define USART3       ((USART_registerMap_t*)USART3_BASE)

#define SPI1         ((SPI_registerMap_t*)SPI1_BASE)
#define SPI2         ((SPI_registerMap_t*)SPI2_BASE)

#define I2C1         ((I2C_registerMap_t*)I2C1_BASE)
#define I2C2         ((I2C_registerMap_t*)I2C2_BASE)

/*__________________________________________________________________________*/


//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*


/*__________________________________________________________________________*/

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Bit Definition
//-*-*-*-*-*-*-*-*-*-*-*




//-*-*-*-*-*-*-*-*-*-*-*-
//I2C Bit Definition
//-*-*-*-*-*-*-*-*-*-*-*

/*******************  Bit definition for I2C_CR1 register  ********************/

#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */

/*******************  Bit definition for I2C_CR2 register  ********************/

#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */

/*******************  Bit definition for I2C_OAR2 register  *******************/

#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)

/*******************  Bit definition for I2C_SR1 register  ********************/

#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/

#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */


/*__________________________________________________________________________*/

#endif /* STM32F103X6_H_ */
