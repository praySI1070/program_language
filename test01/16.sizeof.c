//데이터 크기 확인, 메모리 동적 할당 작업 사용
#include <stdio.h>

int main()
{
	int a = 10;
	double b = 3.4;

	printf("int형 변수의 크기 : %d\n", sizeof(a));
	printf("double형 변수의 크기 : %d\n", sizeof(b));
	printf("정수형 상수의 크기 : %d\n", sizeof(10));
	printf("수식의 경과값의 크기 : %d\n", sizeof(1.5+3.4));
	printf("char형 자료형의 크기 : %d\n", sizeof(char));

	int c = 10, d = 20;
	int res = 2;

	c += 20;		//a와 20을 더한 결과를 다시 a에 ㅈ장
	res *= d + 10;	//b에 10을 더한 결과값에 res를 곱하고 다시 res에 저장 -> 연산방향이 우측에서 좌측이기 때믄에 +10이 먼저들어가고 곱셈이 들어간다.

	printf("a = %d, b =%d\n", c, d);
	printf("res = %d\n", res);


	return 0;
}