#include <stdio.h>

int main()
{
	int ch;

	printf("문자 a의 아스키 코드 값 : %d\n", 'a');
	printf("아스키 코드값이 97인 문자 : %c\n", 97);
	printf("문자 상수의 크기 : %d바이트\n", sizeof('a'));

	ch = 'a';
	ch++;
	printf("문자 %c의 아스키 코드 값 : %d\n", ch, ch);

	return 0;
}