#include <stdio.h>

int main()
{
	char S[101] = "ABC";
	int check[27] = {0};
	char *ptr_S = S;
	int *ptr_c = check;
	
	for(int i = 0; i< 26; i++)	//알파뱃 넣기 
	{
		*(ptr_c + i) = 97+i;
	}
//	printf("%d\n", *(ptr_c + 1));
	
	scanf("%s", S);
	for(int i =0; i <100; i++)	//소문자 확인 
	{
		if(*(ptr_S) > 122 || *(ptr_S) <97) {
			return 0;
		}
	}
//	printf("%d\n", *(ptr_S + 1));
	
	for(int i =0; i<26; i++)
	{
		int count = 0;
		for(int j = 0; j < 100; j++)
		{
			if(*(ptr_c + i) == *(ptr_S + j))
			{
				*(ptr_c + i) = j;
//				printf("i:%d :%d\n",i, *(ptr_c + i));
				break;
			}
			else
			{
				count ++;
//				printf("i:%d : j:%d count : %d\n", i , j, count);
			}
			if(count == 100) {
				*(ptr_c + i) = -1;
			}
		}
	}
	
	for(int i = 0; i<26; i++)
	{
		printf("%d ", *(ptr_c + i));
	}
	
	return 0;
}
