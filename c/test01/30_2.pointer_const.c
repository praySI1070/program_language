#include <stdio.h>

int main()
{
	int a = 10, b = 20;
	const int* pa = &a;	//const가 앞에 있을 경우, 대입을 새로 할 수 없음.
	int* const ps = &a;	//const가 중앙에 있을 경우, 대입은 가능하지만, 주소를 바꿀 수 없음.
	
	
	
	printf("변수 a값 : %d\n", *pa);
	pa = &b;
	printf("변수 b값 : %d\n", *pa);
	a = 20;
	printf("변수 a값 : %d\n", *pa);

	return 0;
}