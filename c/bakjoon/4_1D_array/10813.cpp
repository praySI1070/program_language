#include <stdio.h>
#include <stdlib.h>

void change(int*,int*);

int main()
{
	int N,M,i,j;
	scanf("%d %d", &N, &M);
	if(N <1 || M < 1)
	{
		return 0;
	}
	int *arr = (int*)malloc(sizeof(int) * N);
	
	for(int k= 0; k<N; k++)
	{
		*(arr+k) = k+1;
	}
	
	for(int k =0; k<M; k++)
	{
		scanf("%d %d", &i, &j);
		change((arr+i-1),(arr+j-1));
	}
	
	for(int k=0; k<N; k++)
	{
		printf("%d ", *(arr+k));
	}
	
	free(arr);
	
	return 0;
}

void change(int *a, int*b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
	return;
}
