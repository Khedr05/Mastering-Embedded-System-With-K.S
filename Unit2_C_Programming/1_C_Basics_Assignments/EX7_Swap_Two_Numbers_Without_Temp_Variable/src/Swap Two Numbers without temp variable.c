/*
 ============================================================================
 Name        : Swap.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int a=0,b=0;
	printf("Enter Two Integers Number \n");
	fflush(stdout);
	scanf("%d \n %d",&a,&b);
	printf("Value Before Swap \n");
	printf("Value Of A = %d \n",a);
	printf("Value Of B = %d \n",b);
	a=a+b;
	b=a-b;
	a=a-b;
	printf("Value After Swap \n");
	printf("Value Of A = %d \n",a);
	printf("Value Of B = %d \n",b);
	return 0;
}
