/*
 ============================================================================
 Name        : Simply.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char ch=0;
	float x=0.0,y=0.0;
	printf("Choose Operator + Or - Or * Or / \n");
	fflush(stdout);
	scanf("%c",&ch);
	printf("Enter Two Operands \n");
	fflush(stdout);
	scanf("%f %f",&x,&y);
	switch(ch)
	{
	case'+':
		printf("Sum Of %f And %f Equal %f",x,y,x+y);
		break;
	case'-':
		printf("Subtract Of %f And %f Equal %f",x,y,x-y);
		break;
	case'*':
		printf("Multiply Of %f And %f Equal %f",x,y,x*y);
		break;
	case'/':
		printf("Division Of %f And %f Equal %f",x,y,x/y);
		break;
	}
}
