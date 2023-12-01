/*
 * CA.h
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */

#ifndef US_H_
#define US_H_

#include "states.h"

// Define States

typedef enum
{
	US_BUSY = 0,
}US_stateId;


// Declare states functions CA

void US_init(void);
STATE_DEFINE(US_BUSY);

//STATE pointer to function

extern void (*US_state)();

#endif /* US_H_ */
