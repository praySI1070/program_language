
#include <stdio.h>

int main()
{
	int a = 0, b = 0;
	int res = 0;

	for (int i = 1; i < 10; i++)
	{
		printf("%d단입니다.\n", i);
		for (int k = 1; k < 10; k++)
		{
			res = i * k;
			printf("%d * %d = %d입니다.\n", i, k, res);
		}
		
	}

	return 0;
}