#include <stdio.h>

void swap(int* pa, int* pb);

int main()
{
	int a = 10, b = 20;

	swap(&a, &b);
	printf("a:%d, b%d\n", a, b);

	return 0;
}

void swap(int* pa, int* pb)	//지역변수를 바꿀 수 있다.
{
	int temp;

	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

//void swap();   //메인 함수의 a,b를 건드는 것은 포인터가 없으면 하지 못함.
//
//int main()
//{
//	int a = 10, b = 20;
//
//	swap();
//	printf("a:%d, b:%d\n", a, b);
//
//	return 0;
//}
//
//void swap()
//{
//	int temp;
//
//	temp = a;
//	a = b;
//	b = temp;
//}

//void swap(int x, int y);  //이거도 작동 안함.
//
//int main()
//{
//	int a = 10, b = 20;
//
//	swap(a,b);
//	printf("a:%d, b:%d\n", a, b);
//
//	return 0;
//}
//
//void swap(int x, int y)
//{
//	int temp;
//
//	temp = x;
//	x = y;
//	y = temp;
//}