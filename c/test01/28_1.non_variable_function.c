#include <stdio.h>

int get_pos();

int main(void)
{
	int res;

	res = get_pos();
	printf("반환값 : %d\n", res);

	return 0;
}

int get_pos()
{
	int pos;

	printf("양수 입력 : ");
	scanf("%d", &pos);

	return pos;
}