/*
 ============================================================================
 Name        : EX3Reverse_A_Sentence_Using_Recursion.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */



#include <stdio.h>
void reverseSentence();
int main() {
    printf("Enter a sentence: ");
    fflush(stdout);
    reverseSentence();
    return 0;
}

void reverseSentence() {
    char c;
    scanf("%c", &c);
    if (c != '\n') {
        reverseSentence();
        printf("%c", c);
        fflush(stdout);
    }
}
