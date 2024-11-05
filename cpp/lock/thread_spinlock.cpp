#include "thread_shared_header.h"
#include <atomic>


//CAS (Compare-And-Swap)�迭�� �Լ��� atomic�� ����� ȿ���� ����.
//bool compare_exchange_strong(bool &_Expected, const bool _Desired)voltile

class SpinLock
{
public:
	//�� �Լ��� ���ÿ� �۵��ϰ� �������Ѵ�.
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
		CAS�ǻ� �ڵ�
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
		//�׳� �ϸ� boolŸ������ �ް���
		_locked.store(false);
	}
private:
	//atomic�� volatile��ɵ� �����ϰ� ����
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