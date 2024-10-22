#include <stdio.h>

int main()
{
	int N;
	int sum = 0;
	char arr[101] = {0};
	char *ptr_arr = arr;
	scanf("%d", &N);
	if(N < 1 || N > 100) {
		return 0;
	}
	
	scanf("%s", arr);
	if(*(ptr_arr + N) != '\0') {
		return 0;
	}		//N보다 큰 경우 종료  
	for(int i =0; i<N; i++)
	{
		if(*(ptr_arr + i) == '\0') {
			return 0;
		}
	}		//N보다 작은 경우 종료
	
	for(int i =0; i<N; i++)
	{
		int x = *(ptr_arr + i) - 48;
		sum = sum + x;
	}
	
	printf("%d", sum);
	
	return 0;
}
