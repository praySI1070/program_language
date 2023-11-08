//ary ++; 은 불가능 배열은 상수이므로
//pa ++; 은 가능
#include <stdio.h>

//int main()
//{
//	int ary[3];
//	int i;
//
//	*(ary + 0) = 10;
//	*(ary + 1) = *(ary + 0) + 10;
//
//	printf("세 번쨰 배열 요소에 키보드 입력 :");
//	scanf("%d", ary + 2);
//
//	for (i = 0; i < 3; i++)
//	{
//		printf("%5d", *(ary + i));
//	}
//
//	return 0;
//}

//배열을 포인터식으로 바꿈

int main()
{
	int ary[3];
	int* pa = ary;
	int i;

	*pa = 10;
	*(pa + 1) = 20;
	pa[2] = pa[0] + pa[1];

	for (i = 0; i < 3; i++)
	{
		printf("%5d", pa[i]);
	}

	return 0;
}