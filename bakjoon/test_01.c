#include <stdio.h>
#include <stdlib.h>

void check(char*, char*);

int main()
{
	char S[21] = { 0 };	//#QR code만 들어있음(0123456789ABCDEFGHIJK...Z\$%*+-./:)
	char* S_ = (char*)calloc(180, sizeof(char));
	char* ptr_S = S;
	char* ptr_S_ = S_;
	int T, R;
	int count = 0, count_ = 0;
	int count_1 = 0;
	scanf("%d", &T);
	//	printf("T: %d\n", T);
	if (T < 1 || T > 1000) {
		return 0;
	}

	for (int j = 0; j < T; j++)
	{
		int k = 0;
		scanf("%d %s", &R, S);
		//		printf("R: %d\n", R);
		//		printf("S : %s\n", S);
		if (R > 9 || R < 1) {
			return 0;
		}
		check(ptr_S, S_);

		//		printf("count_f :%d\n", count_);
		for (k = 0; k < 21; k++)
		{
			if (*(ptr_S + k) == '\0') {
				break;
			}
			for (int x = 0; x < R; x++)
			{
				//				printf("count_: %d\n", count_);
				*((ptr_S_)+count_ + count_1 + x + (R * k)) = *((ptr_S)+k);
			}
			count++;
			//			printf("count : %d\n", count);
			//			printf("S_ : %s\n", S_);
		}
		S_ = (char*)realloc(S_, sizeof(char) * (180 + count_1 + count_ + (R * k)));
		*((ptr_S_)+count_1 + count_ + (R * k)) = '1';
		for (int y = 0; y < count_1 + count_ + (R * k); y++)
		{
			*(ptr_S_ + 180 + y) = '\0';
		}
		count_1++;
		count_ = R * count;
		//		printf("!!: count_ : %d\n", count_);
		//		printf("count_1 : %d\n", count_1);
		//		printf("R*k : %d\n", R*k);
		//		printf("%s\n", S_);
	}

	for (int i = 0; i < count_ + count_1; i++)
	{
		if (*(ptr_S_ + i) != '1') {
			printf("%c", *(ptr_S_ + i));
		}
		else {
			printf("\n");
		}
	}

	free(S_);

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
					free(*b);
					exit(0);
			}
		}
	}

	//	printf("함수실행됨\n");

	return;
}
