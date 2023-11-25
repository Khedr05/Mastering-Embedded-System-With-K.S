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

// booking 1024 B located by .bss through un intialized array of 256 int element (256 * 4 = 1024 B) 
static unsigned long _STACK_TOP[256];

void Default_Handler();
void Reset_Handler(); 
void NMI_Handler() __attribute__((weak,alias("Default_Handler")));;
void H_Fault_Handler() __attribute__((weak,alias("Default_Handler")));;
void MM_Fault_Handler() __attribute__((weak,alias("Default_Handler")));;
void Bus_Fault_Handler() __attribute__((weak,alias("Default_Handler")));;
void Usage_Fault_Handler() __attribute__((weak,alias("Default_Handler")));;


void (* const g_p_fn_vectors[])() __attribute__((section(".vectors"))) =
{
	 (void(*)()) ((unsigned long)_STACK_TOP + sizeof(_STACK_TOP)),
	 &Reset_Handler,
	 &NMI_Handler,
	 &H_Fault_Handler,
	 &MM_Fault_Handler,
	 &Bus_Fault_Handler,
	 &Usage_Fault_Handler,
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

