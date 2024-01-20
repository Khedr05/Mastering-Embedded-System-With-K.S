/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : MNVIC.h
// Date          : Jan 16, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef MCAL_INC_NVIC_H_
#define MCAL_INC_NVIC_H_


#include "stm32f103x6.h"

#define SCB_VECTKEY					0x05FA0000UL

#define getIRQReg(IRQNumber)		(IRQNumber / 32)
#define getIRQPos(IRQNumber)		(IRQNumber % 32)

#define NOT_ACTIVE  0
#define IS_ACTIVE   1

#define NOT_PENDING 0
#define IS_PENDING  1

/*IRQ position in IVT definition */

#define MNVIC_WWDG_IRQ       	  0
#define MNVIC_PVD_IRQ       	  1
#define MNVIC_TAMPER_IRQ     	  2
#define MNVIC_RTC_IRQ       	  3
#define MNVIC_FLASH_IRQ      	  4
#define MNVIC_RCC_IRQ        	  5
#define MNVIC_EXTI0_IRQ      	  6
#define MNVIC_EXTI1_IRQ      	  7
#define MNVIC_EXTI2_IRQ      	  8
#define MNVIC_EXTI3_IRQ      	  9
#define MNVIC_EXTI4_IRQ      	  10
#define MNVIC_DMA1_Channel1_IRQ   11
#define MNVIC_DMA1_Channel2_IRQ   12
#define MNVIC_DMA1_Channel3_IRQ   13
#define MNVIC_DMA1_Channel4_IRQ   14
#define MNVIC_DMA1_Channel5_IRQ   15
#define MNVIC_DMA1_Channel6_IRQ   16
#define MNVIC_DMA1_Channel7_IRQ   17
#define MNVIC_ADC1_2_IRQ      	  18
#define MNVIC_USB_HP_CAN_TX_IRQ   19
#define MNVIC_USB_LP_CAN_RX0_IRQ  20
#define MNVIC_CAN_RX1_IRQ     	  21
#define MNVIC_CAN_SCE_IRQ     	  22
#define MNVIC_EXTI9_5_IRQ     	  23
#define MNVIC_TIM1_BRK_IRQ    	  24
#define MNVIC_TIM1_UP_IRQ     	  25
#define MNVIC_TIM1_TRG_COM_IRQ    26
#define MNVIC_TIM1_CC_IRQ     	  27
#define MNVIC_TIM2_IRQ        	  28
#define MNVIC_TIM3_IRQ        	  29
#define MNVIC_TIM4_IRQ        	  30
#define MNVIC_I2C1_EV_IRQ     	  31
#define MNVIC_I2C1_ER_IRQ     	  32
#define MNVIC_I2C2_EV_IRQ     	  33
#define MNVIC_I2C2_ER_IRQ     	  34
#define MNVIC_SPI1_IRQ        	  35
#define MNVIC_SPI2_IRQ         	  36
#define MNVIC_USART1_IRQ          37
#define MNVIC_USART2_IRQ       	  38
#define MNVIC_USART3_IRQ          39
#define MNVIC_EXTI15_10_IRQ   	  40
#define MNVIC_RTCAlarm_IRQ    	  41
#define MNVIC_USBWakeUp_IRQ   	  42
#define MNVIC_TIM8_BRK_IRQ    	  43
#define MNVIC_TIM8_UP_IRQ     	  44
#define MNVIC_TIM8_TRG_COM_IRQ    45
#define MNVIC_TIM8_CC_IRQ     	  46
#define MNVIC_ADC3_IRQ        	  47
#define MNVIC_FSMC_IRQ        	  48
#define MNVIC_SDIO_IRQ        	  49
#define MNVIC_TIM5_IRQ         	  50
#define MNVIC_SPI3_IRQ         	  51
#define MNVIC_UART4_IRQ      	  52
#define MNVIC_UART5_IRQ      	  53
#define MNVIC_TIM6_IRQ        	  54
#define MNVIC_TIM7_IRQ        	  55
#define MNVIC_DMA2_Channel1_IRQ   56
#define MNVIC_DMA2_Channel2_IRQ   57
#define MNVIC_DMA2_Channel3_IRQ   58
#define MNVIC_DMA2_Channel4_5_IRQ 59

/*IRQ Groups And Subgroups*/

typedef enum
{
	MNVIC_GP_16_SP_00	= 0,
	MNVIC_GP_08_SP_02,
	MNVIC_GP_04_SP_04,
	MNVIC_GP_02_SP_08,
	MNVIC_GP_00_SP_16
}MNVIC_uddtGroups_t;


COMMON_uddtApiState_t  MNVIC_uddtEnableIRQ(uint8 u8IRQ);
COMMON_uddtApiState_t  MNVIC_uddtDisableIRQ(uint8 u8IRQ);

COMMON_uddtApiState_t  MNVIC_uddtGetPendingIRQ(uint8 u8IRQ , uint8 *u8RetOfStatus);
COMMON_uddtApiState_t  MNVIC_uddtSetPendingIRQ(uint8 u8IRQ);
COMMON_uddtApiState_t  MNVIC_uddtResetPendingIRQ(uint8 u8IRQ);

COMMON_uddtApiState_t  MNVIC_uddtIsActiveIRQ(uint8 u8IRQ , uint8 *u8RetOfStatus);

COMMON_uddtApiState_t  MNVIC_uddtSetIRQPriority(uint8 u8IRQ , MNVIC_uddtGroups_t uddtGroupSelection , uint8 u8GroupPriority , uint8 u8SubPriority);
COMMON_uddtApiState_t  MNVIC_uddtSetIRQGroup(MNVIC_uddtGroups_t uddtGroupSelection);

#endif /* MCAL_INC_NVIC_H_ */
