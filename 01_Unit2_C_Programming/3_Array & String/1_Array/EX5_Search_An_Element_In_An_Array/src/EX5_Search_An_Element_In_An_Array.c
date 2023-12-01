/*
 ============================================================================
 Name        : EX5_Search_An_Element_In_An_Array.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int size,i,arr[100],num,found=0;

	printf("Enter Number Of Element\n");
	fflush(stdout); fflush(stdin);
	scanf("%d",&size);

	printf("Enter Elements \n");
	fflush(stdout); fflush(stdin);
	for(i=0;i<size;i++)
	{
		scanf("%d",&arr[i]);
	}

	printf("Elements Are \n");

	for(i=0;i<size;i++)
	{
		printf("%d \t",arr[i]);
		fflush(stdout); fflush(stdin);
	}
	printf("\n");
	printf("Enter The Element You Need Its Location \n");
	fflush(stdout); fflush(stdin);
	scanf("%d",&num);

	for(i=0;i<size;i++)
	{
		if(num == arr[i])
		{
			found = 1;
			break;
		}
	}

	if(found == 1)
		printf("The Element %d Found In The Location Number %d",num,i+1);
	else
		printf("The Element %d Not Found In The List Of Number",num);

}
