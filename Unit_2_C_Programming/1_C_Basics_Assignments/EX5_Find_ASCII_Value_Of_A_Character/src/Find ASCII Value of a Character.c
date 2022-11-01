/*
 ============================================================================
 Name        : Find.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char ch;
	printf("Enter character \n");
	fflush(stdout);
	scanf("%c",&ch);
	printf("ASCII Value Of %c Equal %d",ch,ch);
	return 0;
}
