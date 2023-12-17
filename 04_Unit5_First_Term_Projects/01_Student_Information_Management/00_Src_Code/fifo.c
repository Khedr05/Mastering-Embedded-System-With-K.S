/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 01_FIFO_Buffer
// File          : fifo.c
// Date          : 27 Nov 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include <stdio.h>
#include <string.h>
#include "stdTypes.h"
#include "studentDbOptions.h"
#include "fifo.h"


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
				DPRINTF("FIFO Is Empty \n");
			}
			else
			{
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					DPRINTF("Student Roll Number IS        : %d\n",temp->u32RollNumber);
					DPRINTF("Student First Name IS         : %s\n",temp->u8FirstName);
					DPRINTF("Student Last Name Is          : %s\n",temp->u8LastName);
					DPRINTF("Student GPA Is                : %.2f\n",temp->f32Gpa);
					for(uint8 j=0 ; j<5;j++)
					{
						DPRINTF("Student Course %d Id Is : %d\n",j+1,temp->u32CoursesIdNumber[j]);
					}
					temp++;
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

EN_FIFO_status_t FIFO_uddtIsUniqueRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty \n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						u8IdFounedFlag = 1;
						break;
					}
					temp++;
				}
				if(u8IdFounedFlag == 1)
				{
					ret = FIFO_ID_NOT_UNIQUE;
				}
				else
				{
					ret = FIFO_ID_IS_UNIQUE;
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

EN_FIFO_status_t FIFO_uddtShowDbStatistics(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty");
			}
			else
			{
				DPRINTF("[INFO] The Total Number Of Student Is %d \n",PS_copyUddtFifoBuf->count);
				DPRINTF("[INFO] You Can Add Up To %d Student \n",PS_copyUddtFifoBuf->length);
				DPRINTF("[INFO] You Can Add %d More Student \n",PS_copyUddtFifoBuf->length - PS_copyUddtFifoBuf->count);
				ret = FIFO_OK;
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


EN_FIFO_status_t FIFO_uddtFindByRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						DPRINTF("Student Roll Number IS        : %d\n",temp->u32RollNumber);
						DPRINTF("Student First Name IS         : %s\n",temp->u8FirstName);
						DPRINTF("Student Last Name Is          : %s\n",temp->u8LastName);
						DPRINTF("Student GPA Is                : %.2f\n",temp->f32Gpa);
						for(uint8 j=0 ; j<5;j++)
						{
							DPRINTF("Student Course %d Id Is : %d\n",j+1,temp->u32CoursesIdNumber[j]);
						}
						u8IdFounedFlag = 1;
						break;
					}else{/* Do Nothing */};
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Roll Number %d Not Found \n",copy_u32IdToCheck);
				}
				ret = FIFO_OK;
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

EN_FIFO_status_t FIFO_uddtFindByFirstName(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf, uint8* copy_u8FirstNameToCheck)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if (PS_copyUddtFifoBuf != PTR_NULL)
	{
		if (PS_copyUddtFifoBuf->head != PTR_NULL && PS_copyUddtFifoBuf->base != PTR_NULL && PS_copyUddtFifoBuf->tail != PTR_NULL)
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if (ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8NameFoundFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;

				for (i = 0; i < PS_copyUddtFifoBuf->count; i++)
				{
					if (strcmp((char*)temp->u8FirstName,(char *)copy_u8FirstNameToCheck) == 0)
					{
						DPRINTF("Student Roll Number IS        : %d\n", temp->u32RollNumber);
						DPRINTF("Student First Name IS         : %s\n", temp->u8FirstName);
						DPRINTF("Student Last Name Is          : %s\n", temp->u8LastName);
						DPRINTF("Student GPA Is                : %.2f\n", temp->f32Gpa);
						for (uint8 j = 0; j < 5; j++)
						{
							DPRINTF("Student Course %d Id Is : %d\n", j + 1, temp->u32CoursesIdNumber[j]);
						}
						u8NameFoundFlag = 1;
					}
					else
					{
						/* Do Nothing */
					};
					temp++;
				}

				if (u8NameFoundFlag == 0)
				{
					DPRINTF("[ERROR] First Name %s Not Found\n", copy_u8FirstNameToCheck);
				}

				ret = FIFO_OK;
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


EN_FIFO_status_t FIFO_uddtFindByCourseId(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i,j,studentCount=0;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					for(j=0;j<5;j++)
					{
						if(temp->u32CoursesIdNumber[j] == copy_u32IdToCheck)
						{
							DPRINTF("The Student Details Is        :\n")
																			DPRINTF("Student Roll Number IS        : %d\n",temp->u32RollNumber);
							DPRINTF("Student First Name  IS        : %s\n",temp->u8FirstName);
							DPRINTF("Student Last Name   Is        : %s\n",temp->u8LastName);
							DPRINTF("Student GPA Is                : %.2f\n",temp->f32Gpa);
							u8IdFounedFlag = 1;
							studentCount++;
							break;
						}else{/* Do Nothing */};
					}
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Course Id %d Not Found \n",copy_u32IdToCheck);
				}
				else
				{
					DPRINTF("[INFO] Total Number Of Student Enrolled Is : %d\n",studentCount);
				}
				ret = FIFO_OK;
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

EN_FIFO_status_t FIFO_uddtDeleteByRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						u8IdFounedFlag = 1;
						break;
					}else{/* Do Nothing */};
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Roll Number %d Not Found \n",copy_u32IdToCheck);
				}
				else
				{
					for(;i<PS_copyUddtFifoBuf->count ; i++)
					{
						*temp = *(temp + 1);
						temp++;
					}
					PS_copyUddtFifoBuf->count--;
					DPRINTF("[INFO] The Roll Number %d Is Removed Successfully \n",copy_u32IdToCheck);
				}
				ret = FIFO_OK;
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

EN_FIFO_status_t FIFO_uddtUpdateRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , uint32 copy_u32NewRollNumber)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						temp->u32RollNumber = copy_u32NewRollNumber;
						u8IdFounedFlag = 1;
						break;
					}else{/* Do Nothing */};
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Roll Number %d Not Found \n",copy_u32IdToCheck);
				}
				ret = FIFO_OK;
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

EN_FIFO_status_t FIFO_uddtUpdateFirstName(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , uint8 *copy_u8NewFirstName)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						strcpy((char *)temp->u8FirstName, (char *)copy_u8NewFirstName);
						u8IdFounedFlag = 1;
						break;
					}else{/* Do Nothing */};
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Roll Number %d Not Found \n",copy_u32IdToCheck);
				}
				ret = FIFO_OK;
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
EN_FIFO_status_t FIFO_uddtUpdateLastName(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , uint8 *copy_u8NewLasttName)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						strcpy((char *)temp->u8LastName, (char *)copy_u8NewLasttName);
						u8IdFounedFlag = 1;
						break;
					}else{/* Do Nothing */};
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Roll Number %d Not Found \n",copy_u32IdToCheck);
				}
				ret = FIFO_OK;
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
EN_FIFO_status_t FIFO_uddtUpdateGpa(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck , float32 copy_f32NewGpa)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						temp->f32Gpa = copy_f32NewGpa;
						u8IdFounedFlag = 1;
						break;
					}else{/* Do Nothing */};
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Roll Number %d Not Found \n",copy_u32IdToCheck);
				}
				ret = FIFO_OK;
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
EN_FIFO_status_t FIFO_uddtUpdateCourses(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck ,uint32 *copy_u32NewCourses)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint8 u8IdFounedFlag = 0;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
					    // Copy the values from u32ArrCourses to arrOfCourses
					    for (uint8 i = 0; i < 5; i++)
					    {
					        temp->u32CoursesIdNumber[i] = copy_u32NewCourses[i];
					    }
						u8IdFounedFlag = 1;
						break;
					}else{/* Do Nothing */};
					temp++;
				}
				if(u8IdFounedFlag == 0)
				{
					DPRINTF("[ERROR] Roll Number %d Not Found \n",copy_u32IdToCheck);
				}
				ret = FIFO_OK;
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

EN_FIFO_status_t FIFO_uddtIsValidRollNumber(ST_FIFO_Buffer_t* PS_copyUddtFifoBuf , uint32 copy_u32IdToCheck)
{
	EN_FIFO_status_t ret = FIFO_NOK;

	if((PS_copyUddtFifoBuf != PTR_NULL))
	{
		if( (PS_copyUddtFifoBuf->head != PTR_NULL) && (PS_copyUddtFifoBuf->base != PTR_NULL) && (PS_copyUddtFifoBuf->tail != PTR_NULL) )
		{
			ret = FIFO_uddtIsFull(PS_copyUddtFifoBuf);
			if(ret == FIFO_IS_EMPTY)
			{
				DPRINTF("FIFO Is Empty\n");
			}
			else
			{
				DATA_WIDTH *temp;
				uint32 i;
				temp = PS_copyUddtFifoBuf->tail;
				for(i=0 ; i<PS_copyUddtFifoBuf->count ; i++)
				{
					if(temp->u32RollNumber == copy_u32IdToCheck)
					{
						ret = FIFO_ID_VALID;
						break;
					}else{/* Do Nothing */};
					temp++;
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
