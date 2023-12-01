#include<stdio.h>

void main(void)
{
	char arr[27];
	char *ptr = arr;

	for(char i=0;i<26;i++)
	{
		*ptr='a'+i;
		ptr++;
	}

	ptr = arr;
	for(char i=0;i<26;i++)
	{
		printf("%c \t",*ptr);
		ptr++;
	}
}