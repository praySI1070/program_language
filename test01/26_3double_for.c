#include <stdio.h>

int main()
{
	int i, j;
	int k = 1;
	for (i = 0; i < 5; i++)		// 변수 3개
	{
		for (j = 0; j < k; j++)
		{
			printf("*");
		}
		k += 1;
		printf("\n");
	}

	for (i = 0; i < 5; i++)		//변수 2개
	{
		for (j = 0; j < i + 1; j++)
		{
			printf("#");
		}
		printf("\n");
	}

	for (i = 0; i < 5; i++)		//뒤집기
	{
		for (k = 4; k > i; k--)
		{
			printf(" ");
		}

		for (j = 0; j < i + 1 ; j++)
		{
			printf("@");
		}
		printf("\n");
	}

	printf("%d", i);  // int를 밖에서 선언했기 때문에 i가 밖에서 존재
}