/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_LIFO_Buffer
// File          : main.c
// Date          : Nov 27, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "stdTypes.h"
#include "lifo.h"

uint32 gl_u32buffer1[5];

int main(void)
{
	uint32 i, temp;
	EN_LIFO_status_t ret = LIFO_NOK;
	ST_LIFO_Buffer_t uartLifo , i2cLifo;

	// static allocation
	LIFO_uddtInitBuffer(&uartLifo , gl_u32buffer1 , 5);

	// dynamic allocation
	uint32 *lo_u32buffer2 = (uint32 *)malloc(5 * sizeof(uint32));
	LIFO_uddtInitBuffer(&i2cLifo , lo_u32buffer2 , 5);

	for(i=0 ;i<7; i++)
	{
		ret = LIFO_uddtPushData(&uartLifo , i);
		if(ret == LIFO_OK)
		printf("Uart Lifo add : %d \n",i);
	}

	for(i=0 ;i<7; i++)
	{
		ret = LIFO_uddtPopData(&uartLifo , &temp);
		if(ret == LIFO_OK)
		printf("Uart Lifo remove : %d \n",temp);
	}
	return 0;
}
