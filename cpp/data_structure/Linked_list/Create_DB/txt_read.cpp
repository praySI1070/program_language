#include "printT.h"
#include "Linked_list.h"

void ensure_file_exists(const string& filename) {
	// 파일이 존재하지 않으면 생성
	ofstream file(filename, ios::app); // ios::app 플래그로 추가 모드로 열기
	if (!file) {
		cerr << "파일 생성 실패!" << endl;
		exit(1);
	}
}

Node* start_read_node(Node* node) {
	string line = "";
	s_s* si = nullptr;
	int count = 1;
	Node* pre = node;
	Node* curr = nullptr;

	ensure_file_exists("data.txt");

	ifstream file("data.txt");	//파일열기, 없으면 생성
	if (file.is_open()) {
		while (getline(file, line)) {
			si = str_slice(line);
			if (node == nullptr) {
				node = new Node;
				node->count = count;
				node->name = si->name;
				node->phone_num = si->phone_num;
				if (node->phone_num == "None") {
					node->phone_num = "Null";
				}
				pre = node;
			}
			else {
				curr = new Node;
				pre->address = curr;
				curr->count = count;
				curr->name = si->name;
				curr->phone_num = si->phone_num;
				if (node->phone_num == "None") {
					node->phone_num = "Null";
				}
				pre = curr;
			}
			count++;
		}
		file.close();
	}
	else {
		println("파일을 못열음");
		exit(1);
	}

	return node;
}


void exit_write_node(Node* node) {
	Node* next = nullptr;
	string line;
	ofstream file("data.txt");
	if (file.is_open()) {
		while (node != nullptr) {
			if (node->phone_num == "NULL") {
				node->phone_num = "None";
			}
			file << node->name << ',' << node->phone_num << endl;
			next = node;
			node = node->address;
			delete next;
		}
		file.close();
		println("파일저장 완료");
	}
	else {
		println("파일열기 에러");
		exit(1);
	}


	return;
}


////종료 시에 delete함수
//void delete_node(Node* node) {
//	Node* next = nullptr;
//
//	while (node != nullptr) {
//
//		next = node->address;
//
//		delete node;
//
//		node = next;
//	}
//
//	return;
//}