/*
 * CA.c
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */
#include <stdio.h>
#include <stdlib.h>
#include "DC.h"

// variables

static int	DC_speed = 0;

static DC_stateId DCState;
//STATE pointer to function

void (*DC_state)();


void DC_init(void)
{
	//Init Dc
	printf("DC_Init\n");
}

void DC_motor(int s)
{
	DC_speed = s;
	DC_state = STATE(DC_BUSY);
	printf("CA -> -> -> DC          DC_motor()\n");
}

STATE_DEFINE(DC_IDLE)
{
	//State Action
	DCState = DC_IDLE;
	//Call PWM
	printf("DC_IDLE State : Speed = %d \n",DC_speed);
}

STATE_DEFINE(DC_BUSY)
{
	//State Action
	DCState = DC_BUSY;
	//Call Dc_Driver
	DC_state = STATE(DC_IDLE);

	printf("DC_Busy State :   speed = %d \n\n\n",DC_speed);
}


