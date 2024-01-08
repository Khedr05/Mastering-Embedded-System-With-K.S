/*************************************************************************/
// Author        : Sherif Ashraf Khadr									 
// Project       : 00_Gpio_Driver                                    	 
// File          : vector_table.h                                  	     
// Date          : 31 Jul 2023	                                                                                                 */
// GitHub        : https://github.com/sherifkhadr             		     
/*************************************************************************/
#ifndef COMMON_VECTOR_TABLE_H_
#define COMMON_VECTOR_TABLE_H_

#define EXT_INT_0				__vector_1			/* External Interrupt Request 0 */
#define EXT_INT_1				__vector_2			/* External Interrupt Request 1 */
#define EXT_INT_2				__vector_3			/* External Interrupt Request 2 */

#define TIM2_COMP_INT			__vector_4			/* Timer/Counter 2 Compare Match	*/
#define TIM2_OVF_INT			__vector_5			/* Timer/Counter 2 Overflow			*/
#define TIM1_CAPT_INT			__vector_6			/* Timer/Counter 1 Capture Event	*/
#define TIM1_COMPA_INT			__vector_7			/* Timer/Counter 1 Compare Match A	*/
#define TIM1_COMPB_INT			__vector_8			/* Timer/Counter 1 Compare Match B	*/
#define TIM1_OVF_INT			__vector_9			/* Timer/Counter 1 Overflow			*/
#define TIM0_COMP_INT			__vector_10			/* Timer/Counter 0 Compare Match	*/
#define TIM0_OVF_INT			__vector_11			/* Timer/Counter 0 Overflow			*/

#define SPI_STC_INT				__vector_12			/* Serial Transfer Complete Interrupt   */
#define USART_RXC_INT			__vector_13			/* USART Rx Complete Interrupt		    */
#define USART_UDRE_INT			__vector_14			/* USART Data Register Empty Interrupt  */
#define USART_TXC_INT			__vector_15			/* USART Tx Complete Interrupt		    */
#define ADC_INT					__vector_16			/* ADC Conversion Complete Interrupt    */
#define EE_RDY_INT				__vector_17			/* EEPROM Ready Interrupt			    */
#define ANA_COMP_INT			__vector_18			/* Analog Comparator Interrupt		    */
#define TWI_INT					__vector_19			/* Two-Wire Serial Interface Interrupt  */
#define SPM_RDY_INT				__vector_20			/* Store Program Memory Ready Interrupt */


/*=================== Function-like Macros ====================*/

#define sei() __asm__ __volatile__ ("sei" ::: "memory")			/* Sets Global Interrupt Enable Bit   */
#define cli() __asm__ __volatile__ ("cli" ::: "memory")			/* Clears Global Interrupt Enable Bit */


#define ISR(INT_VECT)			void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)


#endif /* COMMON_VECTOR_TABLE_H_ */
