/*
 ============================================================================
 Name        : EX3_Transpose_Of_A_Matrix.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int row=0,column=0;
	int matrix[10][10];
	int t_matrix[10][10];
	int r,c;

	printf("Enter Size Of The Matrix Row Then Column \n");
	fflush(stdout); fflush(stdin);
	scanf("%d\n%d",&row,&column);

	for(r=0;r<row;r++)
	{
		for(c=0;c<column;c++)
		{
			printf("Enter Number Of Matrix(%d,%d)\n",r+1,c+1);
			fflush(stdout); fflush(stdin);
			scanf("%d",&matrix[r][c]);
		}
	}

	printf("The Matrix Is \n");
	for(r=0;r<row;r++)
	{
		for(c=0;c<column;c++)
		{
			printf("%d \t",matrix[r][c]);
		}
		printf("\n");
	}

	printf("The Transpose Matrix Is \n");
	for(r=0;r<row;r++)
	{
		for(c=0;c<column;c++)
		{
			t_matrix[c][r] = matrix[r][c];
		}
	}

	for(r=0;r<row;r++)
	{
		for(c=0;c<column;c++)
		{
			printf("%d \t",t_matrix[r][c]);
		}
		printf("\n");
	}
	return 0;
}
