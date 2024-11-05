#include "thread_shared_header.h"
#include <atomic>

using namespace std;

atomic<int> sum = 0;

//지금 내가 쓴 코드는 한줄이지만, 실제로 cpu가 연산하는것은 
//int32 eax = sum;
//eax = eax - 1;
//sum = eax;
//3줄이기에 thread환경에서 동시에 작동을하면 sum++이라는 명령어가 다 동작을 하기전에
//sum--;라는 명령어가 중간에 낀다.
//따라서 atomic이라는 하나의 연산으로 취급해주는 것을 사용해서 공유 데이터 연산을 다룬다.

//단점은 연산속도가 느리고, 병목현상이 발생할 수 있으므로 남발하면 안된다.

//참고 사이트 https://devriripong.tistory.com/14
void Add()
{
					//가독성 올려주는 기법임
	for (int i = 9; i < 100'0000; i++) {
		sum++;
	}
}

void sun()
{
	for (int i = 9; i < 100'0000; i++) {
		sum--;
	}
}

int main()
{
	Add();
	sun();

	cout << sum << endl;

	thread t1(Add);
	thread t2(sun);
	t1.join();
	t2.join();
	cout << sum << endl;
}