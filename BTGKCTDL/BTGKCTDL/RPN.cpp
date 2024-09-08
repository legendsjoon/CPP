#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
#define MAX 100

struct Stack {
	char* a[MAX];
	int top;
};

void init(Stack& s) {
	s.top = -1;
}

bool isEmpty(Stack s) {
	return s.top == -1;
}

void push(Stack& s, char* x) {
	if (s.top < MAX) {
		s.a[++s.top] = x;
	}
}

const char* peek(Stack& s) {
	if (isEmpty(s))
		return "";
	return s.a[s.top];
}

const char* pop(Stack& s) {
	if (isEmpty(s))
		return "";
	return s.a[s.top--];
}

struct Node {
	const char* data;
	Node* next;
};

Node* createNode(const char* x) {
	Node* p = new Node;
	p->data = x;
	p->next = NULL;
	return p;
}

struct Queue {
	Node* head;
};

void init(Queue& q) {
	q.head = NULL;
}

bool isEmpty(Queue q) {
	return q.head == NULL;
}

void enQueue(Queue& q, const char* x) {
	if (isEmpty(q))
		q.head = createNode(x);
	else {
		Node* p = q.head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = createNode(x);
	}
}

const char* deQueue(Queue& q) {
	if (isEmpty(q))
		return "";
	const char* p = q.head->data;
	Node* temp = q.head;
	q.head = q.head->next;
	delete temp;
	return p;
}

struct NumberStack {
	int a[MAX];
	int top;
};

void init(NumberStack &ns) {
	ns.top = -1;
}

bool isEmpty(NumberStack ns) {
	return ns.top == -1;
}

void push(NumberStack& ns, int x) {
	if (ns.top < MAX)
		ns.a[++ns.top] = x;
}

int pop(NumberStack& ns) {
	if (!isEmpty(ns))
		return ns.a[ns.top--];
	return 0;
}

int calculate(int a, int b, string op) {
	if (op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if (op == "*")
		return a * b;
	if (op == "/")
		return a / b;
}

void evaluateRPN(Queue& q) {
	NumberStack ns;
	init(ns);
	while (!isEmpty(q)) {
		const char* p = deQueue(q);
		if (isdigit(*p))
			push(ns, atoi(p));
		else {
			int b = pop(ns);
			int a = pop(ns);
			push(ns, calculate(a, b, p));
		}
	}
	cout << "KET QUA: " << pop(ns) << endl;
}

int getPriority(string op) {
	if (op == "*" || op == "/")
		return 2;
	if (op == "+" || op == "-")
		return 1;
	return 0;
}

void infixToPostfix(char x[]) {
	Stack s;
	init(s);
	Queue q;
	init(q);
	char* p = strtok(x, " ");
	while (p != NULL) {
		if (isdigit(*p))
			enQueue(q, p);
		else if (*p == '(')
			push(s, p);
		else if (*p == ')') {
			const char* op = pop(s);
			while ((string)op != "(") {
				enQueue(q, op);
				op = pop(s);
			}
		}
		else {
			while (!isEmpty(s) && getPriority(p) <= getPriority(peek(s))) {
				const char* op = pop(s);
				enQueue(q, op);
			}
			push(s, p);
		}
		p = strtok(NULL, " ");
	}
	while (!isEmpty(s))
		enQueue(q, pop(s));
	/*Xuat ket qua*/
	//while (!isEmpty(q))
	//	cout << deQueue(q) << " ";
	evaluateRPN(q);
}

int main() {
	char str[] = "2 + 4 - ( 5 - 3 ) / 2 + 3 - 1 * 5";
	infixToPostfix(str);
	system("pause");
	return 0;
}