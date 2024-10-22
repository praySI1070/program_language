#include <stdio.h>

int check(char*);
int check_d(char*);
int check_space(char*,int *);

int main()
{
	char S[10000] = { 0 };
	char* ptr_S = S;
	int len = 0;
	scanf("%[^\n]s", S);
	//if (check(S) != 1) {
		//return 0;
	//}
	//if (check_d(S) == 1) {
		//return 0;
	//}

	int str_number = 0;
	str_number = check_space(S, &len);
	if (*ptr_S == 32) {
		str_number--;
	}
	if (*(ptr_S + len-1) == 32) {
		str_number--;
	}

	printf("%d", str_number + 1);

	return 0;
}

int check(char* a)	// 알파뱃 , ' '확인
{
	int check_re = 0;
	for (int i = 0; i < 1000001; i++)
	{
		if (*(a + i) == '\0') {
			break;
		}
		if (*(a + i) >= 65 && *(a + i) <= 122) {
			check_re = 1;
		}
		if (*(a + i) == 32) {
			check_re = 1;
		}
	}

	return check_re;
}

int check_d(char* a)	//공백 두 번 연속 확인
{
	int check_re = 0;
	for (int i = 0; i < 1000001; i++)
	{
		if (*(a + i) == '\0') {
			break;
		}
		if (*(a + i) == 32 && *(a + i + 1) == 32) {
			check_re = 1;
		}
	}

	return check_re;
}

int check_space(char* a, int* b)
{
	int check_re = 0;
	for (int i = 0; i < 1000001; i++)
	{
		if (*(a + i) == '\0') {
			break;
		}
		*b += 1;
		if (*(a + i) == 32) {
			check_re++;
		}
	}

	return check_re;
}
