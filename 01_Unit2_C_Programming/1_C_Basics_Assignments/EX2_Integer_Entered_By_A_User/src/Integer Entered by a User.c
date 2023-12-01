/*
 ============================================================================
 Name        : Integer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num = 0;
	printf("Enter a integer \n");
	fflush(stdout);
	scanf("%d",&num);
	printf("you enter : %d",num);
	return 0;
}
