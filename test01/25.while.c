//do while과 while은 처음에 조건문이 거짓일 때, 처음 한번은 실행을 하냐, 아니냐의 차이

#include <stdio.h>

int main()
{
	int a = 1, count = 0;

	while (a < 10)
	{
		a *= 2;
		count++;
	}
	printf("a: %d, count : %d\n", a, count);

	int b = 1;

	do
	{
		b *= 2;
	} while (b < 10);
	printf("b : %d\n", b);

	int c = 1;

	while (c < 10)	//while 과 do while의 결과 값은 참일 경우엔 같음
	{
		c *= 2;
	}

	printf("c : %d\n", c);

	return 0;
}