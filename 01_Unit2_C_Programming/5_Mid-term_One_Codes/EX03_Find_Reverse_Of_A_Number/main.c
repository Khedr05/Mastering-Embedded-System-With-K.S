/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "21-12-2022"

Program : "reverse a number taken from user"
*/
#include<stdio.h>

void main(void)
{
	int n,copy_of_n,reversed_num=0,last;
	printf("Enter number \n");
	scanf("%d",&n);
	copy_of_n = n;
	while(n!=0)
	{	last=n%10;
		n=n/10;
		reversed_num = (reversed_num*10) + last;
	}
	printf("reverse number of %d = %d",copy_of_n,reversed_num);
}