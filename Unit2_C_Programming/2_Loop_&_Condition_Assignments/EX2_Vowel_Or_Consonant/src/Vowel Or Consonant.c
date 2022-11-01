/*
 ============================================================================
 Name        : Vowel.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char c;
	printf("enter the char\n");
	fflush(stdout);
	scanf("%c",&c);
	if( c == 'a'|| c == 'A'|| c == 'e' || c == 'E'|| c == 'o' || c == 'O'|| c == 'i' || c == 'I'|| c == 'u' || c == 'U')
		printf("char is vowel");
	else
		printf("char is consonant");
	return 0;
}
