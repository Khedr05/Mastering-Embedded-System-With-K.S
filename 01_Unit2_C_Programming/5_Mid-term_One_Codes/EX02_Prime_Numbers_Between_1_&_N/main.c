/* 
 
Author  : "Sherif_Ashraf"

Version : "v-1.0"

Date    : "21-12-2022"

Program : "print prime number between range"
*/



#include <stdio.h>
void get_prime(int a , int b);
int check_num(int num);

void main(void) {
    int x=0,y=0;
    printf("Enter Two Numbers Small Number First\n");
    scanf("%d %d",&x,&y);
    get_prime(x,y);
}


int check_num(int num)
{
    int i;

    for(i=2;i<=num/2;i++)
    {
        if(num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}


void get_prime(int a, int b)
{
    printf("Prime Number Between %d And %d Are \n",a,b);
    while(a<=b)
    {
        if(check_num(a))
        {
            printf("%d \t",a);
        }
        a++;
    }
}


