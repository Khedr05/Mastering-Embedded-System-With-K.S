/*
 ============================================================================
 Name        : EX1_Sum_Of_Two_Matrix.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x[2][2];
		float y[2][2];
		int row,column;

		printf("Fill Matrix One \n");
		fflush(stdout);
		for(row=0;row<2;row++)
		{
			for(column=0;column<2;column++)
			{
				printf("Enter Number Of X(%d,%d)\n",row,column);
				fflush(stdout); fflush(stdin);
				scanf("%f",&x[row][column]);
			}
		}
		printf("Fill Matrix Two \n");
		fflush(stdout);
		for(row=0;row<2;row++)
		{
			for(column=0;column<2;column++)
			{
				printf("Enter Number Of Y(%d,%d)\n",row,column);
				fflush(stdout); fflush(stdin);
				scanf("%f",&y[row][column]);
			}
		}
		printf("Sum Of Matrix One & Matrix Two \n");
			fflush(stdout);
			for(row=0;row<2;row++)
			{
				for(column=0;column<2;column++)
				{
					x[row][column] += y[row][column];
				}
			}
			for(row=0;row<2;row++)
			{
				for(column=0;column<2;column++)
				{
				  printf("%2.2f \t",x[row][column]);
				}
				printf("\n");
			}
}
