//문자열을 배열 형탤 저장할 떄는 배열안의 숫자를 문자열 숫자의 +1을 해줘야한다.
//널문자를 문자열의 끝으로 판단하기떄문이다
//배열의 주소는 첫번쨰 문자의 주소이다.

#include <stdio.h>

int main()
{
	char fruit[20] = "strawberry";	//char 배열 선언과 초기화  0~19까지 방
									//빈방은 전부 널문자로 찍혀있다.

	printf("딸기 : %s\n", fruit);	//배열명으로  strawberry 출력
	printf("딸기쨈 : %s %s\n", fruit, "jam");	// 문자열은 %s로 출력
	printf("좋아하는 과일 : %s\n", fruit);

	return 0;
}