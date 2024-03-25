#include <stdio.h>

void check (int*);

int main()
{
	char S[21] = {0};	//#QR code만 들어있음(0123456789ABCDEFGHIJK...Z\$%*+-./:) 
	char S_[161] = {0};
	char *ptr_S = S;
	char *ptr_S_ = S_;
	int T,R;
	scanf("%d", &T);
	if(T < 1 || T > 1000) {
		return 0;
	}
	
	for(int j = 0; j< T; j++)
	{
		scanf("%d %s", &R, S);
		if(R > 9 || R < 1) {
		return 0;
		}
		check(ptr_S);
		
		for(int k =0; k<20; k++)
		{
			if(*(ptr_S + k) == '\0') {
				break;
			}
			for(int x = 0; x<R; x++)
			{
				*((ptr_S_) +x + 8k) = *((ptr_S) + k);
			}
		}
	}
	
	
	
	
	return 0;
}

void check(int *a)
{
	for(int i =0; i<21; i++)
	{
		if(*a > 90 || *a < 48){
			if(*a >= 42 && *a <=47) {
				break;
			}
			switch (*a) {
			case 92:
				break;
			case 36:
				break;
			case 37:
				break
			case 58:
				break
			}
			return 0;
		}
	}

	printf("함수실행됨");
	
	return;
}
