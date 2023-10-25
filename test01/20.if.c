//if문 기본형식

#include <stdio.h>

int main()
{
	int a = 20;
	int b = 0;

	if (a > 10)	// 참이기 떄문에 작동함
	{
		b = a;
	}
	printf("a : %d, b = %d\n", a, b);

	if (a < 10)	//거짓이기 때문에 작동안함
	{
		b = 40;
	}
	printf("a : %d, b = %d\n", a, b);

	return 0;
}