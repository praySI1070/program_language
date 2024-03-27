#include <stdio.h>

int check_zero(int a);
int change(int a);

int main()
{
	int A = 0, B = 0;
	scanf("%d %d", &A, &B);
	if (A < 100 || A >999 || B < 100 || B > 999) {
		return 0;
	}
	if (A == B) {
		return 0;
	}
	if (check_zero(A) == 1) {
		return 0;
	}
	if (check_zero(B) == 1) {
		return 0;
	}
	
	int changed_A = change(A);
	int changed_B = change(B);

	if (changed_A > changed_B) {
		printf("%d", changed_A);
	}
	else {
		printf("%d", changed_B);
	}

	return 0;
}

int check_zero(int a)
{
	int check = 0;
	if (a / 100 % 10 == 0) {
		check = 1;
	}
	if (a / 10 % 10 == 0) {
		check = 1;
	}
	if (a % 10 == 0) {
		check = 1;
	}

	return check;
}

int change(int a)
{
	int A = a / 100 % 10;
	int B = a / 10 % 10;
	int C = a % 10;
	int result = 100 * C + 10 * B + A;

	return result;
}
