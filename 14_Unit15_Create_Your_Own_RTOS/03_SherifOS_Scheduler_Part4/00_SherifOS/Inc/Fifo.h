/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : Fifo.h
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include "stdTypes.h"
#include "Scheduler.h"


// user configuration
// select data width type (uint8 , uint16 , uint32 ...)

#define DATA_WIDTH		TaskRef_t*

typedef struct{
	unsigned int counter;
	DATA_WIDTH* head;
	DATA_WIDTH* tail;
	DATA_WIDTH* base;
	unsigned int  length;
}FIFO_Buffer_t;



typedef enum
{
	FIFO_NO_ERROR =0,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL,

}Buffer_status_t;


/*APIs*/
Buffer_status_t FIFO_uddtInitBuffer(FIFO_Buffer_t* fifo, DATA_WIDTH *buff , uint32 length);
Buffer_status_t FIFO_uddtEnqueue(FIFO_Buffer_t* fifo , DATA_WIDTH item);
Buffer_status_t FIFO_uddtDequeue(FIFO_Buffer_t* fifo , DATA_WIDTH *item);
Buffer_status_t FIFO_uddtIsFull(FIFO_Buffer_t* fifo);
Buffer_status_t FIFO_uddtPrintBuffer(FIFO_Buffer_t* fifo);


#endif /* FIFO_H_ */

