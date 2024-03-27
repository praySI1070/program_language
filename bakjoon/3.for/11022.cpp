#include <stdio.h>
#include <stdlib.h>

int main()
{
	int T,i;
	scanf("%d", &T);
	int *arr_A = (int*)malloc(sizeof(int) * T);
	int *arr_B = (int*)malloc(sizeof(int) * T);
	int *arr_result = (int*)malloc(sizeof(int) * T);
	
	
	for(i=0; i<T; i++)
	{
		scanf("%d %d", (arr_A + i), (arr_B + i));
		*(arr_result + i) = *(arr_A + i) + *(arr_B + i);
	}
	
	for(i=0; i<T; i++)
	{
		printf("Case #%d: %d + %d = %d\n", i+1, *(arr_A + i), *(arr_B + i), *(arr_result + i));
	}
	
	free(arr_A);
	free(arr_B);
	free(arr_result);
	
	return 0;
}
