/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "25-12-2022"

Program : "c program to save student info using struct"

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
	student sherif;

	printf("Enter Info of student\n");
	printf("Enter Name of student :");
	scanf("%s",sherif.name);
	printf("Enter Roll Number of student :");
	scanf("%d",&sherif.rollNumber);
	printf("Enter Mark of student :");
	scanf("%f",&sherif.mark);

	printf("Name of student :%s\n",sherif.name);
	printf("Roll Number of student :%d\n",sherif.rollNumber);
	printf("Mark of student :%f\n",sherif.mark);


}