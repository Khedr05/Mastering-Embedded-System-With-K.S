/*
 * CA.c
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */
#include <stdio.h>
#include <stdlib.h>
#include "CA.h"

// variables

static int CA_speed = 0;
static int CA_distance = 0;
static int CA_threshold = 50;
static CA_stateId carState;
//STATE pointer to function

void (*CA_state)();

//States Connection
void US_distance_set(int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold)?(CA_state = STATE(CA_WAITING)) : (CA_state = STATE(CA_DRIVING));

	printf("US -------> CA: distance = %d speed = %d \n",CA_distance , CA_speed);
}

STATE_DEFINE(CA_WAITING)
{
	// state name
	carState = CA_WAITING;

	// state action
	CA_speed = 0;
	//DC_Motor(speed);

	printf("CA_Waiting State: distance = %d speed = %d \n",CA_distance , CA_speed);
}

STATE_DEFINE(CA_DRIVING)
{
	// state name
	carState = CA_DRIVING;

	// state action
	CA_speed = 30;
	//DC_Motor(speed);
	DC_motor(CA_speed);
	// event check
	//get_distance_from_us
	(CA_distance <= CA_threshold)?(CA_state = STATE(CA_WAITING)) : (CA_state = STATE(CA_DRIVING));

	printf("CA_Driving State: distance = %d speed = %d \n",CA_distance , CA_speed);
}



