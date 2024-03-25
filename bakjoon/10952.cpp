#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N = 0;
	int A,B;
	int *C = (int*)malloc(sizeof(int) * (N + 1));
	
	while(1)
	{
		scanf("%d %d", &A, &B);
		if(A == 0 && B == 0)
		{
			break;
		}
		*(C+N) = A + B;
		N++;
		C = (int*)realloc(C, sizeof(int) * (N + 1));
	}
	
	for(int i=0; i<N;i++)
	{
		printf("%d\n", *(C + i));
	}
	

	free(C);
	
	return 0;
}
