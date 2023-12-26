/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 02_Linked_List
// File          : linkedList.c
// Date          : 28 Nov 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "stdTypes.h"
#include "linkedList.h"

#define DPRINTF(...)	{fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}

EN_LINKEDLIST_status_t  LINKEDLIST_uddtAddRecord(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	ST_linkedListNode_t *p_uddtLastStudent = PTR_NULL;
	ST_linkedListNode_t *p_uddtNewStudent = PTR_NULL ;
	/* if list is empty */
	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		if(PS_copyUddtLinkedList->P_nextStudentNode == PTR_NULL)
		{
			/* create first record */
			p_uddtNewStudent = (ST_linkedListNode_t*)malloc(sizeof(ST_linkedListNode_t));
			/* assign the new student to the list */

			LINKEDLIST_uddtFillRecord(p_uddtNewStudent);

			p_uddtNewStudent->P_nextStudentNode = PTR_NULL;
			PS_copyUddtLinkedList->P_nextStudentNode = p_uddtNewStudent;
			ret = LINKED_LIST_OK;

		}
		else /* if list contain records */
		{
			/* navigate until reach to the last record */
			p_uddtLastStudent = PS_copyUddtLinkedList;
			while(p_uddtLastStudent->P_nextStudentNode != PTR_NULL)
			{
				p_uddtLastStudent = p_uddtLastStudent->P_nextStudentNode;
			}
			// create new record and store it in the next pointer

			p_uddtNewStudent = (ST_linkedListNode_t*)malloc(sizeof(ST_linkedListNode_t));


			LINKEDLIST_uddtFillRecord(p_uddtNewStudent);

			p_uddtNewStudent->P_nextStudentNode = PTR_NULL;
			p_uddtLastStudent->P_nextStudentNode = p_uddtNewStudent;

			ret = LINKED_LIST_OK;
		}
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}

	return ret;
}


EN_LINKEDLIST_status_t  LINKEDLIST_uddtFillRecord(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		uint8 temp_text[50];
		DPRINTF("\nEnter Student ID : ");
		gets((char *)temp_text);
		PS_copyUddtLinkedList->ST_uddtStudentData.ID = atoi((char *)temp_text);
		DPRINTF("\nEnter Student Full Name : ");
		gets((char *)PS_copyUddtLinkedList->ST_uddtStudentData.name);
		DPRINTF("\nEnter Student Height : ");
		gets((char *)temp_text);
		PS_copyUddtLinkedList->ST_uddtStudentData.height = atof((char *)temp_text);
		ret = LINKED_LIST_OK;
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}

	return ret;
}

EN_LINKEDLIST_status_t  LINKEDLIST_uddtDeleteRecord(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		uint8 u8TempText[50],u8FoundFlag = 0;
		uint32 u32SelectedId;

		/* get id from user  */

		DPRINTF("\nEnter Student Id To Deleted : ");
		gets((char *)u8TempText);
		u32SelectedId = atoi((char *)u8TempText);

		ST_linkedListNode_t *p_uddtPreviousStudent = PS_copyUddtLinkedList;
		ST_linkedListNode_t *p_uddtSelectedStudent = PS_copyUddtLinkedList->P_nextStudentNode ;

		/* search in recored to find the selected id */

		while(p_uddtSelectedStudent)
		{
			/* compare recored id with the selected id */
			if(p_uddtSelectedStudent->ST_uddtStudentData.ID == u32SelectedId)
			{

				u8FoundFlag = 1;
				p_uddtPreviousStudent->P_nextStudentNode = p_uddtSelectedStudent->P_nextStudentNode;
				free(p_uddtSelectedStudent);
				break;
			}
			else
			{
				p_uddtPreviousStudent = p_uddtSelectedStudent;
			}
			/* store previous record pointer */
			p_uddtSelectedStudent = p_uddtSelectedStudent->P_nextStudentNode;
		}
		if(u8FoundFlag == 0)
			DPRINTF("\nCannot Find Student Id ");

		ret = LINKED_LIST_OK;
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}
	return ret ;
}

EN_LINKEDLIST_status_t  LINKEDLIST_uddtViewRecords(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{

		if(PS_copyUddtLinkedList->P_nextStudentNode != PTR_NULL)
		{
			uint8 u8Count = 0;

			ST_linkedListNode_t *p_uddtCurrentStudent = PS_copyUddtLinkedList->P_nextStudentNode;

			while(p_uddtCurrentStudent)
			{
				DPRINTF("\nRecord Number : %d",u8Count+1);
				DPRINTF("\nID : %d",p_uddtCurrentStudent->ST_uddtStudentData.ID);
				DPRINTF("\nName : %s",p_uddtCurrentStudent->ST_uddtStudentData.name);
				DPRINTF("\nHeight : %f",p_uddtCurrentStudent->ST_uddtStudentData.height);

				p_uddtCurrentStudent = p_uddtCurrentStudent->P_nextStudentNode;
				u8Count++;
			}
			ret = LINKED_LIST_OK;
		}
		else
		{
			DPRINTF("\nEmpty List");
			ret = LINKED_LIST_IS_EMPTY;
		}
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}

	return ret;
}


EN_LINKEDLIST_status_t  LINKEDLIST_uddtDeleteAllRecords(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		if(PS_copyUddtLinkedList->P_nextStudentNode != PTR_NULL)
		{
			ST_linkedListNode_t *p_uddtCurrentStudent = PS_copyUddtLinkedList->P_nextStudentNode;

			while(p_uddtCurrentStudent)
			{
				ST_linkedListNode_t *p_uddtTempStudent = p_uddtCurrentStudent;
				p_uddtCurrentStudent = p_uddtCurrentStudent->P_nextStudentNode;
				free(p_uddtTempStudent);
			}
			PS_copyUddtLinkedList->P_nextStudentNode = PTR_NULL;
			ret = LINKED_LIST_OK;
		}
		else
		{
			DPRINTF("\nEmpty List");
			ret = LINKED_LIST_IS_EMPTY;
		}
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}
	return ret;
}


EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetNthNode(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		uint8 u8TempText[50],u8FoundFlag = 0;
		uint32 u32SelectedIndex,u32Count = 0;

		/* get id from user  */

		DPRINTF("\nEnter Node Index : ");
		gets((char *)u8TempText);
		u32SelectedIndex = atoi((char *)u8TempText);
		u32SelectedIndex--;
		ST_linkedListNode_t *p_uddtSelectedStudent = PS_copyUddtLinkedList->P_nextStudentNode ;

		/* search in recored to find the selected id */

		while(p_uddtSelectedStudent)
		{
			/* compare recored id with the selected id */
			if( u32SelectedIndex == u32Count )
			{
				u8FoundFlag = 1;
				DPRINTF("\nNode Index : %d",u32SelectedIndex+1);
				DPRINTF("\nID : %d",p_uddtSelectedStudent->ST_uddtStudentData.ID);
				DPRINTF("\nName : %s",p_uddtSelectedStudent->ST_uddtStudentData.name);
				DPRINTF("\nHeight : %f",p_uddtSelectedStudent->ST_uddtStudentData.height);
				break;
			}
			else
			{
				/* Do Nothing */
			}
			p_uddtSelectedStudent = p_uddtSelectedStudent->P_nextStudentNode;
			u32Count++;
		}
		if(u8FoundFlag == 0)
			DPRINTF("\nThis Node Index Is Empty ");

		ret = LINKED_LIST_OK;
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}
	return ret ;
}

EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetLengthIterative(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		uint8 u8FoundFlag = 0;
		uint32 u32Count = 0;

		ST_linkedListNode_t *p_uddtSelectedStudent = PS_copyUddtLinkedList->P_nextStudentNode ;

		while(p_uddtSelectedStudent)
		{
			u8FoundFlag = 1;
			p_uddtSelectedStudent = p_uddtSelectedStudent->P_nextStudentNode;
			u32Count++;
		}
		if(u8FoundFlag == 0)
		{
			DPRINTF("\nThis List Is Empty ");
		}
		else
		{
			DPRINTF("\nList Contain %d Node ",u32Count);
		}

		ret = LINKED_LIST_OK;
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}
	return ret ;
}

uint32  LINKEDLIST_u32GetLengthRecursive(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		ST_linkedListNode_t *p_uddtSelectedStudent = PS_copyUddtLinkedList;

		if(p_uddtSelectedStudent->P_nextStudentNode != PTR_NULL)
		{
			return 1+LINKEDLIST_u32GetLengthRecursive(p_uddtSelectedStudent->P_nextStudentNode);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		DPRINTF("\nThis List Is NULL ");
		return 0;
	}
}


EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetNthNodeFromTheEnd(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		uint8 u8TempText[50],u8FoundFlag = 0;
		uint32 u32SelectedIndex,u32Count = 0;

		/* get id from user  */

		DPRINTF("\nEnter Node Index From The End : ");
		gets((char *)u8TempText);
		u32SelectedIndex = atoi((char *)u8TempText);
		u32SelectedIndex--;
		ST_linkedListNode_t *p_uddtSelectedIndex = PS_copyUddtLinkedList->P_nextStudentNode ;
		ST_linkedListNode_t *p_uddtreference = PS_copyUddtLinkedList->P_nextStudentNode ;

		while(p_uddtreference->P_nextStudentNode != PTR_NULL)
		{
			if(u32SelectedIndex == u32Count )
			{
				break;
			}
			else
			{
				p_uddtreference = p_uddtreference->P_nextStudentNode;
				u32Count++;
			}
		}

		while(p_uddtreference->P_nextStudentNode != PTR_NULL)
		{
			p_uddtreference = p_uddtreference->P_nextStudentNode;
			p_uddtSelectedIndex = p_uddtSelectedIndex->P_nextStudentNode;
		}

		if( p_uddtSelectedIndex  != PTR_NULL)
		{
			u8FoundFlag = 1;
			DPRINTF("\nNode Index From The End : %d",u32SelectedIndex+1);
			DPRINTF("\nID : %d",p_uddtSelectedIndex->ST_uddtStudentData.ID);
			DPRINTF("\nName : %s",p_uddtSelectedIndex->ST_uddtStudentData.name);
			DPRINTF("\nHeight : %f",p_uddtSelectedIndex->ST_uddtStudentData.height);
		}
		else
		{
			/* Do Nothing */
		}

		if(u8FoundFlag == 0)
			DPRINTF("\nThis Node Index Is Empty ");

	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}
	return ret ;
}

EN_LINKEDLIST_status_t  LINKEDLIST_uddtGetMiddleNode(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{
		uint8 u8FoundFlag = 0;
		uint32 u32Count = 1;


		ST_linkedListNode_t *p_uddtSlow = PS_copyUddtLinkedList->P_nextStudentNode ;
		ST_linkedListNode_t *p_uddtFast = PS_copyUddtLinkedList->P_nextStudentNode ;

		while((p_uddtFast->P_nextStudentNode != PTR_NULL) && (p_uddtFast->P_nextStudentNode->P_nextStudentNode != PTR_NULL))
		{
			p_uddtFast = p_uddtFast->P_nextStudentNode->P_nextStudentNode;
			p_uddtSlow = p_uddtSlow->P_nextStudentNode;
			u32Count++;
		}

		if( p_uddtSlow  != PTR_NULL)
		{
			u8FoundFlag = 1;
			DPRINTF("\nMiddle Node In Index : %d",u32Count);
			DPRINTF("\nID : %d",p_uddtSlow->ST_uddtStudentData.ID);
			DPRINTF("\nName : %s",p_uddtSlow->ST_uddtStudentData.name);
			DPRINTF("\nHeight : %f",p_uddtSlow->ST_uddtStudentData.height);
		}
		else
		{
			/* Do Nothing */
		}

		if(u8FoundFlag == 0)
			DPRINTF("\nThis Node Index Is Empty ");

	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}
	return ret ;
}

EN_LINKEDLIST_status_t  LINKEDLIST_uddtDetectLoop(ST_linkedListNode_t *PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if(PS_copyUddtLinkedList != PTR_NULL)
	{

		ST_linkedListNode_t *p_uddtFast = PS_copyUddtLinkedList->P_nextStudentNode ;
		ST_linkedListNode_t *p_uddtSlow = PS_copyUddtLinkedList->P_nextStudentNode ;


		while((p_uddtFast->P_nextStudentNode != PTR_NULL) && (p_uddtSlow->P_nextStudentNode != PTR_NULL))
		{
			p_uddtSlow = p_uddtSlow->P_nextStudentNode;
			p_uddtFast = p_uddtFast->P_nextStudentNode->P_nextStudentNode;

			if(p_uddtFast == p_uddtSlow)
			{
				DPRINTF("\nFound Loop");
				ret = LINKED_LIST_FOUND_LOOP;
				break;
			}
			else
			{
				ret = LINKED_LIST_OK;
			}
		}

		if(ret == LINKED_LIST_OK)
			DPRINTF("\nNo Loop Found");

	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}
	return ret ;
}


//EN_LINKEDLIST_status_t LINKEDLIST_uddtReverseRecords(ST_linkedListNode_t* PS_copyUddtLinkedList)
//{
//    EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;
//
//    if (PS_copyUddtLinkedList != PTR_NULL)
//    {
//        ST_linkedListNode_t* p_uddtnew = PTR_NULL;
//        ST_linkedListNode_t* p_uddtold = PS_copyUddtLinkedList;
//        ST_linkedListNode_t* p_temp = PTR_NULL;
//
//        uint32 size = LINKEDLIST_u32GetLengthRecursive(PS_copyUddtLinkedList);
//
//        for(uint32 i = 0; i < size; i++)
//        {
//            p_temp = p_uddtnew;
//            p_uddtnew = (ST_linkedListNode_t*)malloc(sizeof(ST_linkedListNode_t));
//
//            // Link the new node to the reversed list
//            p_uddtnew->P_nextStudentNode = p_temp;
//
//            for(uint32 j = size - i - 1; j > 0; j--)
//            {
//                p_uddtold = p_uddtold->P_nextStudentNode;
//            }
//
//            // Copy the data from the old node to the new node
//            p_uddtnew->ST_uddtStudentData = p_uddtold->ST_uddtStudentData;
//        }
//
//        // Now, p_uddtnew points to the head of the reversed list
//        LINKEDLIST_uddtViewRecords(p_uddtnew);
//    }
//    else
//    {
//        ret = LINKED_LIST_PTR_NULL;
//    }
//
//    return ret;
//}


EN_LINKEDLIST_status_t LINKEDLIST_uddtReverseRecords(ST_linkedListNode_t* PS_copyUddtLinkedList)
{
	EN_LINKEDLIST_status_t ret = LINKED_LIST_NOK;

	if (PS_copyUddtLinkedList != PTR_NULL)
	{
		ST_linkedListNode_t* p_uddtnew = PTR_NULL;
		ST_linkedListNode_t* p_uddtold = PS_copyUddtLinkedList->P_nextStudentNode;
		ST_linkedListNode_t* p_temp = PTR_NULL;

		while (p_uddtold != PTR_NULL)
		{
			p_temp = p_uddtnew;
			p_uddtnew = (ST_linkedListNode_t*)malloc(sizeof(ST_linkedListNode_t));

			// Copy the data from the old node to the new node
			p_uddtnew->ST_uddtStudentData = p_uddtold->ST_uddtStudentData;

			// Link the new node to the reversed list
			p_uddtnew->P_nextStudentNode = p_temp;

			// Move to the next node in the original list
			p_uddtold = p_uddtold->P_nextStudentNode;
		}

		// Now, p_uddtnew points to the head of the reversed list
		LINKEDLIST_uddtViewRecords(p_uddtnew);

		PS_copyUddtLinkedList = p_uddtnew;
	}
	else
	{
		ret = LINKED_LIST_PTR_NULL;
	}

	return ret;
}




