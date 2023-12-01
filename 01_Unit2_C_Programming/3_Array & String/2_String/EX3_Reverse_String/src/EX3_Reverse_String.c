/*
 ============================================================================
 Name        : EX3_Reverse_String.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int i=0,size=0,counter=0;
	char arr[100],revarr[100];
	printf("Enter The String \n");
	fflush(stdout); fflush(stdin);
	gets(arr);
	size = strlen(arr);
	counter = size;
	while(arr[i]!='\0')
	{
		revarr[size-1] = arr[i];
		i++; size--;
	}
	revarr[counter+1]='\0';
	printf("The String Is : ");
	fflush(stdout); fflush(stdin);
	for(i=0;i<counter;i++)
	{
		printf("%c",arr[i]);
		fflush(stdout); fflush(stdin);
	}
	printf("\n");
	printf("The Reverse String Is : ");
	fflush(stdout); fflush(stdin);
	for(i=0;i<counter;i++)
	{
		printf("%c",revarr[i]);
		fflush(stdout); fflush(stdin);
	}
	printf("\n");
}
