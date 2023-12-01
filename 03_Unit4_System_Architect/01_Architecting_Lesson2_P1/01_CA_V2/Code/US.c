/*
 * CA.c
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */
#include <stdio.h>
#include <stdlib.h>
#include "US.h"

// variables

static int US_distance = 0;

static US_stateId USState;
//STATE pointer to function

void (*US_state)();


int US_Get_Distance_Rand(int l,int r,int count)
{
	int i,rand_num=0;
	for(i=0 ; i<count ; i++)
	{
		rand_num = (rand()%(r-l+1))+ l;
	}
	return rand_num;
}

void US_init(void)
{
	//Init US Sensor
	//Call The US Driver Or Functions
	printf("DC_Init\n");
}


STATE_DEFINE(US_BUSY)
{
	//State Action
	USState = US_BUSY;
	//Read From The US
	US_distance = US_Get_Distance_Rand(45,55,1);

	printf("US_BUSY State : Distance = %d \n",US_distance);

	US_distance_set(US_distance);
	US_state = STATE(US_BUSY);
}


