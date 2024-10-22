#include <stdio.h>

int main()
{
	char small, cap = 'G';

	if ((cap >= 'A') && (cap <= 'Z'))
	{
		small = cap + ('a' - 'A');
	}
	printf("대문자 : %c %c", cap, '\n');	//개행 문자를 캐릭터에 넣어도 작동한다.
	printf("소문자 : %c", small);

	return 0;
}