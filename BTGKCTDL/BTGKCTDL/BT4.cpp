#include <iostream>
using namespace std;
#define MAX 100

struct Node {
	int data;
	Node* left, * right;
};

Node* createNode(int x) {
	Node* p = new Node;
	p->data = x;
	p->left = p->right = NULL;
	return p;
}

struct Stack {
	Node* a[MAX];
	int top;
};

void initStack(Stack& s) {
	s.top = -1;
}

void push(Stack& s, Node* x) {
	if (s.top < MAX)
		s.a[++s.top] = x;
}

bool isStackEmpty(Stack s) {
	return s.top == -1;
}

Node* top(Stack s) {
	if (!isStackEmpty(s))
		return s.a[s.top];
	return NULL;
}

Node* pop(Stack& s) {
	if (!isStackEmpty(s))
		return s.a[s.top--];
	return NULL;
}

void initBinaryTree(Node*& root) {
	root = NULL;
}

void insert(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else {
		Node* p = root, * pre = root;
		while (p != NULL) {
			pre = p;
			if (p->data == x)
				return;
			else if (p->data > x)
				p = p->left;
			else if (p->data < x)
				p = p->right;
		}
		p = createNode(x);
		if (pre->data > x)
			pre->left = p;
		else
			pre->right = p;
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
}

void del(Node*& root, int key) {
	if (root != NULL) {
		Node* p = root, * pre = root;
		while (p != NULL && p->data != key) {
			pre = p;
			if (p->data > key)
				p = p->left;
			else
				p = p->right;
		}
		if (p != NULL) {
			if (p->left == NULL || p->right == NULL) {
				if (p == root) {
					if (p->left != NULL)
						root = p->left;
					else if (p->right != NULL)
						root = p->right;
					else
						root = NULL;
				}
				else {
					if (pre->data > key)
						pre->left = p->left;
					else
						pre->right = p->right;

				}
				delete p;

			}
			else {
				Node* q = p->right, * preq = p->right;
				while (q->left != NULL) {
					preq = q;
					q = q->left;
				}
				p->data = q->data;
				if (q == preq) {
					p->right = q->right;
				}
				else {
					preq->left = q->right;
				}
				delete q;
			}
		}
	}
}



void searchStandForNoRecursion(Node*& p, Node*& q) {
	Node* pre = NULL;
	Node* temp = q;
	while (temp->left != NULL) {
		pre = temp;
		temp = temp->left;
	}
	p->data = temp->data;
	p = temp;
	if (pre == NULL)
		q = q->right;
	else
		pre->left = temp->right;
}

void searchStandFor(Node*& p, Node*& q) {
	if (q->left == NULL) {
		p->data = q->data;
		p = q;
		q = q->right;
	}
	else {
		searchStandFor(p, q->left);
	}
}

void recursiveDel(Node*& root, int key) {
	if (root == NULL)
		return;
	else if (root->data == key) {
		Node *p = root;
		if (root->left == NULL) {
			root = root->right;
		}
		else if (root->right == NULL)
			root = root->left;
		else {
			searchStandFor(p, root->right);
		}
		delete p;
	}
	else if (root->data > key)
		recursiveDel(root->left, key);
	else if (root->data < key)
		recursiveDel(root->right, key);
}

bool search(Node* root, int key) {
	if (root != NULL) {
		Node* p = root;
		while (p != NULL) {
			if (p->data == key)
				return true;
			if (p->data > key)
				p = p->left;
			else
				p = p->right;
		}
	}
	return false;
}

void LNR(Node* root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->data << " ";
		LNR(root->right);
	}
}

void LRN(Node* root) {
	if (root != NULL) {
		LRN(root->left);
		LRN(root->right);
		cout << root->data << " ";
	}
}

void NLR(Node* root) {
	if (root != NULL) {
		cout << root->data << " ";
		NLR(root->left);
		NLR(root->right);
	}
}

bool isPrimeNumber(int x) {
	if (x < 2)
		return false;
	for (int i = 2; i <= sqrt(x); i++) {
		if (x % i == 0)
			return false;
	}
	return true;
}

int countNode(Node* root) {
	if (root == NULL)
		return 0;
	return 1 + countNode(root->left) + countNode(root->right);

}

void countNodeTailRecursion(Node* root, int& count) {
	if (root == NULL)
		return;
	count++;
	countNodeTailRecursion(root->left,count);
	countNodeTailRecursion(root->right,count);
}

int countPrimeNode(Node* root) {
	if (root == NULL)
		return 0;
	if (isPrimeNumber(root->data))
		return 1 + countPrimeNode(root->left) + countPrimeNode(root->right);
	else
		return countPrimeNode(root->left) + countPrimeNode(root->right);
}

void countPrimeNodeTailRecursion(Node* root, int &count) {
	if (root == NULL)
		return;
	if (isPrimeNumber(root->data))
		count++;
	countPrimeNodeTailRecursion(root->left, count);
	countPrimeNodeTailRecursion(root->right, count);
}

void LNRNoRecursion(Node* root) {
	if (root != NULL) {
		Node* p = root;
		Stack s;
		initStack(s);
		while (!isStackEmpty(s) || p != NULL) {
			while (p != NULL) {
				push(s, p);
				p = p->left;
			}
			p = pop(s);
			cout << p->data << " ";
			p = p->right;
		}
	}
}

void NLRNoRecursion(Node* root) {
	if (root != NULL) {
		Node* p = root;
		Stack s;
		initStack(s);
		while (!isStackEmpty(s) || p != NULL) {
			while (p != NULL) {
				cout << p->data << " ";
				push(s, p);
				p = p->left;
			}
			p = pop(s);
			p = p->right;
		}
	}
}

void LRNNoRecursion(Node* root) {
	if (root != NULL) {
		Node* p = root, * lastVisited = NULL;
		Stack s;
		initStack(s);
		while (!isStackEmpty(s) || p != NULL) {
			while (p != NULL) {
				push(s, p);
				p = p->left;
			}
			p = pop(s);
			if (p->right != NULL && p->right != lastVisited) {
				push(s, p);
				p = p->right;
			}
			else {
				cout << p->data << " ";
				lastVisited = p;
				p = NULL;
			}
		}
	}
}

struct LLQueue {
	Node* data;
	LLQueue* next;
};

LLQueue* createNode2(Node* data) {
	LLQueue* p = new LLQueue;
	p->data = data;
	p->next = NULL;
	return p;
}

struct Queue {
	LLQueue* head;
};

void initQueue(Queue& q) {
	q.head = NULL;
}

bool isQueueEmpty(Queue q) {
	return q.head == NULL;
}

void enQueue(Queue& q, Node* data) {
	if (isQueueEmpty(q))
		q.head = createNode2(data);
	else {
		LLQueue* p = q.head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = createNode2(data);
	}
}

Node* deQueue(Queue& q) {
	if (isQueueEmpty(q))
		return NULL;
	Node* p = q.head->data;
	LLQueue* temp = q.head;
	q.head = q.head->next;
	delete temp;
	return p;
}

void BFS(Node* root) {
	if (root != NULL) {
		Node* p = root;
		Queue q;
		initQueue(q);
		enQueue(q, p);
		while (!isQueueEmpty(q)) {
			p = deQueue(q);
			cout << p->data << " ";
			if (p->left != NULL)
				enQueue(q, p->left);
			if (p->right != NULL)
				enQueue(q, p->right);
		}
	}
}

int main() {
	Node* t;
	initBinaryTree(t);
	recursiveInsert(t, 10);
	recursiveInsert(t, 7);
	recursiveInsert(t, 13);
	recursiveInsert(t, 14);
	recursiveInsert(t, 11);
	recursiveInsert(t, 12);
	recursiveInsert(t, 6);
	recursiveInsert(t, 8);
	recursiveInsert(t, 9);
	//cout << "So luong node: " << countNode(t) << endl;
	//int count = 0;
	//countNodeTailRecursion(t, count);
	//cout << "So luong node: " << count << endl;
	//countPrimeNodeTailRecursion(t, count);
	//cout << "So luong node nguyen to: " << count << endl;
	//cout << "So luong node nguyen to: " << countPrimeNode(t) << endl;
	//BFS(t);
	LNR(t);
	cout << endl;
	recursiveDel(t, 10);
	LNR(t);
	cout << endl;
	//LRNNoRecursion(t);
	//if (search(t, 1)) cout << "Tim thay!\n";
	system("pause");
	return 0;
}