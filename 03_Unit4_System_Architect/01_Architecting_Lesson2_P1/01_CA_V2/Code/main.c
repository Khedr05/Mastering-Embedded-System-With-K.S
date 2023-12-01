/*
 * main.c
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */

#include "CA.h"
#include "DC.h"
#include "US.h"

void setup()
{
	//init all the drivers
	//init IRQ
	//init HAL
	//init Block
	//set states pointers for each block
	DC_init();
	US_init();

	CA_state = STATE(CA_WAITING);
	DC_state = STATE(DC_IDLE);
	US_state = STATE(US_BUSY);
}

int main(void)
{
	setup();
	volatile int d;
	while(1)
	{
		// call state for each block
		CA_state();
		DC_state();
		US_state();
		for(d=0 ; d<=1000;d++);
	}
	return 0;
}
