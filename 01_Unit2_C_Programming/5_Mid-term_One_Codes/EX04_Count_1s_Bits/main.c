/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "21-12-2022"

Program : "count number of ones bits in a binary number"
*/


#include<stdio.h>

void main(void)
{
	int num,read_bit,bit,ones_count=0;
	printf("Enter Number To \n");
	scanf("%d",&num);


	for(bit = 0;bit<=7;bit++)
	{
		read_bit = (num>>bit)&1;
		if(read_bit)
		{
			ones_count++;
		}
	}
	printf("Ones Bit In Number %d = %d \n",num,ones_count);
}