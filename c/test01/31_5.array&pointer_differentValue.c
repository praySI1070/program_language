#include <stdio.h>

void print_ary(int* pa, int size);

int main()
{
	int ary1[5] = { 10,20,30,40,50 };
	int ary2[7] = { 10,20,30,40,50,60,70 };
	int size_ary1 = sizeof(ary1) / sizeof(int);
	int size_ary2 = sizeof(ary2) / sizeof(ary2[0]);
	printf("%d\n", size_ary1);

	print_ary(ary1, size_ary1);
	printf("\n");
	print_ary(ary2, size_ary2);

	return 0;
}

void print_ary(int* pa, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%d ", pa[i]);
	}
}