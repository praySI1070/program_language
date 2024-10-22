#include <stdio.h>

int main()
{
	int x,y;
	int c[30] = {0};
	int d[28] = {0};
	int *ptr = &c[0];
	int *ptr_ = &d[0];
	
	for(int i = 0; i <30; i++)
	{
		*(ptr + i) = i+1;
	}
	
	for(int i=0; i<28; i++)
	{
	scanf("%d", (ptr_+i));
	}
	
	for(int i =0; i<30; i++)
	{
		for(int j =0; j<28; j++)
		{
			if(*(ptr + i) == *(ptr_ + j))
			{
				*(ptr + i) = 0;
			}
			else
			{
				continue;
			}
		}
	}
	
	for(int i=0; i <30; i++)
	{
		if(*(ptr + i) != 0)
		{
			printf("%d\n", *(ptr + i));
		}
		else
		{
			continue;
		}
	}
	
	return 0;
}
