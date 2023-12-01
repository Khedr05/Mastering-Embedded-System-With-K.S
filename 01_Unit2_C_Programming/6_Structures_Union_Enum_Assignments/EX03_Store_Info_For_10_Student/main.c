/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "25-12-2022"

Program : "c program to save student info for 10 student using struct"

*/

#include<stdio.h>


typedef struct studentInfo
{
	char name[20];
	int rollNumber;
	float mark;
}student;


void main(void)
{
	student arrOfStudent[10];

	printf("Enter Info of student\n");
	for(int i=0;i<10;i++)
	{
		printf("For Roll Number: %d \n",i+1);
		arrOfStudent[i].rollNumber = i; 
		printf("Enter Name of student: %d \n",i+1);
		scanf("%s",arrOfStudent[i].name);
		printf("Enter Mark of student : %d \n",i+1);
		scanf("%f",&arrOfStudent[i].mark);	
	}

	printf("Displaying All Student Info \n");

	for(int i=0;i<10;i++)
	{
		printf("Roll Number of student :%d\n",arrOfStudent[i].rollNumber);
		printf("Name of student :%s\n",arrOfStudent[i].name);
		printf("Mark of student :%f\n",arrOfStudent[i].mark);
	}
}