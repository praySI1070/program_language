// ++a는 즉시 적용, a++은 ;이후에 적용된다.
// >>1은 비트 이동 연산자로서 한칸 옆으로 민다. ex) 0000 0110 -> 0000 0011
//xor 다를때만 참

#include <stdio.h>

int main()
{
	int a, b;
	int sum, sub, mul;
	unsigned int inv;

	a = 10;
	b = 20;
	sum = a + b;
	sub = a - b;
	mul = a * b;
	inv = -a;

	printf("a의 값 :%d, b의 값 : %d\n", a, b);
	printf("덧셈 : %d\n", sum);
	printf("뺄셈 : %d\n", sub);
	printf("곱셈 : %d\n", mul);
	printf("a의 음수계산 : %u\n", inv);

	double apple;
	int banana;
	int orange;

	apple = 5.0 / 2.0;	//실수와 실수의 나눗셈 연산
	banana = 5 / 2;		//나눗셈
	orange = 5 % 2;		//나머지

	printf("apple: %.1lf\n", apple);
	//printf("apple: %.1lf\n", (int)apple);   앞에 (int)를 붙이면 그 뒤의 자료형만 붙인 자료형이 된다.
	printf("banana: %d\n", banana);
	printf("orange: %d\n", orange);


	++a;
	--b;

	printf("a : %d\n", a);
	printf("b : %d\n", b);


	return 0;
}
