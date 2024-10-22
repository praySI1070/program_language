#include <stdio.h>

int main()
{
	char word[16] = { 0 };
	char* ptr_w = word;
	int time = 0;

	scanf("%s", word);
	if (*(ptr_w + 1) == '\0' || *(ptr_w + 0) == '\0') {
		return 0;
	}

	for (int i = 0; i < 15; i++)
	{
		if (*(ptr_w + i) == '\0') {
			break;
		}
		if (*(ptr_w + i) < 65) {
			return 0;
		}
		else if (*(ptr_w + i) >= 65 && *(ptr_w + i) <= 67) {
			time += 3;
		}
		else if (*(ptr_w + i) >= 68 && *(ptr_w + i) <= 70) {
			time += 4;
		}
		else if (*(ptr_w + i) >= 71 && *(ptr_w + i) <= 73) {
			time += 5;
		}
		else if (*(ptr_w + i) >= 74 && *(ptr_w + i) <= 76) {
			time += 6;
		}
		else if (*(ptr_w + i) >= 77 && *(ptr_w + i) <= 79) {
			time += 7;
		}
		else if (*(ptr_w + i) >= 80 && *(ptr_w + i) <= 83) {
			time += 8;
		}
		else if (*(ptr_w + i) >= 84 && *(ptr_w + i) <= 86) {
			time += 9;
		}
		else if (*(ptr_w + i) >= 87 && *(ptr_w + i) <= 90) {
			time += 10;
		}
		else {
			return 0;
		}
	}

	printf("%d", time);

	return 0;
}
