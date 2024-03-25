#include <stdio.h>
#include <stdlib.h>

int main()
{
	int A,B,T,i;
	scanf("%d", &T);
	int *arr = (int*)malloc(sizeof(int)*T);
	for(i=0; i<T; i++)
	{
		scanf("%d %d", &A, &B);
		*(arr + i) = A + B;
	}
	
	for(i=0; i<T; i++)
	{
		printf("%d\n", *(arr+i));
	}
	
	free(arr);
	return 0;
}
