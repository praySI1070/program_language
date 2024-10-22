//조건 연산자는 3항으로 이루어져 있으며, 첫째항은 보통 조건, 둘째는 참, 셋째는 거짓이 된다.

#include <stdio.h>

int main()
{
	int a = 10, b = 20, res;

	res = (a > b) ? a : b;	//a가 b보다 큰지를 물어봄 > 참이면 a 거짓이면 b
	printf("큰값 : %d\n", res);

	return 0;
}
