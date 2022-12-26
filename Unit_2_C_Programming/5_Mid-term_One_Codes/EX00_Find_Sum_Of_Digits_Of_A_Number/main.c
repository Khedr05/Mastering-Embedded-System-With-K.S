/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "21-12-2022"

Program : "count number of digits in number"
*/

#include<stdio.h>
void main(void)
{
	int n,i,last,sum=0;
	printf("Enter number \n");
	scanf("%d",&n);
	i=n;
	while(i!=0)
	{	last=i%10;
		i=i/10;
		sum+=last;
	}
	printf("sum of digit of number %d = %d",n,sum);
}