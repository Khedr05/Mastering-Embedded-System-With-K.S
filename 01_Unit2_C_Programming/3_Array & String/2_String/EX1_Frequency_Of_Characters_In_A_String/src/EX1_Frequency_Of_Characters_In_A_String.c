/*
 ============================================================================
 Name        : EX1_Frequency_Of_Characters_In_A_String.c
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
	int i,counter=0;
	char ch,arr[100];

	printf("Enter The String \n");
	fflush(stdout); fflush(stdin);
	gets(arr);
	printf("Enter The Char To Search \n");
	fflush(stdout); fflush(stdin);
	scanf("%c",&ch);
	i=0;
	while(arr[i] != '\0')
	{
		if(arr[i] == ch)
			counter++;
		i++;
	}
	printf("Frequency Of %c = %d \n",ch,counter);
}
