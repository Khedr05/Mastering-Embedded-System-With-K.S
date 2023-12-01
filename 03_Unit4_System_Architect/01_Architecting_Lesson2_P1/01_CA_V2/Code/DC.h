/*
 * CA.h
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */

#ifndef DC_H_
#define DC_H_

#include "states.h"

// Define States

typedef enum
{
	DC_IDLE = 0,
	DC_BUSY
}DC_stateId;


// Declare states functions CA

STATE_DEFINE(DC_IDLE);
STATE_DEFINE(DC_BUSY);

void DC_init(void);
//STATE pointer to function

extern void (*DC_state)();

#endif /* DC_H_ */
