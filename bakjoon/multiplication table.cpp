#include <stdio.h>

int main()
{
	int i, j, k = 0;
	
	for(k=0; k<5; k++)
	{
		for(j=1; j<=9; j++)
		{
			for(i=1+3*k; i<=3+3*k; i++)
			{
				printf("%d * %d = %d\t", i, j, i*j);
				if(i%3==0) printf("\n");
			}
		}
	}
	
	return 0;
}
