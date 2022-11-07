/*
 ============================================================================
 Name        : EX2_Factorial_Using_Recursion.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int fac(int num);

int main(void) {

	int x=0 , res=1;
	printf("Enter An Positive Integer Number \n");
	fflush(stdout); fflush(stdin);
	scanf("%d",&x);
	res = fac(x);
	printf("Factorial Of %d Is %d \n",x,res);
	fflush(stdout);
}

int fac(int num)
{
	if(num == 0)
		return 1;
	else
		return num*fac(num-1);
}
