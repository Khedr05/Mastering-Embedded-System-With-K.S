/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "25-12-2022"

Program : "c program to get size of struct and union"

*/

#include<stdio.h>

union job
{
	char name[32];
	float salary;
	int worker_no;
}u;

struct job1
{
	char name[32];
	float salary;
	int worker_no;
}s;

void main(void)
{
	printf("size of union = %d\n",sizeof(u)); // size of the biggest data type -> 
										   //char name[32] -> size of union -> 32*1=32byte 

	printf("size of struct = %d",sizeof(s));  // word size = size of the biggest data type -> float salary = 4 byte  
											 // -> char name[32] = 32*1=32 byte
											// -> float salary = 4 byte  
										   // -> int worker_no = 4 byte
										  // -> total = 40 byte
}
