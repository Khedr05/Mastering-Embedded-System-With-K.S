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


typedef enum
{
	FIFO_NOK = 0,
	FIFO_OK,
	FIFO_IS_FULL,
	FIFO_IS_EMPTY,
	FIFO_NEITHER_FULL_NOR_EMPTY,
	FIFO_IS_NULL,
	FIFO_IS_PTR_NULL
}EN_FIFO_status_t;

typedef struct
{
	uint32 length;
	DATA_WIDTH count;
	DATA_WIDTH *head;
	DATA_WIDTH *base;
	DATA_WIDTH *tail;
}ST_FIFO_Buffer_t;

EN_FIFO_status_t FIFO_uddtInitBuffer(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH *P_copyUddtBuf , uint32 copy_U32BufLength);
EN_FIFO_status_t FIFO_uddtPushData(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH copyUddtData);
EN_FIFO_status_t FIFO_uddtPopData(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH *copyUddtRetOfData);
EN_FIFO_status_t FIFO_uddtIsFull(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf);
EN_FIFO_status_t FIFO_uddtPrintBuffer(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf);


#endif /* FIFO_H_ */
