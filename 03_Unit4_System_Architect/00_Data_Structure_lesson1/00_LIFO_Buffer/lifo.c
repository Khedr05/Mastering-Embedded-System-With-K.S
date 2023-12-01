/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_LIFO_Buffer
// File          : lifo.c
// Date          : Nov 27, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "stdTypes.h"
#include "lifo.h"


EN_LIFO_status_t LIFO_uddtInitBuffer(ST_LIFO_Buffer_t* PS_copyUddtLifoBuf , uint32 *P_copyU32Buf , uint32 copy_U32BufLength)
{
	EN_LIFO_status_t ret = LIFO_NOK;

	if((PS_copyUddtLifoBuf != PTR_NULL) && (P_copyU32Buf != PTR_NULL))
	{
		PS_copyUddtLifoBuf->base = P_copyU32Buf;
		PS_copyUddtLifoBuf->head = P_copyU32Buf;
		PS_copyUddtLifoBuf->length = copy_U32BufLength;
		PS_copyUddtLifoBuf->count = 0;

		ret = LIFO_OK;
	}
	else
	{
		ret = LIFO_IS_PTR_NULL;
	}

	return ret;
}

EN_LIFO_status_t LIFO_uddtPushData(ST_LIFO_Buffer_t* PS_copyUddtLifoBuf , uint32 copyU32Data)
{
	EN_LIFO_status_t ret = LIFO_NOK;

	if((PS_copyUddtLifoBuf != PTR_NULL))
	{
		if((PS_copyUddtLifoBuf->head != PTR_NULL) && (PS_copyUddtLifoBuf->base != PTR_NULL))
		{
			if(PS_copyUddtLifoBuf->count == PS_copyUddtLifoBuf->length)
			{
				ret = LIFO_IS_FULL;
			}
			else
			{
				*(PS_copyUddtLifoBuf->head) = copyU32Data;
				PS_copyUddtLifoBuf->head++;
				PS_copyUddtLifoBuf->count++;
				ret = LIFO_OK;
			}
		}
		else
		{
			ret = LIFO_IS_NULL;
		}
	}
	else
	{
		ret = LIFO_IS_PTR_NULL;
	}

	return ret;
}

EN_LIFO_status_t LIFO_uddtPopData(ST_LIFO_Buffer_t* PS_copyUddtLifoBuf , uint32 *copyU32RetOfData)
{
	EN_LIFO_status_t ret = LIFO_NOK;

	if((PS_copyUddtLifoBuf != PTR_NULL) && (copyU32RetOfData != PTR_NULL))
	{
		if((PS_copyUddtLifoBuf->head != PTR_NULL) && (PS_copyUddtLifoBuf->base != PTR_NULL))
		{
			if(PS_copyUddtLifoBuf->count == 0)
			{
				ret = LIFO_IS_EMPTY;
			}
			else
			{
				PS_copyUddtLifoBuf->head--;
				*copyU32RetOfData = *(PS_copyUddtLifoBuf->head);
				PS_copyUddtLifoBuf->count--;
				ret = LIFO_OK;
			}
		}
		else
		{
			ret = LIFO_IS_NULL;
		}
	}
	else
	{
		ret = LIFO_IS_PTR_NULL;
	}

	return ret;
}
