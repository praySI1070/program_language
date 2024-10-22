#include <stdio.h>

int main()
{
	int i, arr_len;
	int num01 = 10, num02 = 20, num03 = 30;
	int* arr[3] = {&num01, &num02, &num03};	//int형 포인터 배열 선언 
	
	arr_len = sizeof(arr) / sizeof(arr[0]);
	for(i = 0; i < arr_len; i++)
	{
		printf("%d\n", *arr[i]);
	}
	

	
	return 0;
}
