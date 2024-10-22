#include <stdio.h>

int main()
{
	int income = 0;		//소득액 초기화
	double tax;			// 세금
	const double tax_rate = 0.12;	//세율 초기화 , double을 입력해 주지 않으면 값이 소실될 수 있음.
	//const는 값을 지정하면 이후에는 값을 수정할 수 없음.
	//double tax_rate = 0.15 -> 후에 값을 지정하더라도 바뀌지않음.

	income = 456;		//소득액 저장
	tax = income * tax_rate;	//세금계산
	printf("세금은 : %.1lf입니다.\n", tax);

	return 0;
}