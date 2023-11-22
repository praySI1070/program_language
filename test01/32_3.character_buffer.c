//버퍼는 메모리에 있는 임시 저장 공간
//입출력 버퍼의 이름 직접 사용하는 함수
//ffluh함수는 이제 사용 불가 (호완성문제)
//while(getchar()!='\n');사용하는게 제일 좋음(보편적)
//scanf함수는 호출 즉시 버퍼에서 데이터를 가져옴

#include <stdio.h>

int main()
{
	char ch;
	int i;

	for (i = 0; i < 3; i++)		//3개까지는 버퍼에 안남지만, 넘으면 남음
	{
		scanf("%c", &ch);
		printf("%c", ch);
	}

	while (getchar() != '\n');	//버퍼에서 빼기
	printf("\n");

	scanf("%c", &ch);	//다시입력
	printf("%c", ch);

	return 0;
}