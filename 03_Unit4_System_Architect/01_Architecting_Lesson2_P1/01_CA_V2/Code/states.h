/*
 * states.h
 *
 *  Created on: 30 Nov 2023
 *      Author: sherif
 */

#ifndef STATES_H_
#define STATES_H_



//Automatic STATE Function genrated
#define STATE_DEFINE(_statefun_) void ST_##_statefun_()
#define STATE(_statefun_)	ST_##_statefun_

//States Connection
void US_distance_set(int d);
void DC_motor(int s);

#endif /* STATES_H_ */
