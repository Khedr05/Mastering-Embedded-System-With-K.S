/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "21-12-2022"

Program : "count number of ones bit between two zeros"
*/



#include<stdio.h>

char maxOnes(char a);

void main(void)
{
	int num;
	printf("enter number \n");
	scanf("%d",&num);
	printf("Max Ones = %d",maxOnes(num));
}


char maxOnes(char a)
{
	char counter=0;

	while(a!=0)
	{
		a = (a &(a<<1));
		counter++;
	}
	return counter;
}