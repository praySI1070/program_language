#include <stdio.h>

int main()
{
	int year,result;
	scanf("%d", &year);
	
	if(year%400 == 0) {
		result =1;
	}
	else if(year%100 == 0) {
		result = 0;
	}
	else if(year%4 == 0) {
		result = 1;
	}
	else
		result =0;
	printf("%d", result);
	
	return 0;
}
