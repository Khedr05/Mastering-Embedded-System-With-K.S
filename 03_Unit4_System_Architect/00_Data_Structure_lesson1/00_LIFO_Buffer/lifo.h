/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_LIFO_Buffer
// File          : lifo.h
// Date          : Nov 27, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#ifndef LIFO_H_
#define LIFO_H_

// Type Definitions

typedef enum
{
	LIFO_NOK = 0,
	LIFO_OK,
	LIFO_IS_FULL,
	LIFO_IS_EMPTY,
	LIFO_IS_NULL,
	LIFO_IS_PTR_NULL
}EN_LIFO_status_t;

typedef struct
{
	uint32 length ;
	uint32 count ;
	uint32 *base ;
	uint32 *head ;
}ST_LIFO_Buffer_t;

// APIs

EN_LIFO_status_t LIFO_uddtInitBuffer(ST_LIFO_Buffer_t* PS_copyUddtLifoBuf , uint32 *P_copyU32Buf , uint32 copy_U32BufLength);
EN_LIFO_status_t LIFO_uddtPushData(ST_LIFO_Buffer_t* PS_copyUddtLifoBuf , uint32 copyU32Data);
EN_LIFO_status_t LIFO_uddtPopData(ST_LIFO_Buffer_t* PS_copyUddtLifoBuf , uint32 *copyU32RetOfData);



#endif /* LIFO_H_ */
