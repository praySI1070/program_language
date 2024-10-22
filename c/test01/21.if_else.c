// if else문

#include <stdio.h>

int main()
{
	int a = 10;

	if (a >= 10) // a>=10이면 a = 1
	{
		a = 1;
	}
	else		// a>=10이 아니라면 a=-1
	{
		a = -1;
	}

	printf("a : %d\n", a);

	return 0;
}