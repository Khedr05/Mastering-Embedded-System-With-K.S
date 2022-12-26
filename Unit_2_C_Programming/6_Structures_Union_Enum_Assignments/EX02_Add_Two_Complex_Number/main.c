/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date	: "25-12-2022"

Program : "Add two complex number"

*/

#include<stdio.h>

typedef struct scomplex
{
	float real;
	float imag;
}complex;

complex addComplex(complex num1,complex num2);

void main(void)
{
	complex n1,n2,res;

	printf("Enter complex one real: ");
	scanf("%f",&n1.real);
	printf("Enter complex two imag: ");
	scanf("%f",&n1.imag);
	printf("Enter complex one real: ");
	scanf("%f",&n2.real);
	printf("Enter complex two imag: ");
	scanf("%f",&n2.imag);

	res = addComplex(n1,n2);
	printf("sum of two complex number is : %0.1f+%0.1fi",res.real,res.imag);


}

complex addComplex(complex num1,complex num2)
{
	complex res;
	res.real = num1.real + num2.real;
	res.imag = num1.imag + num2.imag;
	return res; 
}