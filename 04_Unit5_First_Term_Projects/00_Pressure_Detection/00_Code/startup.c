/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : startup.c
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


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
void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void H_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void MM_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void Bus_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void Usage_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;

uint32_t vectors[] __attribute__((section(".vectors"))) = 
{
	(uint32_t) &_STACK_TOP,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault_Handler,
	(uint32_t) &Usage_Fault_Handler,

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

