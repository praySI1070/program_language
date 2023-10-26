#include <stdio.h>

int main()
{
	int test;

	test = minus(10, 2, 5);



	printf("%d\n", test);



}

int minus(int x, int y, int z)
{
	int minus_1;

	minus_1 = x - y - z;

	return minus_1;		//retrun문은 변수자체를 넘기는 것이 아니라 변수에 들어있는 값을 넘기는 것이다.
	
}