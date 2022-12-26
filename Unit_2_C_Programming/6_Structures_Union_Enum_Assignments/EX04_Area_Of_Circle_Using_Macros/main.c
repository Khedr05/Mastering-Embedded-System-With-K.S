/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "25-12-2022"

Program : "c program to get area of circle using macros"

*/

#include<stdio.h>
#define pi 3.14
#define area(r) (pi*(r)*(r))

void main(void)
{
	int red;
	float area;
	printf("Enter redius of circle \n");
	scanf("%d",&red);
	area = area(red);
	printf("Area of circle = %0.2f",area);
}