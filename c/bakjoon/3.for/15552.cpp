#include <stdio.h>
#include <stdlib.h>

int main()
{
	int T,A,B;
	scanf("%d", &T);
	int *arr = (int*)malloc(sizeof(int) * T);
	
	for(i=0; i<T; i++)
	{
		scanf("%d %d", &A, &B);
		*(arr + i) = A + B;
	}
	
	for(i=0; i<T; i++)
	{
		
	}
	
	free(arr)
	
	return 0;
}
