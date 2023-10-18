#include <stdio.h> //stdio.h에 저장된 함수를 불러옴

int main() // 함수는 구조 <반환형 / 함수이름 / 매개변수>로 되어있다. int는 반환형 main은 함수이름 ()안에는 변수
{
	
	printf("1234578901234567890\n");	// 12345678901234567890프린트 후 개행
		printf("Be happy\n");			// Be happy 출력 후 개행
		printf("My\tfriend\n");			// My tab만큼 뛰어쓰기 friend 출력 후 개행
		printf("Goot\bd\tchance\n");	// Goot에서 t를 d로 바꾸고 tab하고 chance 출력 후 개행
		printf("Cow\rW\a\n");			// Cow에서 제일앞문자를 W로 교체후 알람 후 개행


		printf("%d\n", 10);
		printf("%lf\n", 3.4);					//실수를 표기
		printf("%.1lf\n", 3.45);				//실수 아래 한자리표기
		printf("%.10lf\n", 3.12345678901);		//실수아래 열자리까지 표기

		printf("%d과 %d의 합은 %d입니다.\n", 10, 20, 10 + 20);
		printf("%.1lf - %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2);
		
		printf("%c\n", 'A');		//%c는 문자를 읽음
		printf("%d\n", 'A');		//A는 아스키코드로 65임
		printf("%d\n", 'a');		//a는 아스키코드로 97임
		printf("%c\n", 65);			//반대로 숫자를 문자로도 바꿈
		printf("%s\n", "A");		//%s는 문자열을 읽음
		printf("%c은 %s입니다.", '1', "first");

}
