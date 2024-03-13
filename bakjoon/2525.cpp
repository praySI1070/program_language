#include <stdio.h>

int main()
{
	int A,B,C;
	int time,minute;
	scanf("%d %d", &A, &B);
	scanf("%d", &C);
	int D = 0;
	while(C >59) {
		C -= 60;
		D++;
	}
	minute = B + C;
		if(minute >= 60) {
			A += 1;
			minute -= 60;
		}
	time = A + D;
		if(time >= 24) {
			time -= 24;
		}
	printf("%d %d", time, minute);
}
