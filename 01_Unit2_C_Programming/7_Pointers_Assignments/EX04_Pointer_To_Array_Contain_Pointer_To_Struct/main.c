#include<stdio.h>

struct employee
{
	char *employeeName;
	int employeeId;
};

void main(void)
{
	struct employee emp1={"sherif",5},emp2={"ashraf",1},emp3={"ali",2};

	struct employee(*arr[])={&emp1,&emp2,&emp3};

	struct employee (*(*pt)[3])=&arr;

	printf("Employee Name : %s\n",(**(*pt)).employeeName);
	printf("Employee Id : %d",(**(*pt)).employeeId);


}