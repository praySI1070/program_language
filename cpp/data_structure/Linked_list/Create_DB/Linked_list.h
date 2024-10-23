#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include <fstream>

#define txt_adr "data.txt"


//링크드 리스트 구조체
typedef struct Linked {
	int count = 0;
	string name = "";
	string phone_num = "";
	struct Linked* address = nullptr;
}Node;


//문자열 받는 구조체
typedef struct sl_str {
	string name;
	string phone_num;
}s_s;

//test함수
void test();

// 줄긋기 함수
void Line();

//문자열 자르기 함수
s_s* str_slice(string data);

//문자열 숫자 변환 오류 함수
int error_num(string qu);

//번호 겹치는거 확인 함수
bool check_exist_num(Node* node, string qu);

//현재 주소에 값넣기 함수
Node* value_input(Node* curr, s_s* si);

Node* start_read_node(Node* node);

void exit_write_node(Node* node);

#endif // LINKED_LIST_H