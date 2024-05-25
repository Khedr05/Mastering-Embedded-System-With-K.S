/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : Fifo.c
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#include "Fifo.h"


EN_FIFO_status_t FIFO_uddtInitBuffer(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH *P_copyUddtBuf , uint32 copy_U32BufLength)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL) && (P_copyUddtBuf != PTR_NULL))
	{
		PS_copyUddtFifoBuf->base = P_copyUddtBuf;
		PS_copyUddtFifoBuf->head = P_copyUddtBuf;
		PS_copyUddtFifoBuf->tail = P_copyUddtBuf;
		PS_copyUddtFifoBuf->length = copy_U32BufLength;
		PS_copyUddtFifoBuf->count = 0;
		ret = FIFO_OK;
	}
	else
	{
		ret = FIFO_IS_PTR_NULL;
	}

	return ret;
}

EN_FIFO_status_t FIFO_uddtPushData(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH copyUddtData)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret != FIFO_IS_FULL)
			{
				*(PS_copyUddtFifoBuf->head) = copyUddtData;
				PS_copyUddtFifoBuf->count++;

				if( (PS_copyUddtFifoBuf->head) ==
						(PS_copyUddtFifoBuf->base + (PS_copyUddtFifoBuf->length * sizeof(DATA_WIDTH))))
				{
					PS_copyUddtFifoBuf->head = PS_copyUddtFifoBuf->base;
					ret = FIFO_OK;
				}
				else
				{
					PS_copyUddtFifoBuf->head++;
					ret = FIFO_OK;
				}
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{
			ret = FIFO_IS_NULL;
		}
	}
	else
	{
		ret = FIFO_IS_PTR_NULL;
	}

	return ret;
}

EN_FIFO_status_t FIFO_uddtPopData(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH *copyUddtRetOfData)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				/* Do Nothing */
			}
			else
			{
				*copyUddtRetOfData = *(PS_copyUddtFifoBuf->tail);
				PS_copyUddtFifoBuf->count--;

				if( (PS_copyUddtFifoBuf->tail) ==
						(PS_copyUddtFifoBuf->base + (PS_copyUddtFifoBuf->length * sizeof(DATA_WIDTH))))
				{
					PS_copyUddtFifoBuf->tail = PS_copyUddtFifoBuf->base;
					ret = FIFO_OK;
				}
				else
				{
					PS_copyUddtFifoBuf->tail++;
					ret = FIFO_OK;
				}
			}
		}
		else
		{
			ret = FIFO_IS_NULL;
		}
	}
	else
	{
		ret = FIFO_IS_PTR_NULL;
	}

	return ret;
}

EN_FIFO_status_t FIFO_uddtIsFull(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			if(PS_copyUddtFifoBuf->count == PS_copyUddtFifoBuf->length)
			{
				ret = FIFO_IS_FULL;
			}
			else if(PS_copyUddtFifoBuf->count < PS_copyUddtFifoBuf->length)
			{
				ret = FIFO_NEITHER_FULL_NOR_EMPTY;
			}
			else if(PS_copyUddtFifoBuf->count == 0)
			{
				ret = FIFO_IS_EMPTY;
			}
			else{/* Do Nothing */};
		}
		else
		{
			ret = FIFO_IS_NULL;
		}
	}
	else
	{
		ret = FIFO_IS_PTR_NULL;
	}

	return ret;
}

EN_FIFO_status_t FIFO_uddtPrintBuffer(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			DATA_WIDTH *temp;
			uint32 i;

			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				printf("FIFO Is Empty \n");
			}
			else
			{
				temp = PS_copyUddtFifoBuf->tail;
				printf("\n============= FIFO DATA ============\n");

				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					printf("\t %X \n",*temp);
					temp++;
				}
				printf("\n============= FIFO DATA END ============\n");
			}
		}
		else
		{
			ret = FIFO_IS_NULL;
		}
	}
	else
	{
		ret = FIFO_IS_PTR_NULL;
	}

	return ret;
}

