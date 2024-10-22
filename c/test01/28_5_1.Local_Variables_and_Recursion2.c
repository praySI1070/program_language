#include <stdio.h>

void fruit(int n);

int main()
{
	fruit(1);

	return 0;
}

void fruit(int n)		//마지막에 찍히는 애플 이후 n이 3이 되므로 return으로 함수가 종료되서 3번쨰 jam이 찍히지 않는다.
{
	printf("apple");
	if (n == 3) return 0;
	printf("jam\n");
	fruit(n + 1);
}