#include "./CookHeader.h"
#include <stdio.h>
#include <fstream>
#include <sstream>

#define txt_adr "data.txt"

//using namespace std;


//링크드 리스트 구조체
typedef struct Linked {
	int count = 0;
	string name ="";
	string phone_num ="";
	struct Linked* address = nullptr;
}Node;


//문자열 받는 구조체
typedef struct sl_str{
	string name;
	string phone_num;
}s_s;


//test함수
void test() {
	println("test");
	return;
}


// 줄긋기 함수
void Line() {
	for(int i =0;i< 15;i++)
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
		default:
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
		curr->phone_num = "NULL";
	}

	return curr;
}


//뭐로 찾는지 확인하는 함수
Node* search_way(Node* node, int num) {
	Node* curr = node;
	bool curr_check = false;
	string check = "";
	int same_name = 0;

	while (num != -1) {
		switch (num)
		{
		case 21:
			input(num, "찾으려는 번호를 입력해주세요.:  ");
			while (curr != nullptr) {
				if (curr->count == num) {
					curr_check = true;
					break;
				}

				curr = curr->address;
			}


			if (!curr_check) {
				curr = nullptr;
			}
			num = -1;
			break;
		case 22:
			input(check, "찾으려는 이름을 입력해주세요.:  ");
			while (curr != nullptr) {
				if (curr->name == check) {
					same_name++;
				}


				curr = curr->address;
			}

			if (same_name > 0) {
				curr_check = true;
				curr = node;
				if (same_name == 1) {
					while (curr != nullptr) {
						if (curr->name == check) {
							break;
						}


						curr = curr->address;
					}
					num = -1;
					break;
				}
				else {
					println("이름이 겹치는 사람이 있습니다.");
					Line();
					while (curr != nullptr) {
						if (curr->name == check) {
							print(curr->count);
							print("\t");
							print(curr->name);
							print("\t");
							println(curr->phone_num);
							Line();
						}


						curr = curr->address;
					}
					curr = node;
					num = 21;
					break;
				}
			}

			if (!curr_check) {
				curr = nullptr;
			}
			break;
		case 23:
			input(check, "찾으려는 전화번호를 입력해주세요.:  ");
			while (curr != nullptr) {
				if (curr->phone_num == check) {
					curr_check = true;
					break;
				}


				curr = curr->address;
			}


			if (!curr_check) {
				curr = nullptr;
			}
			num = -1;
			break;
		default:
			println("수정함수 에서 이상한 에러발생");
			num = -1;
			break;
		}
	}



	return curr;
}


//시작 함수
int start() {
	string qu = "";
	int check = 0;

	while (true) {
		println("하고 싶은 작업을 번호로 입력하세요.");
		input(qu, "1.추가, 2.수정, 3.삽입, 4.삭제, 5.검색, 8.전부 출력 ,9.종료:  ");

		check = error_num(qu);
		if (check == -1) {
			continue;
		}
		else {
			break;
		}
	}

	return check;
}


//추가 함수
Node* add(Node* node,s_s* si) {

	if (node == nullptr) {
		node = new Node;

		node->count = 1;
		node->name = si->name;
		node->phone_num = si->phone_num;
		if (si->phone_num == "") {
			node->phone_num = "NULL";
		}

		delete si;

		return node;
	}
	else {
		Node* curr = node;
		Node* pre = curr;

		while (curr->address != nullptr) {
			curr = curr->address;
			pre = curr;
		}
		curr = new Node;
		pre->address = curr;
		
		curr = value_input(curr, si);
		curr->count = pre->count + 1;

		delete si;

		return node;
	}
}


//수정 선택 함수
int check_modify(Node* node) {
	int check = -1;
	string qu = "";

	while (check == -1) {
		input(qu, "찾을 방법을 선택해주세요. 1.번호, 2.이름, 3.휴대폰번호, 4.뒤로가기:  ");
		check = error_num(qu);
		if (check == -1) {
			continue;
		}
		else {
			check += 20;
			break;
		}
	}

	return check;
}


//수정 함수
Node* modify(Node* node, int num) {
	string check = "";
	string data = "";
	s_s* si = nullptr;
	Node* curr = node;
	bool curr_check = false;
	bool exist_num = true;
	int same_name = 0;

	curr = search_way(node,num);

	if (curr == nullptr) {
		println("찾으시는 자료가 없습니다.");
	}
	else {
		while (exist_num) {
			println("수정하려는 값을 입력해주세요.");
			input(data, "ex)전석일,010-1234-5678\n");
			si = str_slice(data);


			exist_num = check_exist_num(node,si->phone_num);

			//현재 수정하려는 자료와 번호가 같으면 통과 -> 이름만 수정
			if (si->phone_num == curr->phone_num) {
				exist_num = false;
			}

			if (exist_num) {
				println("이미 존재하는 전화번호입니다.");
			}
		}
		
		curr = value_input(curr, si);
	}

	delete si;

	return node;
}


//삽입 함수
Node* insert(Node* node,s_s* si) {
	int count = 0;
	bool exist_value = false;
	Node* curr = node;
	Node* pre = node;
	Node* tail = nullptr;

	input(count, "몇번째에 삽입할지 말해주세요.:  ");


	while (curr != nullptr) {	//count번쨰에 값이 있는지 확인
		if (curr->count == count) {
			exist_value = true;
			break;
		}

		pre = curr;
		curr = curr->address;
	}


	if (exist_value) {
		if (curr->address != nullptr) {
			tail = curr;
		}

		curr = new Node;

		if (count == 1) {
			curr->count = 1;
			curr = value_input(curr, si);
			curr->address = tail;
			node = curr;

			while (tail != nullptr) {

				tail->count = curr->count + 1;
				curr = tail;
				tail = tail->address;
			}
		}
		else {
			curr = value_input(curr, si);
			pre->address = curr;
			curr->address = tail;

			while (curr != nullptr) {
				curr->count = pre->count + 1;
				pre = curr;
				curr = curr->address;
			}
		}
	}

	return node;
}


//삭제 함수
Node* del_node(Node* node, int check) {
	Node* curr = node;
	Node* pre = node;
	Node* tail = nullptr;
	int temp = 0;
	curr = search_way(node, check);

	//curr이 head라면
	if (curr == node) {
		pre = curr;
		curr = curr->address;
		tail = curr;
		delete pre;

		while (curr != nullptr) {
			temp++;
			curr->count = temp;
			curr = curr->address;
		}

		return tail;
	}
	else {
		while (pre->address != curr) {
			pre = pre->address;
		}

		tail = curr->address;
		delete curr;
		pre->address = tail;

		temp = pre->count;
		while (tail != nullptr) {
			temp++;
			tail->count = temp;
			tail = tail->address;
		}
	}

	return node;
}


//검색 함수
void search(Node* node, int check) {
	Node* curr = node;

	curr = search_way(node, check);

	cout << "\n";
	Line();
	print(curr->count);
	print('\t');
	print(curr->name);
	print("\t");
	println(curr->phone_num);
	Line();

	return;
}


//전부 출력 함수
void all_print(Node* node) {
	cout << "\n";
	Line();
	int count = 1;

	if (node != nullptr) {
		do {
			print(node->count);
			print("\t");
			print(node->name);
			print("\t");
			println(node->phone_num);
			Line();
			node = node->address;
		} while (node != nullptr);
	}
	else {
		Line();
	}
	cout << "\n";

	return;
}


//종료 시에 delete함수
void delete_node(Node* node) {
	Node* next = nullptr;

	while (node != nullptr) {
		next = node->address;

		delete node;

		node = next;
	}

	return;
}


int main()
{
	int check= 0;

	Node* node = nullptr;
	string data = "";
	s_s* si = nullptr;
	bool exist_num = true;

	while (check != 9) {
		check = start();

		switch (check)
		{	
		case 1:	//추가
			exist_num = true;
			while (exist_num) {
				println("추가하려는 값을 입력해주세요.");
				input(data, "ex)전석일,010-1234-5678\n");
				si = str_slice(data);
				exist_num = check_exist_num(node, si->phone_num);

				if (exist_num) {
					println("이미 존재하는 전화번호입니다.");
				}
			}
			node = add(node,si);
			break;
		case 2:	//수정
			if (node == nullptr) {
				println("수정할 값이 없습니다.");
				break;
			}
			check = check_modify(node);
			if (check == 24) {
				break;
			}
			node = modify(node,check);
			break;
		case 3:	// 삽입
			exist_num = true;
			while (exist_num) {
				println("삽입하려는 값을 입력해주세요.");
				input(data, "ex)전석일,010-1234-5678\n");
				si = str_slice(data);
				exist_num = check_exist_num(node, si->phone_num);

				if (exist_num) {
					println("이미 존재하는 전화번호입니다.");
				}

			}

			node = insert(node,si);
			break;
		case 4:	// 삭제
			if (node == nullptr) {
				println("삭제할 값이 없습니다.");
				break;
			}
			check = check_modify(node);
			if (check == 24) {
				break;
			}
			node = del_node(node, check);

			break;
		case 5:	//검색
			if (node == nullptr) {
				println("검색할 값이 없습니다.");
				break;
			}
			check = check_modify(node);
			if (check == 24) {
				break;
			}
			search(node, check);

			break;
		case 8:
			all_print(node);
			break;
		case 9:	//종료
			println("종료되었습니다.");
			delete_node(node);
			break;
		default:
			println("다시 선택해주세요.");
			continue;
		}
	}


	return 0;
}