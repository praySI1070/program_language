#include <stdio.h>
#include <stdlib.h>

void change (int*, int*);

int main()
{
	int M,N;
	int i,j;
	scanf("%d %d", &N, &M);
	if(N<0 || N > 100 || M < 0 || M > 100) {
		return 0;
	}
	int *arr = (int*)malloc(sizeof(int) * N);
	
	for(int x = 0; x < N; x++)
	{
		*(arr + x) = x+1;
	}
	
	for(int x = 0;x <M; x++)
	{
		scanf("%d %d", &i, &j);
		if((j - i) % 2 == 1)
		{
			for(int y = 0; y < (j - i + 1) / 2; y++)
			{
				change((arr + i - 1 + y),(arr+ j - 1 - y));
			}
		}
		else
		{
			for(int y = 0; y < (j - i) / 2; y++)
			{
				change((arr + i - 1 + y),(arr + j - 1 - y));
			}
		}
	}
	
	
	for(int x = 0; x < N; x++)
	{
		printf("%d ", *(arr + x));
	}
	
	free(arr);
	
	return 0;
}

void change(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
	return;
}
