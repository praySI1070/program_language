#include <stdio.h>

int main()
{
	int a = 5, b = 5;
	int pre, post;

	pre = (++a) * 3;	//전위형은 즉시저장
	post = (b++) * 3;	//후위형은 식이 끝난 후에 반영 지금시점 b는 5이 다음줄에선 6

	printf("초기값 a = %d\n, b = %d\n", a, b);
	printf("전위형: (++a)*3=%d, 후위형: (b++)*3=%d\n", pre, post);

	return 0;
}