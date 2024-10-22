#include <stdio.h>

int main()
{
	int score[5];
	int i;
	int tot = 0;
	double avg;

	//for (i = 0; i < 5; i++)
	//{
	//	scanf("%d", &score[i]);
	//}

	for (i = 0; i < 5; i++)
	{
		scanf("%d", score + i);    // score 자체는 주소이므로 이렇게 사용해도 된다.
	}

	for (i = 0; i < 5; i++)
	{
		tot += score[i];
	}
	avg = tot / 5.0;

	for (i = 0; i < 5; i++)
	{
		printf("%5d", score[i]);    //%5d는 5칸을 만들어 놓고 오른쪽으로 정렬한다. ---80/---95
	}								//%-5d는 왼쪽부터 정렬한다. (5칸 만드는 건 똑같다.)
	printf("\n");

	printf("%.1lf\n", avg);

	return 0;
}