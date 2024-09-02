#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* next;
	Node* prev;
};

struct DSLKK {
	Node* head, * tail;
};

void init(DSLKK &ds) {
	ds.head = NULL;
	ds.tail = NULL;
}

void printList(DSLKK ds) {
	Node* p = ds.head;
	while (p != NULL) {
		cout << p->info << " ";
		p = p->next;
	}
}

Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	p->prev = NULL;
	return p;
}

void insertFirst(DSLKK &ds, int x) {
	Node* p = createNode(x);
	if (ds.head == NULL) {
		ds.head = ds.tail = p;
	}
	else {
		ds.head->prev = p;
		p->next = ds.head;
		ds.head = p;
	}
}

void insertLast(DSLKK& ds, int x) {
	Node* p = createNode(x);
	if (ds.head == NULL) {
		ds.head = ds.tail = p;
	}
	else {
		ds.tail->next = p;
		p->prev = ds.tail;
		ds.tail = p;
	}
}

void delFirst(DSLKK& ds) {
	if (ds.head != NULL) {
		if (ds.head == ds.tail) {
			delete ds.head;
			init(ds);
		}
		else {
			Node* p = ds.head;
			ds.head = ds.head->next;
			ds.head->prev = NULL;
			delete p;
		}
	}
}

void delLast(DSLKK& ds) {
	if (ds.head != NULL) {
		if (ds.head == ds.tail) {
			delete ds.head;
			init(ds);
		}
		else {
			Node* p = ds.tail;
			ds.tail = ds.tail->prev;
			ds.tail->next = NULL;
			delete p;
		}
	}
}
//Xoa phan tu theo tim kiem
Node* find(DSLKK ds, int x) {
	Node* p = ds.head;
	while (p != NULL) {
		if (p->info == x) return p;
		p = p->next;
	}
	return NULL;
}

void deleteNode(DSLKK& ds, int x) {
	Node* p = find(ds, x);
	if (p == NULL) {
		cout << "Khong tim thay " << x << " trong danh sach!\n";
	}
	else {
		if (p == ds.head)
			delFirst(ds);
		else if (p == ds.tail) {
			delLast(ds);
		}
		else {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
		}
	}
}

//Tim kiem gan dung
Node* approxfind(DSLKK ds, int x) {
	Node* p = ds.head, * target = ds.head;
	int min=INT_MAX;
	while (p != NULL) {
		if (p->info>=x) {
			if (min > (p->info - x)) {
				target = p;
				min = p->info - x;
			}
		}
		p = p->next;
	}
	return target;
}

void insertNode(DSLKK& ds, int x, int y) {
	Node* p = approxfind(ds, y);
	if (p == NULL) {
		cout << "Danh sach trong!\n";
	}
	else {
		if (ds.tail == ds.head)
			insertFirst(ds, x);
		else{
			Node* temp = createNode(x);
			temp->next = p;
			temp->prev = p->prev;
			p->prev = temp;
			temp->prev->next = temp;
		}
	}
}

void destroyList(DSLKK& ds) {
	while (ds.head != NULL) {
		delFirst(ds);
	}
}

int main() {
	DSLKK ds;
	init(ds);
	insertLast(ds, 9);
	insertFirst(ds, 1);
	insertLast(ds, 30);
	insertLast(ds, 40);
	//delFirst(ds);
	//delLast(ds);
	//deleteNode(ds, 8);
	insertNode(ds, 10, 8);
	printList(ds);
	destroyList(ds);
	system("pause");
	return 0;
}