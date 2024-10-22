// 예약어는 이미 선언이 되어있는 언어, 식별자는 나머지 대문자 소문자 숫자 _로 만든 변수 -> 시작은 숫자로는 못함
//주소를 저장할 때는 int*뒤에 *인 포인터 변수를 붙여서 만든다.
#include <stdio.h>

int main()
{
	int a;

	scanf("%d", &a);
	printf("입력된 값 : %d\n", a);

	int age;
	double height;

	//printf("나이와 키를 입력하세요: ");	//입력 안내 메시지 출력
	//scanf("%d%lf", &age, &height);		//나이와 키를 함께 입력
	printf("나이를 입력하세요: ");
	scanf("%d", &age);
	printf("키를 입력하세요: ");
	scanf("%lf", &height);
	printf("나이는 %d살, 키는 %.1lfcm입니다.\n", age, height);	//입력값 출력

	if (a == 1)
		printf("1번");
	else if (a == 2)
		printf("2번");
	else
		printf("아무것도아님");	//if문 주의점 : if와 else는 한번만 사용, else if 는 여러번else가 else if보다 빨리오면 오류

	return 0;
}