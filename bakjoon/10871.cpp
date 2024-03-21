#include <stdio.h>
#include <stdlib.h>

int main()
{
	unsigned int N,X;
	scanf("%d %d", &N, &X);
	unsigned int *A = (unsigned int*)malloc(sizeof(int) * N);
	
	for(int i =0; i<N; i++)
	{
		scanf("%d", (A+i));
	}
	
	for(int i=0; i<N; i++)
	{
		if(*(A+i) < X)
		{
			printf("%d ", *(A+i));
		}
		else
		{
			continue;
		}
	}
	
	free(A);
	
	return 0;
}
