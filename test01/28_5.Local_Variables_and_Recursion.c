#include <stdio.h>

void fruit();

int main()
{
	fruit(1);

	return 0;
}

void fruit(int n)		//재귀함수는 함수가 끝나지 않은 상태에서 다음 함수를 호출하므로 호출된 함수가 끝나게 된다면, fruit(2)의 16번쨰 줄로 돌아가게 된다.
{
	printf("apple\n");
	if (n == 3) return;
	fruit(n+1);
}