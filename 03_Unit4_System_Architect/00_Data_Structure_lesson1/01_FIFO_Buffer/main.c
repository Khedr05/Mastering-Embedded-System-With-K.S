/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 01_FIFO_Buffer
// File          : main.c
// Date          : 27 Nov 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include <stdio.h>
#include "stdTypes.h"
#include "fifo.h"

int main(void)
{
	ST_FIFO_Buffer_t fifoUart ;
	DATA_WIDTH i , temp;
	DATA_WIDTH uartBuffer[5];

	if(FIFO_uddtInitBuffer(&fifoUart , uartBuffer , 5) == FIFO_OK)
		printf("FIFO initialise done \n");

	for(i=0;i<7;i++)
	{
		if(FIFO_uddtPushData(&fifoUart , i) == FIFO_OK)
			printf("FIFO push %X done \n",i);
		else
			printf("FIFO push %X fail \n",i);
	}

	FIFO_uddtPrintBuffer(&fifoUart);

	if(FIFO_uddtPopData(&fifoUart , &temp) == FIFO_OK)
		printf("FIFO pop %X done \n",temp);
	else
		printf("FIFO pop %X fail \n",temp);

	if(FIFO_uddtPopData(&fifoUart , &temp) == FIFO_OK)
		printf("FIFO pop %X done \n",temp);
	else
		printf("FIFO pop %X fail \n",temp);

	FIFO_uddtPrintBuffer(&fifoUart);

	return 0;
}
