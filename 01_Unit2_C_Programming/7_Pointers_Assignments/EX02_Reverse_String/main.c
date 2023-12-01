#include<stdio.h>

#define MAX_SIZE 100

void main(void)
{
	char str[MAX_SIZE],revstr[MAX_SIZE];
	char *strptr = str;
	char *revstrPtr = revstr;
	char counter = -1;

	printf("Enter String To Reverse \n");
	scanf("%s",str);

	while(*strptr)
	{
		counter++;
		strptr++;
	}

	while(counter>=0)
	{
		strptr--;
		*revstrPtr= *strptr;
		revstrPtr++;
		counter--;
	}
	*revstrPtr='\0';

	printf("%s",revstr);
}