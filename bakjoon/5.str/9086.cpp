#include <stdio.h>

int main()
{
	int T;
	scanf("%d", &T);
	if(T <1 || T > 10) {
		return 0;
	}
	
	char S[1000] = {0};
	char first[10] = {0};
	char last[10] = {0};
	char *ptr_S = S;
	char *ptr_f = first;
	char *ptr_l = last;
	
	for(int i = 0; i<T; i++)
	{
		scanf("%s" ,S);
		if(*(ptr_S+1) == '\0') {
			*(ptr_f + i) = *(ptr_S);
			*(ptr_l + i) = *(ptr_S);
			int a = 0;
			a++;
		}
		else
		{
			*(ptr_f + i) = *(ptr_S);
			int j;
			for(j = 0; j < 1000; j++)
			{
				if(*(ptr_S + j) == '\0')
				{
					break;
				}
			}
			*(ptr_l + i) = *(ptr_S + j-1);
		}
	}
	
	for(int i =0; i <T; i++)
	{
		printf("%c%c\n", *(ptr_f + i), *(ptr_l + i));
	}
	
	return 0;
}
