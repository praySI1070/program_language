//컴파일러는 보통 위에서 아래로 읽지만, 함수의 경우 일단 넘어간 후에 검색한 후에 적용한다.

#include <stdio.h>

int add(int x, int y);

int main()
{
	int a = 10, b = 20;
	int res;

	res = add(a, b);
	printf("result : %d\n", res);

	return 0;
}

int add(int x, int y)
{
	int temp;

	temp = x + y;

	return temp;
}