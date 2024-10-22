#include <stdio.h>

void print_char(char ch, int cnt);

int main()
{
	print_char('@', 13);

	return 0;
}

void print_char(char ch, int cnt)
{
	int i;

	if (cnt > 10)
	{
		printf("종료됩니다.");
		return;
	}
	for (i = 0; i < cnt; i++)
	{
		printf("%c", ch);
	}
}