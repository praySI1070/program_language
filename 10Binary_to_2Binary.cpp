#include <stdio.h>

int main()
{
	int value = 47;
	
	for(unsigned int i= 1<<31; i > 0; i = 1/2)	// i 를 2로 나누는 이유는 한칸을 오른쪽으로 떙기기 위해서이다. 
	(value & i) ? printf("1"): printf("0");		//value는 컴퓨터에는 이미 2진수로 저장되어 있기 떄문에 &연산을 사용할 수 있다. 
	
	return 0;
}
