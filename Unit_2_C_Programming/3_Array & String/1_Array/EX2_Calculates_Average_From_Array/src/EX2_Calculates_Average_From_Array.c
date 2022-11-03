/*
 ============================================================================
 Name        : EX2_Calculates_Average_From_Array.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i,n = 0;
	float arr[n],average;
	printf("Enter The Number Of Data \n");
	fflush(stdout); fflush(stdin);
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter The Data Number %d \n",i);
		fflush(stdout); fflush(stdin);
		scanf("%f",&arr[i]);
	}
	for(i=0;i<n;i++)
	{
		fflush(stdout); fflush(stdin);
		average += arr[i];
	}
	average = average / n;
	printf("Average Equal : %0.2f",average);
}
