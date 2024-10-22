#include <stdio.h>

int main()
{
	int ary1[5] = { 1,2,3,4,5 };
	int ary2[5] = { 1,2,3 };
	int ary3[] = { 1,2,3,4 };
	double ary4[5] = { 1.0,2.1,3.2,4.3,5.4 };
	char ary5[5] = { 'a','b','c','d','e' };

	ary1[0] = 10;
	ary1[1] = 20;
	ary1[2] = 30;
	ary1[3] = 40;
	ary1[4] = 50;

	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", ary1[i]);
	}
	printf("---\n");

	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", ary2[i]);
	}
	printf("---\n");

	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", ary3[i]);
	}
	printf("---\n");

	for (int i = 0; i < 5; i++)
	{
		printf("%lf\n", ary4[i]);
	}
	printf("---\n");

	for (int i = 0; i < 5; i++)
	{
		printf("%c\n", ary5[i]);
	}

	return 0;
}