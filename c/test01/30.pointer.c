//주소값의 크기는 운영 체제에 의해서 결정된다.  64비트는 8바이트
#include <stdio.h>

int main()
{
	int a;
	double b;
	char c;
	int d;
	int* pd;

	pd = &d;
	d = 10;

	printf("int형 변수의 주소 : %u\n", &a);	//%x나 %xp를 사용하면 16진수로도 표시가 가능하다.
	printf("couble형 변수의 주소 : %u\n", &b);
	printf("char형 변수의 주소 : %u\n", &c);
	printf("포인터로 d의 값 출력 : %d\n ", *pd);	//간접참조 연산자 *pd = d의 값
	printf("d의 값 출력 : %d\n", d);

	return 0;
}