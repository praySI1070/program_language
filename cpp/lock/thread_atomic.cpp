#include "thread_shared_header.h"
#include <atomic>

using namespace std;

atomic<int> sum = 0;

//���� ���� �� �ڵ�� ����������, ������ cpu�� �����ϴ°��� 
//int32 eax = sum;
//eax = eax - 1;
//sum = eax;
//3���̱⿡ threadȯ�濡�� ���ÿ� �۵����ϸ� sum++�̶�� ��ɾ �� ������ �ϱ�����
//sum--;��� ��ɾ �߰��� ����.
//���� atomic�̶�� �ϳ��� �������� ������ִ� ���� ����ؼ� ���� ������ ������ �ٷ��.

//������ ����ӵ��� ������, ���������� �߻��� �� �����Ƿ� �����ϸ� �ȵȴ�.

//���� ����Ʈ https://devriripong.tistory.com/14
void Add()
{
					//������ �÷��ִ� �����
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