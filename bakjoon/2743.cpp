#include <stdio.h>

int main()
{
	int i = 0;
	char S[101] = {0};
	char *ptr = S;
	
	scanf("%s" ,S);
	if(sizeof(S) > sizeof(char) * 101) {
		return 0;
	}
	
	for(i = 0; i<100; i++)
	{
		if(*(ptr + i) == '\0') {
			break;
		}
	}
	
	printf("%d", i);
	
	return 0;
}
