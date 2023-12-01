/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date    : "21-12-2022"

Program : "print from 1 to 100 without loop"
*/


#include<stdio.h>
int main()
{
    int i = 0;
begin:
    i = i + 1;
    printf("%d ", i);
 
    if (i < 100)
        goto begin;
}