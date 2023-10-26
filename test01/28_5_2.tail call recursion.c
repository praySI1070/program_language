//꼬리 재귀 - 재귀 함수의 열려있는 함수들이 계속 메모리를 먹는다는 단점을 함수쪽에 연산을 없애는 것으로 극복한 방법
#include <stdio.h>

int main()
{
    printf("%d",Factorial(5));
}

/*int factorial(int n)    //원형
{
    int ;
    if (n == 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}*/

int FactorialTail(int n, int acc)    // acc : accumulator의 약자

{

    if (n == 1) return acc;

    return FactorialTail(n - 1, acc * n);    //  일반 재귀에서의 n * Factorial(n-1)와 달리 반환값에서 추가 연산을 필요로 하지 않음

}



int Factorial(int n)

{

    return FactorialTail(n, 1);

}