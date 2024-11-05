#include "thread_shared_header.h"
#include <atomic>


//CAS (Compare-And-Swap)계열의 함수는 atomic과 비슷한 효과를 본다.
//bool compare_exchange_strong(bool &_Expected, const bool _Desired)voltile

class SpinLock
{
public:
	//이 함수가 동시에 작동하게 만들어야한다.
	void before_lock()
	{
		while (_locked) {

		}

		_locked = true;
	}

	void lock()
	{
		bool expected = false;
		bool desired = true;

		/*
		CAS의사 코드
		if (_locked == expected)
		{
			expected = _locked; 
			_locked = desired; 
			return true; 
		}
		else
		{
			expected = _locked;
			return false;
		*/

		while (_locked.compare_exchange_strong(expected, desired) == false) {
			expected = false;
		}
	}

	void unlock()
	{

		//_locked = false;
		//그냥 하면 bool타입인줄 햇갈림
		_locked.store(false);
	}
private:
	//atomic이 volatile기능도 포함하고 있음
	atomic<bool> _locked = false;
	//volatile bool _locked = false;
};



int32 sum = 0;
mutex m;
SpinLock spinlock;



void Add()
{
	for (int32 i = 0; i < 10'0000; i++) {
		lock_guard<SpinLock> guard(spinlock);
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 10'0000; i++) {
		lock_guard<SpinLock> guard(spinlock);
		sum--;
	}
}

int main()
{

	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	print(sum);
}