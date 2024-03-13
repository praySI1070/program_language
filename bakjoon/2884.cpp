#include <stdio.h>

int main()
{
	int H,M;
	scanf("%d %d", &H, &M);
	
	if(H >= 0 && H <= 23 && M >= 0 && M <= 59)
		if(M <=45 && H <= 0) {
			H =23;
			M += 15;
		}
		else if(M <45) {
			H -= 1;
			M += 15;
		}
		else if(M >=45) {
			M -= 45;
		}
	printf("%d %d", H, M);
}
