#include<stdio.h>

void main(void)
{
	int m = 29;
	int *ptrm = &m;


	printf("Address Of M : %p\n",&m);
	printf("Value Of M : %d\n",m);

	printf("Address Of Pointer ptrm : %p\n",ptrm);
	printf("Content Of Pointer ptrm : %d\n",*ptrm);

	m = 34;

	printf("Address Of Pointer ptrm : %p\n",ptrm);
	printf("Content Of Pointer ptrm : %d\n",*ptrm);

	*ptrm = 7;

	printf("Address Of M : %p\n",&m);
	printf("Value Of M : %d\n",m);





}