/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Student_Information_Management
// File          : studentDbOptions.c
// Date          : Dec 12, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studentDbOptions.h"
#include "fifo.h"




ST_FIFO_Buffer_t uddtStudentsBuffer;
ST_studentInfo_t uddtStudentDb[50];

static void convertToLower(char *str) {
	while (*str) {
		*str = (*str >= 'A' && *str <= 'Z') ? (*str + ('a' - 'A')) : *str;
		str++;
	}
}

static uint32 u32GetRollNumber(void)
{
	// Declare a temporary input buffer
	uint8 u8TempInput[50];
	uint32 u32RollNumber = 0;
	// Declare a variable to store the result of FIFO functions
	EN_FIFO_status_t FifoRet = FIFO_NOK;
	// Prompt the user to enter the student's roll number
	DPRINTF("Enter Student Roll Number : ");

	// Loop until valid roll number is entered
	while (1) {
		// Read user input as a string
		fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);

		// Convert the string to an integer
		char *endptr;
		u32RollNumber = (uint32)strtol((char *)u8TempInput, &endptr, 10);

		// Check if the conversion was successful and roll number is unique
		if (*endptr == '\0' || *endptr == '\n') {
			FifoRet = FIFO_uddtIsUniqueRollNumber(&uddtStudentsBuffer,u32RollNumber);
			if (FifoRet == FIFO_ID_IS_UNIQUE) {
				break;  // Exit the loop if roll number is valid and unique
			} else {
				DPRINTF("[ERROR] Roll Number Is Not Unique. Try Again With a Different Roll Number.\n");
			}
		} else {
			DPRINTF("[ERROR] Invalid Roll Number. Please enter a valid integer.\n");
		}
	}
	return u32RollNumber;
}


static void vGetFirstName(uint8 *u8FirstName)
{
	uint8 u8Name[50];
	// Prompt the user to enter the first name
	DPRINTF("Enter Student First Name : ");
	// Read user input as a string and copy to the student structure
	fgets((char *)u8Name, sizeof(u8Name), stdin);
	// Remove the newline character at the end (if present)
	u8Name[strcspn((char *)u8Name, "\n")] = '\0';
	u8Name[sizeof(u8Name) - 1] = '\0';
	convertToLower((char *)u8Name);
	strcpy((char *)u8FirstName, (char *)u8Name);
}

static void vGetLastName(uint8 *u8LastName)
{
	uint8 u8Name[50];
	// Prompt the user to enter the first name
	DPRINTF("Enter Student Last Name : ");
	// Read user input as a string and copy to the student structure
	fgets((char *)u8Name, sizeof(u8Name), stdin);
	// Remove the newline character at the end (if present)
	u8Name[strcspn((char *)u8Name, "\n")] = '\0';
	u8Name[sizeof(u8Name) - 1] = '\0';
	convertToLower((char *)u8Name);
	strcpy((char *)u8LastName, (char *)u8Name);
}

static float32 f32GetGpa(void)
{
	// Declare a temporary input buffer
	uint8 u8TempInput[50];
	float32 u32Gpa = 0.0;
	// Prompt the user to enter the GPA
	DPRINTF("Enter Student GPA : ");

	// Loop until a valid GPA is entered
	while (1) {
		// Read user input as a string and convert to float
		fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);
		char *endptr;
		u32Gpa = strtof((char *)u8TempInput, &endptr);

		// Check if the conversion was successful
		if (*endptr == '\0' || *endptr == '\n') {
			break;  // Exit the loop if GPA is valid
		} else {
			DPRINTF("[ERROR] Invalid GPA. Please enter a valid float.\n");
		}
	}
	return u32Gpa;
}

static void vGetCoursesId(uint32 *arrOfCourses)
{
	// Declare a temporary input buffer
	uint8 u8TempInput[50];
	uint32 u32ArrCourses[5];
	// Loop to get course codes from the user
	for (uint8 i = 0; i < 5; i++) {
		DPRINTF("Enter Course %d Id : ", i + 1);

		// Loop until a valid course code is entered
		while (1) {
			// Read user input as a string and convert to integer
			fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);
			char *endptr;
			u32ArrCourses[i] = (uint32)strtol((char *)u8TempInput, &endptr, 10);

			// Check if the conversion was successful
			if (*endptr == '\0' || *endptr == '\n') {
				break;  // Exit the loop if course code is valid
			} else {
				DPRINTF("[ERROR] Invalid Course Code. Please enter a valid integer.\n");
			}
		}
		// Copy the values from u32ArrCourses to arrOfCourses
		for (uint8 i = 0; i < 5; i++)
		{
			arrOfCourses[i] = u32ArrCourses[i];
		}
	}
}



void STUDENT_vInitDataBase(void)
{
	/* initilaize the buffer */
	FIFO_uddtInitBuffer(&uddtStudentsBuffer , uddtStudentDb , 50);
}

void STUDENT_vAddUsersByFile(void)
{
	ST_studentInfo_t uddtNewStudent;
	// Declare a variable to store the result of FIFO functions
	EN_FIFO_status_t FifoRet = FIFO_NOK;
    FILE* file = fopen("studentDb.txt", "r");
    if (!file) {
        DPRINTF("[ERROR] Unable to open file: %s\n", "studentDb.txt");
        return;
    }
    // Read student information from the file and add to the database
    while (fscanf(file, "%u %s %s %f %u %u %u %u %u",
            &uddtNewStudent.u32RollNumber,
            uddtNewStudent.u8FirstName,
            uddtNewStudent.u8LastName,
            &uddtNewStudent.f32Gpa,
            &uddtNewStudent.u32CoursesIdNumber[0],
            &uddtNewStudent.u32CoursesIdNumber[1],
            &uddtNewStudent.u32CoursesIdNumber[2],
            &uddtNewStudent.u32CoursesIdNumber[3],
            &uddtNewStudent.u32CoursesIdNumber[4]) == 9) {

        // Add the student to the buffer
		FifoRet = FIFO_uddtIsUniqueRollNumber(&uddtStudentsBuffer,uddtNewStudent.u32RollNumber);
		if(FifoRet == FIFO_ID_IS_UNIQUE)
		{
	        FIFO_uddtPushData(&uddtStudentsBuffer, uddtNewStudent);
	    	DPRINTF("[INFO] Student With Roll Number %d Is Added Successfully\n",uddtNewStudent.u32RollNumber);
	    	FIFO_uddtShowDbStatistics(&uddtStudentsBuffer);
		}
		else
		{
	    	DPRINTF("[ERROR] Student With Roll Number %d Is Not Added Taken Roll Number\n",uddtNewStudent.u32RollNumber);
		}
    }

    fclose(file);
}

/*
 * STUDENT_vAddUser - Function to add a new student to the database
 */
void STUDENT_vAddUser(void) {
	// Declare a new student and temporary input buffer
	ST_studentInfo_t uddtNewStudent;
	DPRINTF("___________________________________________________________\n");
	DPRINTF("Adding New Student To Your DB \n\n");

	uddtNewStudent.u32RollNumber = u32GetRollNumber();
	vGetFirstName(uddtNewStudent.u8FirstName);
	vGetLastName(uddtNewStudent.u8LastName);
	uddtNewStudent.f32Gpa = f32GetGpa();
	vGetCoursesId(uddtNewStudent.u32CoursesIdNumber);

	// Push the new student into the buffer
	FIFO_uddtPushData(&uddtStudentsBuffer, uddtNewStudent);
	DPRINTF("[INFO] Student Details Is Added Successfully\n");
	FIFO_uddtShowDbStatistics(&uddtStudentsBuffer);
}


void STUDENT_vFindByRollNumber(void)
{
	/* temp array to take user input from keyboard and store it */
	uint8 u8TempInput[50];
	/* temp uint32 variable to store integer id */
	uint32 u32RollNumber = 0;
	// Prompt the user to enter the student's roll number
	DPRINTF("Enter Student Roll Number : ");

	// Loop until valid roll number is entered
	while (1) {
		// Read user input as a string
		fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);

		// Convert the string to an integer
		char *endptr;
		u32RollNumber = (uint32)strtol((char *)u8TempInput, &endptr, 10);

		// Check if the conversion was successful and roll number is unique
		if (*endptr == '\0' || *endptr == '\n') {
			FIFO_uddtFindByRollNumber(&uddtStudentsBuffer ,u32RollNumber);
			break;
		}
		else
		{
			DPRINTF("[ERROR] Invalid Roll Number. Please enter a valid integer.\n");
		}
	}
}


void STUDENT_vFindByFirstName(void)
{
	/* temp array to take user input from the keyboard and store it */
	uint8 u8TempInput[50];

	// Prompt the user to enter the student's first name
	DPRINTF("Enter Student First Name : ");

	// Loop until a valid first name is entered
	while (1) {
		// Read user input as a string
		fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);

		// Remove the newline character at the end (if present)
		u8TempInput[strcspn((char *)u8TempInput, "\n")] = '\0';
		// Copy the input string to the first name variable
		u8TempInput[sizeof(u8TempInput) - 1] = '\0';

		// Check if the first name is not empty
		if (strlen((char *)u8TempInput) > 0) {
			convertToLower((char *)u8TempInput);
			// Call the function to find and print student details by first name
			FIFO_uddtFindByFirstName(&uddtStudentsBuffer, u8TempInput);
			break;
		} else {
			DPRINTF("[ERROR] Invalid First Name. Please enter a non-empty string.\n");
		}
	}
}


void STUDENT_vFindByCourseId(void)
{
	/* temp array to take user input from keyboard and store it */
	uint8 u8TempInput[50];
	/* temp uint32 variable to store integer id */
	uint32 u32CourseId = 0;
	// Prompt the user to enter the student's roll number
	DPRINTF("Enter Course Id : ");

	// Loop until valid roll number is entered
	while (1) {
		// Read user input as a string
		fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);

		// Convert the string to an integer
		char *endptr;
		u32CourseId = (uint32)strtol((char *)u8TempInput, &endptr, 10);

		// Check if the conversion was successful and roll number is unique
		if (*endptr == '\0' || *endptr == '\n') {
			FIFO_uddtFindByCourseId(&uddtStudentsBuffer ,u32CourseId);
			break;
		}
		else
		{
			DPRINTF("[ERROR] Invalid Roll Number. Please enter a valid integer.\n");
		}
	}
}

void STUDENT_vPrintDbInfo(void)
{
	FIFO_uddtShowDbStatistics(&uddtStudentsBuffer);
}

void STUDENT_vPrintAllStudents(void)
{
	FIFO_uddtPrintBuffer(&uddtStudentsBuffer);
}

void STUDENT_vDeleteUser(void)
{
	/* temp array to take user input from keyboard and store it */
	uint8 u8TempInput[50];
	/* temp uint32 variable to store integer id */
	uint32 u32RollNumber = 0;
	// Prompt the user to enter the student's roll number
	DPRINTF("Enter The Roll Number Which You Want To Delete : ");

	// Loop until valid roll number is entered
	while (1) {
		// Read user input as a string
		fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);

		// Convert the string to an integer
		char *endptr;
		u32RollNumber = (uint32)strtol((char *)u8TempInput, &endptr, 10);

		// Check if the conversion was successful and roll number is unique
		if (*endptr == '\0' || *endptr == '\n') {
			FIFO_uddtDeleteByRollNumber(&uddtStudentsBuffer ,u32RollNumber);
			break;
		}
		else
		{
			DPRINTF("[ERROR] Invalid Roll Number. Please enter a valid integer.\n");
		}
	}
}

void STUDENT_vUpdateUser(void)
{
	/* temp array to take user input from keyboard and store it */
	uint8 u8TempInput[50],u8Choice=0;
	/* temp uint32 variable to store integer id */
	uint32 u32RollNumber = 0;
	// Declare a variable to store the result of FIFO functions
	EN_FIFO_status_t FifoRet = FIFO_NOK;
	// Prompt the user to enter the student's roll number
	DPRINTF("Enter Student Roll Number To Update Info : ");

	// Loop until valid roll number is entered
	while (1) {
		// Read user input as a string
		fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);

		// Convert the string to an integer
		char *endptr;
		u32RollNumber = (uint32)strtol((char *)u8TempInput, &endptr, 10);

		// Check if the conversion was successful and roll number is unique
		if (*endptr == '\0' || *endptr == '\n') {

			FifoRet = FIFO_uddtIsValidRollNumber(&uddtStudentsBuffer,u32RollNumber);

			if(FifoRet == FIFO_ID_VALID)
			{
				DPRINTF("1 - Roll Number\n");
				DPRINTF("2 - First Name\n");
				DPRINTF("3 - Last Name\n");
				DPRINTF("4 - GPA\n");
				DPRINTF("5 - Courses\n");
				DPRINTF("Enter Any Key To Exit\n");
				while(1)
				{
					// Read user input as a string
					fgets((char *)u8TempInput, sizeof(u8TempInput), stdin);
					// Convert the string to an integer
					char *endptr;
					u8Choice = (uint32)strtol((char *)u8TempInput, &endptr, 10);

					// Check if the conversion was successful
					if (*endptr == '\0' || *endptr == '\n')
					{
						switch(u8Choice)
						{
						case 1:
						{
							FIFO_uddtUpdateRollNumber(&uddtStudentsBuffer,u32RollNumber,u32GetRollNumber());
							DPRINTF("[INFO] Student With Roll Number %d Its Roll Number Is Updated\n",u32RollNumber);
							break;
						}
						case 2:
						{
							uint8 u8TempOfName[50];
							vGetFirstName(u8TempOfName);
							FIFO_uddtUpdateFirstName(&uddtStudentsBuffer,u32RollNumber,u8TempOfName);
							DPRINTF("[INFO] Student With Roll Number %d Its First Name Is Updated\n",u32RollNumber);
							break;
						}
						case 3:
						{
							uint8 u8TempOfName[50];
							vGetLastName(u8TempOfName);
							FIFO_uddtUpdateLastName(&uddtStudentsBuffer,u32RollNumber,u8TempOfName);
							DPRINTF("[INFO] Student With Roll Number %d Its Last Name Is Updated\n",u32RollNumber);
							break;
						}
						case 4:
						{
							FIFO_uddtUpdateGpa(&uddtStudentsBuffer,u32RollNumber,f32GetGpa());
							DPRINTF("[INFO] Student With Roll Number %d Its Gpa Is Updated\n",u32RollNumber);
							break;
						}
						case 5:
						{
							uint32 u32TempOfCourses[5];
							vGetCoursesId(u32TempOfCourses);
							FIFO_uddtUpdateCourses(&uddtStudentsBuffer,u32RollNumber,u32TempOfCourses);
							DPRINTF("[INFO] Student With Roll Number %d Its Courses Id Is Updated\n",u32RollNumber);
							break;
						}
						default :
						{
							DPRINTF("[INFO] Process Is Cancelled \n");
							break;
						}
						}
						break;
					}
					else
					{
						DPRINTF("[ERROR] Invalid Choice. Please enter a valid integer.\n");
					}
				}
				break;
			}
			else
			{
				DPRINTF("[ERROR] Roll Number %d Not Found \n",u32RollNumber);
			}
		}
		else
		{
			DPRINTF("[ERROR] Invalid Roll Number. Please enter a valid integer.\n");
		}
	}
}


