/*
 ============================================================================
 Name        : EX1_Prime_Number_Betwwen_Two_Intervals.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void get_prime(int a , int b);
int check_num(int num);


int main(void) {
	int x=0,y=0;
	printf("Enter Two Numbers Small Number First\n");
	fflush(stdout); fflush(stdin);
	scanf("%d %d",&x,&y);
	get_prime(x,y);
}

void get_prime(int a, int b)
{
	printf("Prime Number Between %d And %d Are \n",a,b);
	fflush(stdout);
	while(a<=b)
	{
		if(check_num(a))
		{
			printf("%d \t",a);
			fflush(stdout);
		}
		a++;
	}
}

int check_num(int num)
{
	int i;

	for(i=2;i<=num/2;i++)
	{
		if(num % i == 0)
		{
			return 0;
		}
	}
	return 1;
}
