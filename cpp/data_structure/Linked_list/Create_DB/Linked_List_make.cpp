#include "printT.h"
#include "Linked_list.h"
#include <sstream>


//test함수
void test() {
	println("test");
	return;
}


// 줄긋기 함수
void Line() {
	for (int i = 0; i < 15; i++)
		print("-");
	printf("\n");

	return;
}


//문자열 자르기 함수
s_s* str_slice(string data) {
	istringstream data_slice(data);
	string temp;
	s_s* sl = new s_s;

	int count = 0;
	while (getline(data_slice, temp, ',')) {
		switch (count)
		{
		case 0:
			sl->name = temp;
			break;
		case 1:
			sl->phone_num = temp;
			break;
		default:
			println("메모장의 형식이 이상합니다.");
			break;
		}
		count++;
	}

	return sl;
}


//문자열 숫자 변환 오류 함수
int error_num(string qu) {
	int check = 0;

	try {
		check = stoi(qu);
	}
	catch (invalid_argument& e) {		// &연산자임
		println("숫자로만 입력해주세요.");
		check = -1;
	}
	catch (out_of_range& e) {
		println("범위를 벗어났습니다.");
		check = -1;
	}


	return check;
}


//번호 겹치는거 확인 함수
bool check_exist_num(Node* node, string qu) {
	while (node != nullptr) {
		if (node->phone_num == qu) {
			return true;
		}

		node = node->address;
	}


	return false;
}


//현재 주소에 값넣기 함수
Node* value_input(Node* curr, s_s* si) {
	curr->name = si->name;
	curr->phone_num = si->phone_num;
	if (si->phone_num == "") {
		curr->phone_num = "None";
	}

	return curr;
}