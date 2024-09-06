#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* left, * right;
};

Node* createNode(int x){
	Node* p = new Node;
	p->data = x;
	p->left = p->right = NULL;
	return p;
}

void initBinaryTree(Node*& root) {
	root = NULL;
}

void insert(Node *&root, int x) {
	if (root == NULL)
		root = createNode(x);
	else {
		Node* p = root, *pre = root;
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

void del(Node*& root, int key) {
	if (root != NULL) {
		Node* p = root, * pre = root;
		while (p != NULL && p->data!=key) {
			pre = p;
			if (p->data > key)
				p = p->left;
			else
				p = p->right;
		}
		if (p != NULL) {
			if (p->left != NULL && p->right != NULL) {

			}
			else if (p->left != NULL) {
				pre
			}
			else if (p->right != NULL) {

			}
		}
	}
}

bool search(Node* root, int key) {
	if (root != NULL){
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

void LNR(Node *root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->data << " ";
		LNR(root->right);
	}
}

int main() {
	Node * t;
	initBinaryTree(t);
	insert(t, 1);
	insert(t, 2);
	insert(t, 3);
	insert(t, 4);
	insert(t, 5);
	LNR(t);
	//if (search(t, 1)) cout << "Tim thay!\n";
	system("pause");
	return 0;
}