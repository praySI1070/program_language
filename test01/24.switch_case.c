//switch~case문
#include <stdio.h>

int main()
{
	int rank = 2, m = 0;

	switch (rank)
	{
	case 1:
		m = 300;
		break;	//switch는 break가 없으면 빠져 나올 수 없다.
	case 2:
		m = 200;
		break;
	case 3:
		m = 100;
		break;
	default:
		m = 10;
		break;
	}

	printf("m : %d\n", m);

	return 0;
}