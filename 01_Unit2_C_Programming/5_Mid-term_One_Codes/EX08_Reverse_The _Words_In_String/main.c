/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date    : "21-12-2022"

Program : "reverse words in string"
*/


#include <stdio.h>
#include <string.h>

int main()
{
    char str[100], reverse[100];
    int len, i, index, wordStart, wordEnd;

    printf("Enter string: ");
    gets(str);

    len   = strlen(str);
    index = 0;

    wordStart = len - 1;
    wordEnd   = len - 1;

    while(wordStart > 0)
    {
        if(str[wordStart] == ' ')
        {
            i = wordStart + 1;
            while(i <= wordEnd)
            {
                reverse[index] = str[i];

                i++;
                index++;
            }
            reverse[index++] = ' ';

            wordEnd = wordStart - 1;
        }

        wordStart--;
    }

    for(i=0; i<=wordEnd; i++)
    {
        reverse[index] = str[i];
        index++;
    }
    reverse[index] = '\0'; 
    printf("Reverse string :  \n%s", reverse);
    return 0;
}