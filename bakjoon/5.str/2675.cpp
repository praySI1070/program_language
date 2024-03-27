#include <stdio.h>
#include <stdlib.h>

void check(char*, char*);
int len(char*);

int main()
{
	char S[21] = { 0 };	//#QR code만 들어있음(0123456789ABCDEFGHIJK...Z\$%*+-./:)
	char S_[161] = { 0 };
	//char* S_; 
	//if (S_ = (char*)calloc(1602000, sizeof(char) == NULL)) {
		//fprintf(stderr, "Insufficient memory");
		//exit(EXIT_FAILURE);
	//}

	char* ptr_S = S;
	char* ptr_S_ = S_;
	int T, R;
	scanf("%d", &T);
	
	for (int i = 0; i < T; i++)
	{
		scanf("%d %s", &R, S);
		int len_S = len(S);
		for (int j = 0; j < len_S; j++)
		{
			for (int k = 0; k < R; k++)
			{
				*(ptr_S_ + (k + (R * j))) = S[j];
			}
		}
		*(ptr_S_ + (R + (R * (len_S - 1)))) = '\0';
		printf("%s\n", S_);
	}

	return 0;
}

void check(char* a, char* b)
{
	for (int i = 0; i < 21; i++)
	{
		if (*(a + i) == '\0') {
			break;
		}
		if (*(a + i) > 90 || *(a + i) < 48) {
			switch (*(a + i)) {
			case '\\':
				break;
			case '$':
				break;
			case '%':
				break;
			case '*':
				break;
			case '+':
				break;
			case '-':
				break;
			case '.':
				break;
			case '/':
				break;
			case ':':
				break;
			default:
				//free(*b);
				exit(0);
			}
		}
	}

	return;
}

int len(char* a)
{
	char* ptr_len = a;
	int count = 0;
	while (1)
	{
		if (*(ptr_len + count) == '\0') {
			break;
		}
		else {
			count++;
		}
	}


	return count;
}
