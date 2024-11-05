#include "thread_shared_header.h"
#include <mutex>

//한쪽이 v를 건드리는 동안 다른쪽이 v를 건드리지 못하게 하는 것을 lock이라 한다.
//Mutual Exclusive(상호 베타적)
//mutex는 재귀적으로 호출 불가


//C++의 유명한 패턴 RAII(Resource Acquisition IS Initialization)(리소스 획득이 초기화됨)
//wrapper class
template<typename T>
class LockGuard
{
public:
	explicit LockGuard(T& m)		//explicit는 자신이 원하지 않는 형변환이 일어나지 않도록 제한하는 키워드
	{
		_mutex = &m;
		_mutex->lock();
	}

	~LockGuard()
	{
		_mutex->unlock();
	}
private:
	T* _mutex;
};

vector<int> v;
mutex m;

//void Push()
//{
//	for (int i = 0; i < 10000; i++) {
//		m.lock();
//
//		v.push_back(i);
//
//		m.unlock();
//	}
//}

void Push()
{
	for (int i = 0; i < 1'0000; i++) {
		//자물쇠
		LockGuard<mutex> LockGuard(m);

		v.push_back(i);
	}
}

int main()
{
	thread t1(Push);
	thread t2(Push);

	t1.join();
	t2.join();

	print(v.size());
}