//ctrl + Z는 eof(end of file)을 강제로 발생시킨다. 
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int A,B,C;
	int N = 0;
	int *arr = (int*)malloc(sizeof(int) * N+1);
	
	while(1)
	{
		C = scanf("%d %d", &A, &B);
		if(C == -1)
		{
			break;
		}
		*(arr + N) = A + B;
		N++;
		arr = (int*)realloc(arr, sizeof(int) * (N+1));
	}
	
	for(int i=0; i<N; i++)
	{
		printf("%d\n", *(arr+i));
	}
	
	free(arr);
	
	return 0;
}
