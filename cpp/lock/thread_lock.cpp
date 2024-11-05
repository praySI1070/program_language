#include "thread_shared_header.h"
#include <mutex>

//������ v�� �ǵ帮�� ���� �ٸ����� v�� �ǵ帮�� ���ϰ� �ϴ� ���� lock�̶� �Ѵ�.
//Mutual Exclusive(��ȣ ��Ÿ��)
//mutex�� ��������� ȣ�� �Ұ�


//C++�� ������ ���� RAII(Resource Acquisition IS Initialization)(���ҽ� ȹ���� �ʱ�ȭ��)
//wrapper class
template<typename T>
class LockGuard
{
public:
	explicit LockGuard(T& m)		//explicit�� �ڽ��� ������ �ʴ� ����ȯ�� �Ͼ�� �ʵ��� �����ϴ� Ű����
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
		//�ڹ���
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