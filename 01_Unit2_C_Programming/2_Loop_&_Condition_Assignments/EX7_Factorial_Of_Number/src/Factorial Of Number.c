/*
 ============================================================================
 Name        : Factorial.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n=0,fac=1;
	printf("Enter The Number You Want Its Factorial \n");
	fflush(stdout);
	scanf("%d",&n);
	if(n < 0)
		printf("Factorial Does Not Exist For Negative Numbers \n");
	else if(n == 0)
		printf("Factorial Of 0 Equal 1 \n");
	else if(n > 0)
	{
		for(int i=1;i<=n;i++)
			fac*=i;
	printf("Factorial Of %d Equal %d",n,fac);
	}
}
