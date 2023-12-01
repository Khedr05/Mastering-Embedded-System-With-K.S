#include<stdio.h>

void main(void)
{
	int arr[5];
	int *arrPtr = arr;
	int counter = 5;

	for(int i=0;i<5;i++)
	{
		printf("Enter Element %d :",i);
		scanf("%d",&arr[i]);
	}

	while(counter>0)
	{
		arrPtr++;
		counter--;
	}

	while(counter<5)
	{
		arrPtr--;
		printf("%d \t",*arrPtr);
		counter++;
	}
}