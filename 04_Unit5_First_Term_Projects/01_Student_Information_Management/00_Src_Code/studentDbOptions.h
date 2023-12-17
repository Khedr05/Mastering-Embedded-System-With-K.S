/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Student_Information_Management
// File          : studentDbOptions.h
// Date          : Dec 12, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#ifndef STUDENTDBOPTIONS_H_
#define STUDENTDBOPTIONS_H_
#include "stdTypes.h"


typedef struct
{
	uint8 u8FirstName[50];
	uint8 u8LastName[50];
	uint32 u32RollNumber;
	float32 f32Gpa;
	uint32 u32CoursesIdNumber[5];
}ST_studentInfo_t;

void STUDENT_vInitDataBase(void);
void STUDENT_vAddUsersByFile(void);
void STUDENT_vAddUser(void);
void STUDENT_vFindByRollNumber(void);
void STUDENT_vFindByFirstName(void);
void STUDENT_vFindByCourseId(void);
void STUDENT_vPrintAllStudents(void);
void STUDENT_vPrintDbInfo(void);
void STUDENT_vDeleteUser(void);
void STUDENT_vUpdateUser(void);


#endif /* STUDENTDBOPTIONS_H_ */
