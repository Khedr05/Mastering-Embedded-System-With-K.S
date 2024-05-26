/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : Fifo.c
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#include "Fifo.h"


Buffer_status_t FIFO_uddtInitBuffer(FIFO_Buffer_t* fifo, DATA_WIDTH *buff , uint32 length)
{

	if(!buff )
		return FIFO_NULL;

	fifo->base = buff ;
	fifo->head = fifo->base ;
	fifo->tail = fifo->base ;
	fifo->length = length;
	fifo->counter=0;

	return FIFO_NO_ERROR;

}


Buffer_status_t FIFO_uddtEnqueue(FIFO_Buffer_t* fifo , DATA_WIDTH item)
{

	/* fifo null*/

	if (!fifo->base || !fifo->length)
		return FIFO_NULL;
	/*fifo is full*/

	if ((fifo->head == fifo->tail) && (fifo->counter == fifo->length))
		return FIFO_FULL;

	*(fifo->tail)=item;
	fifo->counter++;

	/*for circular fifo again */

	/* circular enqueue */
	if (fifo->tail == (((unsigned int)fifo->base + (4*fifo->length )) - 4 ))
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_NO_ERROR;


}


Buffer_status_t FIFO_uddtDequeue(FIFO_Buffer_t* fifo , DATA_WIDTH *item)
{
	/* check fifo valid */
	if (!fifo->base || !fifo->length)
		return FIFO_NULL;

	/* fifo empty */
	if (fifo->head == fifo->tail)
		return FIFO_EMPTY;



	*item = *(fifo->head);
	fifo->counter--;

	/* circular dequeue */
	if (fifo->head == (((unsigned int)fifo->base + (4*fifo->length )) - 4 ))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_NO_ERROR;
}


Buffer_status_t FIFO_uddtIsFull(FIFO_Buffer_t* fifo)
{

	if(!fifo->head || !fifo->base || !fifo->tail)
		return FIFO_NULL;
	if(fifo->counter == fifo->length)
		return FIFO_FULL;

	return FIFO_NO_ERROR;
}










