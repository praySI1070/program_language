#include <stdio.h>

int main(void)
{
	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);
	int c1 = b%10;
	int c10 = b/10%10;
	int c100 = b/100%10;

	if(a>=100&&b>=100)
		if(a<1000 && b<1000)
			printf("%d\n", a*c1);
			printf("%d\n", a*c10);
			printf("%d\n", a*c100);
			printf("%d", a*b);
			
	return 0;
}
