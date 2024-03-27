#include <stdio.h>

int change(int *a, int *b);

int main()
{
	int a = 1;
	int b = 2;
	
	printf("%d\n", a);
	printf("%d\n", b);
	
	change(&a,&b);
	
	printf("%d\n", a);
	printf("%d\n", b);
	
	return 0;
}

int change(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
	return 0;
}
