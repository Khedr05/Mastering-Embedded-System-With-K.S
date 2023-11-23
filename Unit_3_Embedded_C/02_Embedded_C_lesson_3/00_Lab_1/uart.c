#include"uart.h"

#define UART0DR		*((volatile unsigned int* const)((unsigned int *)0x101f1000))

void uart_send_string(unsigned char* p_tx_string)
{
	while(*p_tx_string != '\0')
	{
		UART0DR = (unsigned int)(*p_tx_string);
		p_tx_string++;
	}
}