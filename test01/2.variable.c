#include <stdio.h>
// 변수선언
/*엔디안 = 컴퓨터의 메모리와 같은 1차원의 공가에 여러개의 연속된 대상을 배열하는 
방법 - 빅엔디언과 리틀 엔디언이 있으며 빅엔디언은 정순으로 정렬
리틀 엔디언은 1바이트씩 역순으로 정렬된다. 미드 엔디언은 랜덤(?)*/

int main(void)
{
	int a;	//int형 변수선언
	int b, c;	//두개의 int형 변수를 동시 선언
	double da;	//double형 변수선언
	char ch;	//char형 변수선언

	a = 10;		//a=10으로 선언
	b = a;		//b에 a값을 대입
	c = a + 20;	//c에 a값+20
	da = 3.5;	//double변수  da에 실수3.5대입
	ch = 'A';	//A대입

	printf("변수 a의 값 : %d\n", a);
	printf("변수 b의 값 : %d\n", b);
	printf("변수 a의 값 : %d\n", c);
	printf("변수 a의 값 : %.1lf\n", da);
	printf("변수 a의 값 : %c\n", ch);

	return 0;
}