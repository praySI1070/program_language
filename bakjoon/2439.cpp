#include <stdio.h>

int main()
{
	int i,N;
	scanf("%d", &N);
	
	for(i=0; i<N; i++)
	{
		for(int j=0; j<N-i-1; j++)
		{
			printf(" ");
		}
		for(int j=0; j<i+1; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	
	return 0;
}
