#include <stdio.h>
#include <stdlib.h>

int main()
{
	int X,N,a,b,i;
	int X_ = 0;
	scanf("%d", &X);
	scanf("%d", &N);
	int *arr = (int*)malloc(sizeof(int) * N);
	
	for(i=0; i<N; i++)
	{
		scanf("%d %d", &a, &b);
		*(arr + i) = a * b;
	}
	
	for(i=0; i<N; i++)
	{
		X_ += *(arr + i);
	}
	
	if(X == X_) {
		printf("Yes");
	}
	else {
		printf("No");
	}
	
	free(arr);
	
	return 0;
}
