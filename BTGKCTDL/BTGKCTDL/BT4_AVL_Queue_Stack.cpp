#include <iostream>
#include <Windows.h>
#define MAX 100
#define MAXQ 100
using namespace std;

struct Node {
	int data;
	Node* left, * right;
	int height;
};

Node* createNode(int x) {
	Node* p = new Node;
	p->data = x;
	p->left = p->right = NULL;
	p->height = 1;
	return p;
}

struct AVLTree {
	Node* root;
};

void initAVLTree(AVLTree& t) {
	t.root = NULL;
}

int getHeight(Node* node) {
	if (node != NULL)
		return 1 + max(getHeight(node->left), getHeight(node->right));
	return 0;
}

void updateHeight(Node*& root) {
	if (root == NULL)
		return;
	updateHeight(root->left);
	updateHeight(root->right);
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

int checkBalance(Node* root) {
	if (root != NULL)
		return getHeight(root->left) - getHeight(root->right);
	return 0;
}

void rotateLeft(Node*& node) {
	Node* p = node;
	node = node->right;
	p->right = node->left;
	node->left = p;
	p->height = 1 + max(getHeight(p->left), getHeight(p->right));
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

void rotateRight(Node*& node) {
	Node* p = node;
	node = node->left;
	p->left = node->right;
	node->right = p;
	p->height = 1 + max(getHeight(p->left), getHeight(p->right));
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

void insert(AVLTree& t, int x) {
	if (t.root == NULL)
		t.root = createNode(x);
	else {
		Node* p = t.root, * pre = NULL;
		while (p != NULL) {
			pre = p;
			if (p->data == x)
				return;
			else if (p->data > x)
				p = p->left;
			else
				p = p->right;
		}
		p = createNode(x);
		if (pre->data > x)
			pre->left = p;
		else
			pre->right = p;
	}
	updateHeight(t.root);
	int index = checkBalance(t.root);
	if (index > 1) {
		if (checkBalance(t.root->left) < -1)
			rotateLeft(t.root->left);
		rotateRight(t.root);
		updateHeight(t.root);
	}
	else if (index < -1) {
		if (checkBalance(t.root->right) > 1)
			rotateRight(t.root->right);
		rotateLeft(t.root);
		updateHeight(t.root);
	}
}

void recursiveInsert(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else if (root->data == x)
		return;
	else if (root->data > x)
		recursiveInsert(root->left, x);
	else if (root->data < x)
		recursiveInsert(root->right, x);
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	int index = checkBalance(root);
	if (index > 1) {
		if (checkBalance(root->left) < -1) {
			rotateLeft(root->left);
		}
		rotateRight(root);
	}
	else if (index < -1) {
		if (checkBalance(root->right) > 1) {
			rotateRight(root->right);
		}
		rotateLeft(root);
	}
}

void del(AVLTree& t, int key) {
	Node* p = t.root, * pre = NULL;
	while (p != NULL && p->data != key) {
		pre = p;
		if (p->data > key)
			p = p->left;
		else
			p = p->right;
	}
	if (p != NULL) {
		if (p->left == NULL) {
			if (pre == NULL)
				t.root = t.root->right;
			else {
				if (pre->data > key)
					pre->left = p->right;
				else
					pre->right = p->right;
			}
			delete p;
		}
		else if (p->right == NULL) {
			if (pre == NULL)
				t.root = t.root->left;
			else {
				if (pre->data > key)
					pre->left = p->left;
				else
					pre->right = p->left;
			}
			delete p;
		}
		else {
			Node* q = p->right, * pre = NULL;
			while (q->left != NULL) {
				pre = q;
				q = q->left;
			}
			p->data = q->data;
			if (pre != NULL)
				pre->left = q->right;
			else
				p->right = q->right;
			delete q;
		}
	}
	updateHeight(t.root);
	int index = checkBalance(t.root);
	if (index > 1) {
		if (checkBalance(t.root->left) < -1)
			rotateLeft(t.root->left);
		rotateRight(t.root);
		updateHeight(t.root);
	}
	else if (index < -1) {
		if (checkBalance(t.root->right) > 1)
			rotateRight(t.root->right);
		rotateLeft(t.root);
		updateHeight(t.root);
	}
}

void LNR(Node* root) {
	if (root == NULL)
		return;
	LNR(root->left);
	cout << root->data << "(" << root->height << ") | ";
	LNR(root->right);
}

void NLR(Node* root) {
	if (root == NULL)
		return;
	cout << root->data << "(" << root->height << ") | ";
	NLR(root->left);
	NLR(root->right);
}

void LRN(Node* root) {
	if (root == NULL)
		return;
	LRN(root->left);
	LRN(root->right);
	cout << root->data << "(" << root->height << ") | ";
}

struct Stack {
	Node* a[MAX];
	int top;
};
void initS(Stack& s) {
	s.top = -1;
}

bool isSEmpty(Stack s) {
	return s.top == -1;
}

void push(Stack& s, Node* node) {
	if (s.top < MAX)
		s.a[++s.top] = node;
}

Node* pop(Stack& s) {
	if (!isSEmpty(s))
		return s.a[s.top--];
}

void nonRecursiveLNR(AVLTree t) {
	Stack s;
	initS(s);
	Node* p = t.root;
	while (!isSEmpty(s) || p != NULL) {
		while (p != NULL) {
			push(s, p);
			p = p->left;
		}
		p = pop(s);
		cout << p->data << "(" << p->height << ") | ";
		p = p->right;
	}
}

void nonRecursiveNLR(AVLTree t) {
	Stack s;
	initS(s);
	Node* p = t.root;
	while (!isSEmpty(s) || p != NULL) {
		while (p != NULL) {
			cout << p->data << "(" << p->height << ") | ";
			push(s, p);
			p = p->left;
		}
		p = pop(s);
		p = p->right;
	}
}

void nonRecursiveLRN(AVLTree t) {
	Stack s;
	initS(s);
	Node* p = t.root, * lastVisited = NULL;
	while (!isSEmpty(s) || p != NULL) {
		while (p != NULL) {
			push(s, p);
			p = p->left;
		}
		p = pop(s);
		if (p->right != NULL && lastVisited != p->right) {
			push(s, p);
			p = p->right;
		}
		else {
			cout << p->data << "(" << p->height << ") | ";
			lastVisited = p;
			p = NULL;
		}
	}
}

struct LLQueue {
	Node* data;
	LLQueue* next;
};

LLQueue* createNode(Node* node) {
	LLQueue* p = new LLQueue;
	p->data = node;
	p->next = NULL;
	return p;
}

void initLLQueue(LLQueue*& q) {
	q = NULL;
}

bool isLLQEmpty(LLQueue* q) {
	return q == NULL;
}

void enLLQueue(LLQueue*& q, Node* node) {
	if (q == NULL)
		q = createNode(node);
	else {
		LLQueue* p = q;
		while (p->next != NULL)
			p = p->next;
		p->next = createNode(node);
	}
}

Node* deLLQueue(LLQueue*& q) {
	if (q != NULL) {
		Node* p = q->data;
		q = q->next;
		return p;
	}
	return NULL;
}

void BFSWLKQueue(AVLTree& t) {
	Node* p = t.root;
	LLQueue* q;
	initLLQueue(q);
	enLLQueue(q, p);
	while (!isLLQEmpty(q)) {
		p = deLLQueue(q);
		cout << p->data << "(" << p->height << ") | ";
		if (p->left != NULL)
			enLLQueue(q, p->left);
		if (p->right != NULL)
			enLLQueue(q, p->right);
	}
}
//Phuong phap tinh tien
//struct Queue {
//	Node* a[MAX];
//	int front, rear;
//};
//
//bool isQEmpty(Queue q) {
//	return q.front == -1;
//}
//
//bool isQFull(Queue q) {
//	return q.rear - q.front == MAXQ;
//}
//
//void initQueue(Queue& q) {
//	q.front = q.rear = -1;
//}
//
//void enQueue(Queue& q, Node* node) {
//	if (isQFull(q))
//		return;
//	if (!isQEmpty(q)) {
//		q.front = q.rear = 0;
//		q.a[q.front] = node;
//	}
//	else {
//		if (q.rear == MAX - 1) {
//			for (int i = q.front; i <= q.rear; i++) {
//				q.a[i - q.front] = q.a[i];
//			}
//			q.rear -= q.front;
//			q.front = 0;
//		}
//		q.a[++q.rear] = node;
//	}
//}
//
//
//Node* deQueue(Queue& q) {
//	if (!isQEmpty(q) && q.front <= q.rear)
//		return q.a[q.front++];
//	return NULL;
//}

//Phuong phap vong
struct Queue {
	Node* a[MAXQ];
	int front, rear, size;
};

void initQueue(Queue& q) {
	q.front = q.rear = -1;
	q.size = 0;
}

bool isQFull(Queue q) {
	return q.size == MAXQ;
}

bool isQEmpty(Queue q) {
	return q.front == -1;
}

void enQueue(Queue& q, Node* node) {
	if (isQFull(q))
		return;
	if (!isQEmpty(q))
		q.front = 0;
	q.rear = (q.rear + 1) % MAXQ;
	q.a[q.rear] = node;
	q.size++;
}

Node* deQueue(Queue& q) {
	if (isQEmpty(q))
		return NULL;
	Node* p = q.a[q.front];
	q.front = (q.front + 1) % MAX;
	q.size--;
	if (q.size == 0)
		q.front = q.rear = -1;
}

void printK(Node* root, int K, int k=0) {
	if (root != NULL) {
		k++;
		printK(root->left, K, k);
		if(K==k)
			cout << root->data << "(" << root->height << ") | ";
		printK(root->right, K, k);
	}
}

int main() {
	AVLTree t;
	initAVLTree(t);
	recursiveInsert(t.root, 15);
	recursiveInsert(t.root, 10);
	recursiveInsert(t.root, 5);
	recursiveInsert(t.root, 6);
	recursiveInsert(t.root, 7);
	NLR(t.root);
	cout << endl;
	printK(t.root, 2);
	system("pause");
	return 0;
}