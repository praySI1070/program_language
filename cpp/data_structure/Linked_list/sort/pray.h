#include <iostream>
#include <string>

#define println(data) \
	cout << data << endl;
#define print(data) \
	cout << data
#define printT(data) \
	cout << data << '\t';

#define input(data,message) \
	cout << message << '\t' << flush;\
	cin >> data; \
	cout << endl;

using namespace std;



typedef struct Node {
	string name = "";
	int x = 0;
	int y = 0;
	double distance = 0;
	Node* pre = nullptr;
	Node* post = nullptr;
}Node;


Node* swap(Node* node, int a, int b, int len_node);

void print_name(Node* node, int count);

int len_no(Node* node);

Node* serach_node(Node* node, int count);

int exit_Linked(Node* node,int count);

void Line();

double cal_distance(Node* node);

Node* sort_linked(Node* node, int count);

void print_node(Node* pre, int count);

Node* insert(Node* node, int a, int b, int len_node);