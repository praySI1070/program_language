#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N,M,i,j,k;
	
	scanf("%d %d", &N, &M);
	
	if(N < 1 || M < 1)
	{
		return 0;
	}
	int *arr = (int*)malloc(sizeof(int)*N);
	
	for(int x = 0; x < N; x++)
	{
		*(arr + x) = 0;
	}
	
	for(int x = 0; x < M; x++)
	{
		scanf("%d %d %d", &i, &j, &k);
		if(i > j || j > N || k < 1)
		{
			return 0;
		}
		for(int y = 0; y < j - i + 1; y++)
		{
			*(arr+(i-1+y)) = k;
		}
	}
	
	for(int x = 0; x < N; x++)
	{
		printf("%d ", *(arr+x));
	}
	
	free(arr);
	
	return 0;
}
