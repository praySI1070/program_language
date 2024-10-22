//쓰레기 값과 초기화
#include <stdio.h>

int main()
{
	int a;		//9행에서 대입 연산으로 초기화
	int b = 20;	// 변수선언과 동시에 초기화
	int c;		// 초기화되지 않음

	a = 10;		// a에 10을 대입, 초기화
	printf("a:%d\n", a);
	printf("b:%d\n", b);
	printf("c:%d\n", c);

	return 0;
}