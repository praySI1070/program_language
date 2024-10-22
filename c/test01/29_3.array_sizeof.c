#include <stdio.h>

int main()
{
	int score[5];
	int i;
	int tot = 0;
	double avg;
	int cnt;

	cnt = sizeof(score) / sizeof(score[0]);		//배열 요소 수 계산

	for (i = 0; i < cnt; i++)
	{
		scanf("%d", score + i);
	}

	for (i = 0; i < cnt; i++)
	{
		tot += score[i];
	}
	avg = tot / (double)cnt;		//(double)을 쓰는 이유는 avg는 실수인데 tot와 cnt가 전부 정수이므로 실수 값으로 저장하기 위해서 하나를 실수로 변환해서 계산.

	for (i = 0; i < cnt; i++)
	{
		printf("%5d", score[i]);
	}
	printf("\n");

	printf("%.1lf\n", avg);

	return 0;
}