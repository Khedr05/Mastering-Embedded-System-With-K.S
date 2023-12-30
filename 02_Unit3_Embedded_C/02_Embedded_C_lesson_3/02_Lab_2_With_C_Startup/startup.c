/* 
startup.c 
sherif ashraf khedr
*/

#include <stdint.h>

extern int main(void);
extern unsigned int _E_TEXT;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_BSS;
extern unsigned int _E_BSS;
extern unsigned int _STACK_TOP;

void Default_Handler(void);
void Reset_Handler(void); 

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));

void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TAMPER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USB_HP_CAN_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USB_LP_CAN_RX0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN_RX1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN_SCE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTCAlarm_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FSMC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel4_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ETH_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ETH_WKUP(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_TX_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_SCE_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_Handler(void) __attribute__((weak, alias("Default_Handler")));


uint32_t vectors[] __attribute__((section(".vectors"))) = 
{
	(uint32_t) 	&_STACK_TOP,							/* Reserved                                         */
  	(uint32_t) 	&Reset_Handler,							/* Reset 											*/
 	(uint32_t) 	&NMI_Handler,							/* Non maskable interrupt. The RCC Clock Security 
 														   System (CSS) is linked to the NMI vector.		*/
  	(uint32_t) 	&HardFault_Handler, 					/* All class of fault 								*/
 	(uint32_t)	&MemManage_Handler, 					/* Memory management								*/
 	(uint32_t)	&BusFault_Handler,  					/* Pre-fetch fault, memory access BusFault_Handler	*/
 	(uint32_t)	&UsageFault_Handler, 					/* Undefined instruction or illegal state			*/
	(uint32_t)	&0, 									/* Reserved                                         */
  	(uint32_t)	&0, 								    /* Reserved                                         */
  	(uint32_t)	&0, 									/* Reserved                                         */	
  	(uint32_t)	&0, 									/* Reserved                                         */
  	(uint32_t)	&SVC_Handler,							/* System service call via SWI instruction			*/
  	(uint32_t)	&DebugMon_Handler, 						/* Debug Monitor 									*/
  	(uint32_t)	&0, 									/* Reserved                                         */
  	(uint32_t)	&PendSV_Handler, 						/* Pendable request for system service 				*/
  	(uint32_t)	&SysTick_Handler, 						/* System tick timer 								*/
  	(uint32_t)	&WWDG_IRQHandler,          				/* Window Watchdog interrupt                        */
  	(uint32_t)	&PVD_IRQHandler,            			/* PVD through EXTI line detection interrupt        */
  	(uint32_t)	&TAMPER_IRQHandler,         			/* Tamper interrupt                                 */
  	(uint32_t)	&RTC_IRQHandler,            			/* RTC global interrupt                             */
  	(uint32_t)	&FLASH_IRQHandler,         				/* Flash global interrupt                           */
  	(uint32_t)	&RCC_IRQHandler,         				/* RCC global interrupt                             */
  	(uint32_t)	&EXTI0_IRQHandler,         				/* EXTI Line0 interrupt                             */
  	(uint32_t)	&EXTI1_IRQHandler,         				/* EXTI Line1 interrupt                             */
  	(uint32_t)	&EXTI2_IRQHandler,         				/* EXTI Line2 interrupt                             */
  	(uint32_t)	&EXTI3_IRQHandler,         				/* EXTI Line3 interrupt                             */
  	(uint32_t)	&EXTI4_IRQHandler,         				/* EXTI Line4 interrupt                             */
  	(uint32_t)	&DMA1_Channel1_IRQHandler, 				/* DMA1 Channel1 global interrupt                   */
  	(uint32_t)	&DMA1_Channel2_IRQHandler, 				/* DMA1 Channel2 global interrupt                   */
  	(uint32_t)	&DMA1_Channel3_IRQHandler, 				/* DMA1 Channel3 global interrupt                   */
  	(uint32_t)	&DMA1_Channel4_IRQHandler, 				/* DMA1 Channel4 global interrupt                   */
  	(uint32_t)	&DMA1_Channel5_IRQHandler, 				/* DMA1 Channel5 global interrupt                   */
  	(uint32_t)	&DMA1_Channel6_IRQHandler, 				/* DMA1 Channel6 global interrupt                   */
  	(uint32_t)	&DMA1_Channel7_IRQHandler, 				/* DMA1 Channel7 global interrupt                   */
  	(uint32_t)	&ADC1_2_IRQHandler,        				/* ADC1 and ADC2 global interrupt                   */
  	(uint32_t)	&USB_HP_CAN_TX_IRQHandler, 				/* USB High Priority or CAN TX interrupts           */
  	(uint32_t)	&USB_LP_CAN_RX0_IRQHandler,				/* USB Low Priority or CAN RX0 interrupts           */
  	(uint32_t)	&CAN_RX1_IRQHandler,       				/* CAN RX1 interrupt                                */
  	(uint32_t)	&CAN_SCE_IRQHandler,       				/* CAN SCE interrupt                                */
  	(uint32_t)	&EXTI9_5_IRQHandler,       				/* EXTI Line[9:5] interrupts                        */
  	(uint32_t)	&TIM1_BRK_IRQHandler,      				/* TIM1 Break interrupt                             */
  	(uint32_t)	&TIM1_UP_IRQHandler,       				/* TIM1 Update interrupt                            */
  	(uint32_t)	&TIM1_TRG_COM_IRQHandler,  				/* TIM1 Trigger and Commutation interrupts          */
  	(uint32_t)	&TIM1_CC_IRQHandler,       				/* TIM1 Capture Compare interrupt                   */
  	(uint32_t)	&TIM2_IRQHandler,         				/* TIM2 global interrupt                            */
  	(uint32_t)	&TIM3_IRQHandler,         				/* TIM3 global interrupt                            */
  	(uint32_t)	&TIM4_IRQHandler,         				/* TIM4 global interrupt                            */
  	(uint32_t)	&I2C1_EV_IRQHandler,       				/* I2C1 event interrupt                             */
  	(uint32_t)	&I2C1_ER_IRQHandler,       				/* I2C1 error interrupt                             */
  	(uint32_t)	&I2C2_EV_IRQHandler,       				/* I2C2 event interrupt                             */
  	(uint32_t)	&I2C2_ER_IRQHandler,       				/* I2C2 error interrupt                             */
  	(uint32_t)	&SPI1_IRQHandler,          				/* SPI1 global interrupt                            */
  	(uint32_t)	&SPI2_IRQHandler,          				/* SPI2 global interrupt                            */
  	(uint32_t)	&USART1_IRQHandler,        				/* USART1 global interrupt                          */
  	(uint32_t)	&USART2_IRQHandler,        				/* USART2 global interrupt                          */
  	(uint32_t)	&USART3_IRQHandler,        				/* USART3 global interrupt                          */
  	(uint32_t)	&EXTI15_10_IRQHandler,     				/* EXTI Line[15:10] interrupts                      */
  	(uint32_t)	&RTCAlarm_IRQHandler,      				/* RTC Alarms through EXTI line interrupt           */
  	(uint32_t)	&0,                        				/* Reserved                                         */
  	(uint32_t)	&TIM8_BRK_IRQHandler,      				/* TIM8 Break interrupt                             */
  	(uint32_t)	&TIM8_UP_IRQHandler,       				/* TIM8 Update interrupt                            */
  	(uint32_t)	&TIM8_TRG_COM_IRQHandler,  				/* TIM8 Trigger and Commutation interrupts          */
  	(uint32_t)	&TIM8_CC_IRQHandler,       				/* TIM8 Capture Compare interrupt                   */
  	(uint32_t)	&ADC3_IRQHandler,          				/* ADC3 global interrupt                            */
  	(uint32_t)	&FSMC_IRQHandler,          				/* FSMC global interrupt                            */
  	(uint32_t)	&SDIO_IRQHandler,          				/* SDIO global interrupt                            */
  	(uint32_t)	&TIM5_IRQHandler,          				/* TIM5 global interrupt                            */
  	(uint32_t)	&SPI3_IRQHandler,          				/* SPI3 global interrupt                            */
  	(uint32_t)	&UART4_IRQHandler,         				/* UART4 global interrupt                           */
  	(uint32_t)	&UART5_IRQHandler,         				/* UART5 global interrupt                           */
  	(uint32_t)	&TIM6_IRQHandler,          				/* TIM6 global interrupt                            */
  	(uint32_t)	&TIM7_IRQHandler,          				/* TIM7 global interrupt                            */
  	(uint32_t)	&DMA2_Channel1_IRQHandler, 				/* DMA2 Channel1 global interrupt                   */
  	(uint32_t)	&DMA2_Channel2_IRQHandler, 				/* DMA2 Channel2 global interrupt                   */
  	(uint32_t)	&DMA2_Channel3_IRQHandler, 				/* DMA2 Channel3 global interrupt                   */
  	(uint32_t)	&DMA2_Channel4_5_IRQHandler,			/* DMA2 Channel4 and DMA2 Channel5 global interrupt */
  	(uint32_t) 	&ETH_Handler,							/* Ethernet global interrupts						*/
	(uint32_t) 	&ETH_WKUP,								/* Ethernet Wakeup through EXTI line interrupt 		*/
	(uint32_t) 	&CAN2_TX_Handler,						/* CAN2 TX interrupts 								*/
	(uint32_t) 	&CAN2_RX0_Handler,						/* CAN2 RX0 interrupts 								*/
	(uint32_t) 	&CAN2_RX1_Handler,						/* CAN2 RX1 interrupts 								*/
	(uint32_t) 	&CAN2_SCE_Handler,						/* CAN2 SCE interrupts 								*/
	(uint32_t) 	&OTG_FS_Handler,						/* USB On The Go FS global interrupt 				*/

};

void Default_Handler(void)
{
		Reset_Handler();
}

void Reset_Handler(void)
{
	/* copy data section from flash to sram */

	unsigned int DATA_SIZE = (unsigned char *)&_E_DATA - (unsigned char *)&_S_DATA ;
	unsigned char*	P_src = (unsigned char *)&_E_TEXT ;
	unsigned char*	P_dst = (unsigned char *)&_S_DATA ;

	for(int i=0 ; i<DATA_SIZE ; i++)
	{
		*((unsigned char *)P_dst++) = *((unsigned char *)P_src++);
	}

	/* init .bss section in sram  = 0*/

	unsigned int BSS_SIZE = (unsigned char *)&_E_BSS - (unsigned char *)&_S_BSS ;
	P_dst = (unsigned char*)&_S_BSS;

	for(int i=0 ; i<BSS_SIZE ; i++)
	{
		*((unsigned char *)P_dst++) = (unsigned char)0;
	}

	/* jump to the main */

	main();
}

