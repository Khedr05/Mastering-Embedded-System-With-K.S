/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 01_FIFO_Buffer
// File          : fifo.h
// Date          : 27 Nov 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

// user configuration
// select data width type (uint8 , uint16 , uint32 ...)

#include "stdTypes.h"
#define DATA_WIDTH		ST_studentInfo_t


typedef enum
{
	FIFO_NOK = 0,
	FIFO_OK,
	FIFO_IS_FULL,
	FIFO_IS_EMPTY,
	FIFO_NEITHER_FULL_NOR_EMPTY,
	FIFO_IS_NULL,
	FIFO_IS_PTR_NULL,
	FIFO_ID_IS_UNIQUE,
	FIFO_ID_NOT_UNIQUE,
	FIFO_ID_VALID,
	FIFO_ID_NOT_VALID
}EN_FIFO_status_t;

typedef struct
{
	uint8 length;
	uint8 count;
	DATA_WIDTH *head;
	DATA_WIDTH *base;
	DATA_WIDTH *tail;
}ST_FIFO_Buffer_t;


EN_FIFO_status_t FIFO_uddtInitBuffer(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH *P_copyUddtBuf , uint32 copy_U32BufLength);
EN_FIFO_status_t FIFO_uddtPushData(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH copyUddtData);
EN_FIFO_status_t FIFO_uddtPopData(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , DATA_WIDTH *copyUddtRetOfData);
EN_FIFO_status_t FIFO_uddtIsFull(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf);
EN_FIFO_status_t FIFO_uddtPrintBuffer(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf);
EN_FIFO_status_t FIFO_uddtIsUniqueRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck);
EN_FIFO_status_t FIFO_uddtShowDbStatistics(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf);
EN_FIFO_status_t FIFO_uddtFindByRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck);
EN_FIFO_status_t FIFO_uddtFindByFirstName(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf, uint8* copy_u8FirstNameToCheck);
EN_FIFO_status_t FIFO_uddtFindByCourseId(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck);
EN_FIFO_status_t FIFO_uddtDeleteByRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck);
EN_FIFO_status_t FIFO_uddtUpdateRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , uint32 copy_u32NewRollNumber);
EN_FIFO_status_t FIFO_uddtUpdateFirstName(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , uint8 *copy_u8NewFirstName);
EN_FIFO_status_t FIFO_uddtUpdateLastName(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , uint8 *copy_u8NewLasttName);
EN_FIFO_status_t FIFO_uddtUpdateGpa(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , float32 copy_f32NewGpa);
EN_FIFO_status_t FIFO_uddtUpdateCourses(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck ,uint32 *copy_u32NewCourses);
EN_FIFO_status_t FIFO_uddtIsValidRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck);



#endif /* FIFO_H_ */
