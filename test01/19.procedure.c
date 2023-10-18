#include <stdio.h>

int main()
{
	int a = 10, b = 5;
	int res;

	res = a / b * 2;
	printf("res = %d\n", res); //우선 순위가 같으므로 왼쪽부터 차례로 연산
	res = ++a * 3;
	printf("res = %d\n", res); // a의 값을 증가시키고 3을 곱한다
	res = a > b && a !=5;
	printf("res = %d\n", res); // a > b의 결과와 a != 5의 결과를 &&연산
	res = a % 3 == 0;
	printf("res = %d\n", res); // a % 3의 값이 0과 같은지 확인

	return 0;
}