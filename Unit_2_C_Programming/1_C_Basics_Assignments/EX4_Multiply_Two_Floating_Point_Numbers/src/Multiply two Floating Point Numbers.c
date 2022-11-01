/*
 ============================================================================
 Name        : Multiply.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x=0.0,y=0.0;
	printf("Enter Two Numbers \n");
	fflush(stdout);
	scanf("%f \n %f",&x,&y);
	printf("multiply of two floating numbers = %f ",x*y);
	return 0;
}
