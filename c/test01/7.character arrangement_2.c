//

#include <stdio.h>
//배열명은 주소상수임으로 대입연산자쪽에 사용불가 (lvalue)
#include <string.h>

int main()
{
	char fruit[20] = "strawberry";	//strawberry초기화

	printf("%s\n", fruit);	//strawberry 출력
	strcpy(fruit, "banana");	//fruit에 banana복사(뒤쪽에 추가가 아니라 덮어쓰기
	printf("%s\n", fruit);	//banana출력

	return 0;
}