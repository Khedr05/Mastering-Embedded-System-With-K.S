/*
 ============================================================================
 Name        : Add.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x=0,y=0;
	printf("Enter Two Numbers \n");
	fflush(stdout);
	scanf("%d \n %d",&x,&y);
	printf("add of two integer = %d ",x+y);
	return 0;
}
