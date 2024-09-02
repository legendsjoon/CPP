#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* next;
};
void init(Node*& head) {
	head = NULL;
}

void printList(Node* head) {
	Node* p = head;
	if (p != NULL) {
		do {
			cout << p->info << " ";
			p = p->next;
		} while (p!= head);
	}
}

Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

void insertFirst(Node*& head, int x) {
	Node* p = createNode(x);
	if (head == NULL) {
		head = p;
		head->next = head;
	}
	else {
		p->next = head;
		Node* last = head;
		while (last->next != head){
				last = last->next;
			};
		last->next = p;
		head = p;
	}
}

void delFirst(Node*& head) {
	Node* p = head;
	if (p != NULL) {
		Node* last = head;
		while (last->next != head) {
			last = last->next;
		}
		if (p != last) {
			head = head->next;
			delete p;
			last->next = head;
		}
		else {
			delete head;
			head = NULL;
		}
	}
}

void insertLast(Node*& head, int x) {
	Node* p = createNode(x);
	if (head == NULL) {
		head = p;
		head->next = head;
	}
	else {
		Node* last = head;
		while (last->next != head) {
			last = last->next;
		};
		last->next = p;
		p->next =head;
	}
}

void delLast(Node*& head) {
	Node* p = head;
	if (p != NULL) {
		Node* last = head;
		Node* prelast = head;
		while (last->next != head) {
			prelast = last;
			last = last->next;
		}
		if (p != last) {
			prelast->next = head;
			delete last;
			last = NULL;
		}
		else {
			delete head;
			head = NULL;
		}
	}
}

Node* findNode(Node* head,int x) {
	Node* p = head;
	if (p != NULL) {
		do {
			if (p->info == x)
				return p;
			p = p->next;
		} while (p != head);
	}
	return NULL;
}

void delFoundNode(Node*& head, int x) {
	Node* p = findNode(head, x);
	if (p != NULL) {
		if (p == head)
			delFirst(head);
		else {
			Node* q = head;
			while (q->next != p)
				q = q->next;
			q->next = p->next;
			delete p;
		}
	}
	else cout << "Khong tim thay " << x << " trong danh sach!\n";
}

void destroyList(Node*& head) {
	while (head != NULL) {
		delFirst(head);
	}
}

int main() {
	Node* head;
	init(head);
	insertLast(head, 8);
	insertFirst(head, 9);
	insertFirst(head, 10);
	insertLast(head, 7);
	//delFirst(head);
	//delLast(head);
	delFoundNode(head, 7);
	printList(head);
	destroyList(head);
	system("pause");
	return 1;
}
