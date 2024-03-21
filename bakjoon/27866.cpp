#include <stdio.h>

int main()
{
	int i;
	char S[1000] = {0};
	char *ptr = &S[0];
	
	scanf("%s", S);
	scanf("%d", &i);
	printf("%c", *(ptr + i - 1));
	
	
	
	return 0;
}
