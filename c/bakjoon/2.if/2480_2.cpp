#include <stdio.h>

int main()
{
	int A, B, C;
	int reward;
	scanf("%d %d %d", &A, &B, &C);
	
	if(A == B && B == C) {
		reward = 10000+1000*A;
	}
	if(A == B && B != C) {
		reward = 1000+ 100*A;
	}
	if(A == C && B != C) {
		reward = 1000+ 100*A;
	}
	if(A != B && B == C) {
		reward = 1000 + 100 * B;
	}
	if(A != B && B != C && A != C) {
		if(A > B && A > C) {
			reward = 100 * A;
		}
		if(B >A && B > C) {
			reward = 100 * B;
		}
		if(C > A && C > B) {
			reward = 100 * C;
		}
	}
	
	printf("%d", reward);
	return 0;
}
