#include <stdio.h>

int main()
{
	int year; 
	int result;
	scanf("%d", &year);
	
	
	if(year >= 0 && year <= 4000)
	{
		if(year%4 == 0)
		{
			if(year%100 != 0 || year%400 == 0)
			{
				result = 1;
			}	
		}
	}
	else
	{
		result = 0;
	}
	
	
	
	printf("%d", result);
	
	return 0;
}
