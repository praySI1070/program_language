// unsigned 매개변수는 %d가아니라 %u(char short int)와 %llu(long long)
// 수를 뚫고 넘어가면 2의보수로나옴
// 제일 앞의 수가 %d로 쓰면 부호(+-)비트로 쓰이고 %u로 쓰이면 데이터비트로 쓰인다.
#include <stdio.h>

int main()
{
	unsigned int a;
	a = 4294967295;	//큰 양수 저장
	printf("%d\n", a);	//%d로 출력
	a = -1;			// 음수 저장
	printf("%u\n", a);	//%u로 출력

	return 0;
}