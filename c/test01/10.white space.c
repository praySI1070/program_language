#include <stdio.h>

int main()
{
	char grade;
	char name[20];
	//문자를 받고 문자의 끝에 있던 엔터를 문자열에서 문저 받아버리기떄문에 > 화이트 스페이스라는 버퍼에서 먼저 받고, 문자를 받게 학 된다.
	printf("이름 입력: ");
	scanf("%s", name);
	/*printf("학점 입력: ");
	scanf(" %c", &grade);*/	
	printf("학점 입력: ");
	getchar();
	scanf("%c", &grade);
						// getchar함수를 써서도 비슷하게 사용할 수 있다.

	/*printf("이름 입력: ");
	scanf("%s", name);*/
	printf("%s의 학점은 %c입니다.\n", name, grade);


	return 0;
}