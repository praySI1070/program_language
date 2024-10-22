#include <stdio.h>

int main()
{
	int a = 30;
	int res;

	res = (a > 10) && (a < 20);
	printf("(a > 10) && (a < 20) : %d\n", res);
	res = (a < 10) || (a > 20);
	printf("(a < 10) || (a > 20) : %d\n", res);
	res = !(a >= 30);
	printf("!(a >= 30) : %d\n", res);

	//숏 서킷 룰(short circuit rule) 적용이 되어 컴파일러는 최대한 연산을 줄이려는 시도를 한다.
	//ex) &&일떄 좌항이 0이면 0이기에 우항을 시행을 안함


	return 0;
}