#include <stdio.h>

int main()
{
	int i,k,N;
	scanf("%d", &N);
	
	for(i=0; i<N; i++)
	{
		for(k=0; k<i+1; k++)
		{
			printf("*");
		}
		printf("\n");
	}
	
	return 0;
}
