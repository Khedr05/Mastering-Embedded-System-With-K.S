/*
 ============================================================================
 Name        : Largest.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x=0.0 , y=0.0 , z=0.0;
	printf("Enter Three Numbers \n");
	fflush(stdout);
	scanf("%f %f %f",&x,&y,&z);
	if(x>y && x>z)
		printf("Largest Number Is : %f",x);
	else if(y>x && y>z)
		printf("Largest Number Is : %f",y);
	else if(z>x && z>y)
		printf("Largest Number Is : %f",z);
}
