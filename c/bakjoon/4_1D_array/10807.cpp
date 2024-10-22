#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N,v,i;
	int count = 0;
	
	scanf("%d", &N);
	int *arr = (int*)malloc(sizeof(int) *N);
	
	
	for(int i=0; i<N; i++)
	{
		scanf("%d", (arr + i));
	}
	
	scanf("%d", &v);
	
	for(i=0; i<N; i++)
	{
		if(v == *(arr + i))
		{
			count++; 
		}
		else
		{
			continue;
		}
	}
	
	printf("%d", count);
	
	free(arr);
	
	return 0;
}
