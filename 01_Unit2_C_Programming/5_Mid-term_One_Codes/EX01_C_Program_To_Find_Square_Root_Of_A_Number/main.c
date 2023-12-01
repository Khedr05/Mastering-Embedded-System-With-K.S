/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date    : "21-12-2022"

Program : "get square root of number"
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void) {
	float num,root;
	printf("Enter The Number \n");
	fflush(stdout);
	scanf("%f",&num);
	root = sqrt(num);
	printf("Square Root Of %0.2f = %0.2f",num,root);

}
