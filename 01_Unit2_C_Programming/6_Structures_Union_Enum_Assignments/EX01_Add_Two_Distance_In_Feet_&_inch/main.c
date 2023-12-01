/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "25-12-2022"

Program : "Add two distance in feet and inch"

*/

#include<stdio.h>

typedef struct calcdistance
{
	float feet;
	float inch;

}distance;

void main(void)
{	
	distance distance1,distance2,sum;
	printf("Enter distance1 in feet: ");
	scanf("%f",&distance1.feet);
	printf("Enter distance1 in inch: ");
	scanf("%f",&distance1.inch);
	printf("Enter distance2 in feet: ");
	scanf("%f",&distance2.feet);
	printf("Enter distance2 in inch: ");
	scanf("%f",&distance2.inch);

	sum.feet = distance1.feet + distance2.feet;
	sum.inch = distance1.inch + distance2.inch;

	if(sum.inch > 12.0)
	{
		sum.inch = sum.inch-12.0;
		++sum.feet;
	}
	printf("sum of two distance = %0.0f,%0.1f",sum.feet,sum.inch);






}