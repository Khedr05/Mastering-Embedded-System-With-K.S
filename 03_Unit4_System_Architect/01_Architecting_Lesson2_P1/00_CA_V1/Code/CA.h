/*
 * CA.h
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */

#ifndef CA_H_
#define CA_H_

#include "states.h"

// Define States

typedef enum
{
	CA_WAITING = 0,
	CA_DRIVING
}CA_stateId;


// Declare states functions CA

STATE_DEFINE(CA_WAITING);
STATE_DEFINE(CA_DRIVING);

//STATE pointer to function

extern void (*CA_state)();

#endif /* CA_H_ */
