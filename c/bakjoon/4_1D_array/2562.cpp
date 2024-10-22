#include <stdio.h>

void change(int*,int*);

int main()
{
	int natural[9] ={0};
	int check[9] = {0};
	int *ptr = natural;
	int *ptr_ = check;
	
	for(int i=0; i<9; i++)
	{
		scanf("%d", (ptr + i));
	}
	
	for(int i=0; i<9; i++)
	{
		if(*(ptr + i) <= 0)
		{
			return 0;
		}
		else
		{
			continue;
		}
	}
	
	for(int i=0; i<9; i++)
	{
		*(ptr_ + i) = *(ptr + i);
	}
	
	for(int i=0; i<9; i++)
	{
		if(*ptr >= *(ptr + i))
		{
			continue;
		}
		else
		{
			change(ptr,(ptr + i));
		}
	}
	
	printf("%d\n", *ptr);
	
	for(int i=0; i<9; i++)
	{
		if(*ptr == *(ptr_+i))
		{
			printf("%d\n", i+1);
		}
		else
		{
			continue;
		}
	}
	
	return 0;
}

void change(int *a, int*b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
	return;
}
