#include <stdio.h>
#include <stdlib.h>

void change(int*,int*);

int main()
{
	int N,max,min;
	scanf("%d", &N);
	
	if(N<1)
	{
		return 0;
	}

	int *arr = (int*)malloc(sizeof(int) * N);
	
	for(int i=0; i<N; i++)
	{
		scanf("%d", (arr+i));
	}
	
	for(int i=0; i<N; i++)
	{
		if(*(arr) >= *(arr+i))
		{
			continue;
		}
		else
		{
			change(arr,(arr+i));
		}
	}

	max = *arr;
	
	for(int i=0; i<N; i++)
	{
		if(*(arr) <= *(arr+i))
		{
			continue;
		}
		else
		{
			change(arr,(arr+i));
		}
	}
	
	min = *arr;
	
	printf("%d %d", min, max);
	
	free(arr);
	
	return 0;
}

void change(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
	return;
}
