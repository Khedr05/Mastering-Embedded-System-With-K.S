/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 02_Linked_List
// File          : main.c
// Date          : 28 Nov 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#define DPRINTF(...)	{fflush(stdout);\
						 fflush(stdin);\
						 printf(__VA_ARGS__);\
						 fflush(stdout);\
						 fflush(stdin);}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdTypes.h"
#include "linkedList.h"

int main(void)
{
	uint8 u8TempText[50];
	ST_linkedListNode_t gp_uddtStudentsDB;
	gp_uddtStudentsDB.P_nextStudentNode = PTR_NULL;
	while(1)
	{
		DPRINTF("\n=============================\n");
		DPRINTF("\nChosse One Of The Following Option : ");
		DPRINTF("\n1  - Add Student ");
		DPRINTF("\n2  - Delete Student ");
		DPRINTF("\n3  - View Students ");
		DPRINTF("\n4  - Delete All Students ");
		DPRINTF("\n5  - Get Nth Node ");
		DPRINTF("\n6  - Get List Size Iterative ");
		DPRINTF("\n7  - Get List Size Recursive ");
		DPRINTF("\n8  - Get Nth Node From The End ");
		DPRINTF("\n9  - Get Middle Node ");
		DPRINTF("\n10 - Check For Loop ");
		DPRINTF("\n11 - Reverse The List ");
		DPRINTF("\nEnter Your Option Number : ");

		gets((char *)u8TempText);
		DPRINTF("\n=============================\n");

		switch(atoi((char *)u8TempText))
		{
		case 1:
		{
			LINKEDLIST_uddtAddRecord(&gp_uddtStudentsDB);
			break;
		}
		case 2:
		{
			LINKEDLIST_uddtDeleteRecord(&gp_uddtStudentsDB);
			break;
		}
		case 3:
		{
			LINKEDLIST_uddtViewRecords(&gp_uddtStudentsDB);
			break;
		}
		case 4:
		{
			LINKEDLIST_uddtDeleteAllRecords(&gp_uddtStudentsDB);
			break;
		}
		case 5:
		{
			LINKEDLIST_uddtGetNthNode(&gp_uddtStudentsDB);
			break;
		}
		case 6:
		{
			LINKEDLIST_uddtGetLengthIterative(&gp_uddtStudentsDB);
			break;
		}
		case 7:
		{
			uint32 count = LINKEDLIST_u32GetLengthRecursive(&gp_uddtStudentsDB);
			if(count != 0)
			{
				DPRINTF("\nList Contain %d Node ",count);
			}
			else
			{
				DPRINTF("\nThis List Is Empty ");
			}
			break;
		}
		case 8:
		{
			LINKEDLIST_uddtGetNthNodeFromTheEnd(&gp_uddtStudentsDB);
			break;
		}
		case 9:
		{
			LINKEDLIST_uddtGetMiddleNode(&gp_uddtStudentsDB);
			break;
		}
		case 10:
		{
			LINKEDLIST_uddtDetectLoop(&gp_uddtStudentsDB);
			break;
		}
		case 11:
		{
			LINKEDLIST_uddtReverseRecords(&gp_uddtStudentsDB);
			break;
		}

		}
	}

	return 0;
}
