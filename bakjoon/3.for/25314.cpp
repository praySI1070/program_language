#include <stdio.h>

int main()
{
	int N,i;
	scanf("%d", &N);
	if(N % 4 == 0 && N > 0) 
	{
		for(i=0; i<N/4; i++)
		{
			printf("long ");
		}
	}
	printf("int");
	
	return 0;
}
