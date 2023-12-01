/*
 ============================================================================
 Name        : EX2_Length_Of_A_String.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
		int i=0;
		char arr[100];
		printf("Enter The String \n");
		fflush(stdout); fflush(stdin);
		gets(arr);
		while(arr[i] != '\0')
		{
			i++;
		}
		printf("Length Of The String = %d \n",i);
}
