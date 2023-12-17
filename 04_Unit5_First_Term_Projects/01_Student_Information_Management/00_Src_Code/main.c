/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Student_Information_Management
// File          : main.c
// Date          : Dec 12, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "studentDbOptions.h"

int main(void)
{
	uint8 choice;
	STUDENT_vInitDataBase();
	DPRINTF("Welcome To The Student Management System\n");
	DPRINTF("_________________________________________________________\n");
	while(1)
	{
		system("cls");
		DPRINTF("Choose The Task That You Want To Perform :\n");
		DPRINTF("1  - Add    The Student Details Manually\n");
		DPRINTF("2  - Add    The Student Details From Text File\n");
		DPRINTF("3  - Find   The Student Details By Roll Number\n");
		DPRINTF("4  - Find   The Student Details By First Name\n");
		DPRINTF("5  - Find   The Student Details By Course Id\n");
		DPRINTF("6  - Find   The Total Number Of Students\n");
		DPRINTF("7  - Delete The Students Details By Roll Number\n");
		DPRINTF("8  - Update The Students Details By Roll Number\n");
		DPRINTF("9  - Show   All Information\n");
		DPRINTF("10 - To Exit\n");
		DPRINTF("Enter Your Choice To Perform The Task :\n");
		scanf("%d",(int *)&choice);
		switch(choice){
		case 1:
			system("cls");
			STUDENT_vAddUser();
			PAUSE();
			break;
		case 2:
			system("cls");
			STUDENT_vAddUsersByFile();
			PAUSE();
			break;
		case 3:
			system("cls");
			STUDENT_vFindByRollNumber();
			PAUSE();
			break;
		case 4:
			system("cls");
			STUDENT_vFindByFirstName();
			PAUSE();
			break;
		case 5:
			system("cls");
			STUDENT_vFindByCourseId();
			PAUSE();
			break;
		case 6:
			system("cls");
			STUDENT_vPrintDbInfo();
			PAUSE();
			break;
		case 7:
			system("cls");
			STUDENT_vDeleteUser();
			PAUSE();
			break;
		case 8:
			system("cls");
			STUDENT_vUpdateUser();
			PAUSE();
			break;
		case 9:
			system("cls");
			STUDENT_vPrintAllStudents();
			PAUSE();
			break;
		case 10:
			system("cls");
			DPRINTF("Exiting.....\n\n");
			exit(0);
			break;
		default:
			DPRINTF("[ERROR] Invalid Choice Try Again..... \n\n");
			PAUSE();
			break;
		}
	}
	return 0;
}









