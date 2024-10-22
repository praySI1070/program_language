//비트 연산자

#include <stdio.h>

int main()
{
	int a = 10;
	int b = 12;

	printf("a & b : %d\n", a & b);
	printf("a ^ b : %d\n", a ^ b);
	printf("a | b : %d\n", a | b);
	printf("~a : %d\n", ~a);
	printf("a << 1 : %d\n", a << 1);
	printf("a >> 2 : %d\n", a >> 2);
}

/*10 = 0000 1010
12 = 0000 1100

a & b = 0000 1000 = 8
a ^ b = 0000 0110 = 6
a | b = 0000 1110 = 14
~a = 1111 0001 = 64 + 32 + 16 + 1 = 113
a << 1 -> 0001 0100 = 20
a >> 2 -> 0000 0010 = 2*/