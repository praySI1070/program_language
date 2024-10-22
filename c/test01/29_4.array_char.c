//문자열도 배열과 같은 주소개념이다.
//배열에 배열을 넣으면 널문자는 들어가는 것인가? 들어감 -> 문자열은 첫번쨰로 만나는 널문자까지를 문자열의 끝으로 본다.
#include <stdio.h>
#include <string.h>

int main()
{
	char str[80] = "applejam";
	char stt[5] = "+++";
	printf("최초 문자열 : %s\n", str);
	printf("문자열 입력 :");
	scanf("%s", str);
	printf("입력 후 문자열 : %s\n", str);
	strcpy(str, stt);	//문자열 저장 함수.
	puts(str);	//문자열 전용 프린트f 함수

	return 0;
}