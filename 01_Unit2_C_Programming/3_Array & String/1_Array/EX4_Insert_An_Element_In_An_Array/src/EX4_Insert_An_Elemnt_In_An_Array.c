/*
 ============================================================================
 Name        : EX4_Insert_An_Elemnt_In_An_Array.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n=0,index=0,num=0;
	int arr[10];
	printf("Enter Number Of Element\n");
	fflush(stdout); fflush(stdin);
	scanf("%d",&n);

	printf("Enter Elements \n");
	fflush(stdout); fflush(stdin);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}

	printf("Elements Are \n");

	for(int i=0;i<n;i++)
	{
		printf("%d \n",arr[i]);
		fflush(stdout); fflush(stdin);
	}
	printf("Enter The Element You Want To Insert \n");
	fflush(stdout);	fflush(stdin);
	scanf("%d",&num);

	printf("Enter The Location You Want To Insert The Element In It \n");
	fflush(stdout); fflush(stdin);
	scanf("%d",&index);

	 if(index > n+1 || index <= 0)
	        printf("Invalid Position! Please Enter Position Between 1 To %d", n);
	    else
	    {
	        for(int i=n;i>=index;i--)
	        {
	            arr[i] = arr[i-1];
	        }
	        arr[index-1] = num;
	        printf("Array Elements After Insertion : ");
	        for(int i=0; i<n+1; i++)
	        {
	            printf("%d\t", arr[i]);
	        }
	    }

}
