#include <stdio.h>

int main()
{
	int arr[2][3] = {
	{10,20,30},
	{40,50,60}
	};
	
	printf("%d\n", *arr[0]);
	printf("%d\n", *arr[1]);
	
	int (*pArr)[3] = arr;
	
	printf("%d\n", arr[1][1]);
	printf("%d\n", pArr[1][1]);
	
	
	return 0;
}
