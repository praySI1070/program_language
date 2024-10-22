#include <stdio.h>

int main()
{
	int check[42] = {0};
	int input_[10] = {0};
	int *ptr_c = &check[0];
	int *ptr_i = &input_[0];
	int count = 0;
	int cul;
	
	for(int i =0; i<42; i++)
	{
		*(ptr_c + i) = i;
	}
	
	for(int i=0; i <10; i++)
	{
		scanf("%d", &cul);
		*(ptr_i + i) = cul % 42;
	}
	
	for(int i = 0; i<42; i++)
	{
		for(int j = 0; j<10; j++)
		{
			if(*(ptr_c + i) == *(ptr_i + j))
			{
				*(ptr_c + i) = -1;
				count++;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	
	printf("%d", count);
	
	return 0;
}
