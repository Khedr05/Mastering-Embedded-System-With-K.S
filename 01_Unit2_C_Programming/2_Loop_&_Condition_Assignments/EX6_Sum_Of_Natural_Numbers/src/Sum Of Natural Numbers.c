/*
 ============================================================================
 Name        : Sum.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n=0,sum=0;
	printf("Enter The Number \n");
	fflush(stdout);
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
		sum+=i;
	printf("The Sum Equal %d",sum);
}
