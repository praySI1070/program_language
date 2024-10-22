//정적변수는 선언된 함수가 반환되더라도 저장 공간은 유지된다.
//-> 함수가 여러번 호출되더라도 같은 변수를 선언을 여러번 안해도 된다.
#include <stdio.h>

void test_static()
{
	static int i;
	printf("%d\n", i);
	i++;
}

int main()
{
	test_static();
	test_static();
	test_static();
	return(0);
}