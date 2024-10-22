#include "pray.h"
#include <random>

int main()
{
	int count = -1;
	while (count != 0) {
		input(count, "몇개를 생성할까요?(1개이상, 0은 종료)");
		if (count > 0) {
			break;
		}
		else if(count < 0) {
			println("잘못된 숫자입니다.");
		}
		else {
			println("종료되었습니다.");
		}
	}
	

	//시드값 생성
	random_device rd;

	//난수 생성 엔진 초기화
	mt19937 gen(rd());

	//0~100까지 난수 생성
	uniform_int_distribution<int> dis(0, 100);

	Node* pre = new Node;
	pre->name = "S1";
	Node* node = pre;
	pre->x = dis(gen);
	pre->y = dis(gen);
	pre->distance = cal_distance(pre);

	if (count >= 2) {
		for (int i = 2; i <= count; i++) {
			Node* new_node = new Node;
			new_node->name = "S";
			new_node->name += to_string(i);
			new_node->x = dis(gen);
			new_node->y = dis(gen);
			new_node->distance = cal_distance(new_node);
			new_node->pre = pre;
			pre->post = new_node;
			pre = new_node;
		}
	}
	pre->post = node;
	node->pre = pre;


	pre = node;

	println("정렬전");
	print_node(pre, count);

	//정렬함수
	node = sort_linked(node,count);

	pre = node;
	for (int i = 0; i < 2; i++) {
		println("");
	}
	println("정렬후");
	print_node(pre, count);

	exit_Linked(node,count);

	return 0;
}