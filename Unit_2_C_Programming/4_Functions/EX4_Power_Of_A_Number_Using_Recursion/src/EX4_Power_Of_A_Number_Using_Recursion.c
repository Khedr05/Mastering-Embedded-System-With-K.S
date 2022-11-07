/*
 ============================================================================
 Name        : EX4_Power_Of_A_Number_Using_Recursion.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int pow(int base,int power);

int main(void) {
	int base,power,res=1;
	printf("Enter The Base \n");
	fflush(stdout);
	scanf("%d",&base);
	printf("Enter The Number Of Power \n");
	fflush(stdout);
	scanf("%d",&power);

	res=pow(base,power);
	printf("Power %d Of Base %d Equal %d",power,base,res);
	fflush(stdout);
}

int pow(int base , int power)
{

	if(power != 0)
	{
		return base*pow(base,power-1);
	}
	else
		return 1;

}
