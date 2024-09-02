#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* left;
	Node* right;
};

Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->left = p->right = NULL;
	return p;
}

void initBTree(Node*& root) {
	root = NULL;
}

void recursiveInsert(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else {
		if (root->info == x)
			return;
		else if (root->info > x)
			recursiveInsert(root->left, x);
		else
			recursiveInsert(root->right, x);
	}
}

void insert(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else {
		Node* p = root, *pre = root;
		while (p != NULL) {
			pre = p;
			if (p->info == x)
				return;
			else if (p->info > x)
				p = p->left;
			else
				p = p->right;
		}
		p = createNode(x);
		if (pre->info > x)
			pre->left = p;
		else
			pre->right = p;
	}
}

void LNR(Node* root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->info<<" ";
		LNR(root->right);
	}
}

void LRN(Node* root) {
	if (root != NULL) {
		LRN(root->left);
		LRN(root->right);
		cout << root->info<<" ";
	}
}

void NLR(Node* root) {
	if (root != NULL) {
		cout << root->info << " ";
		NLR(root->left);
		NLR(root->right);
	}
}

Node* search(Node* root, int key) {
	Node* p = root;
	while (p != NULL) {
		if (p->info == key)
			return p;
		else if (p->info > key)
			p = p->left;
		else
			p = p->right;
	}
	return p;
}

void del(Node*& root, int key) {
	if (root != NULL) {
		Node* p = root, * pre = root;
		while (p != NULL) {
			if (p->info == key)
				break;
			else {
				pre = p;
				if (p->info > key)
					p = p->left;
				else
					p = p->right;	
			}
		}
		if (p != NULL) {
			if (p->left == NULL || p->right == NULL) {
				if (pre->info > key)
					pre->left = p->left;
				else
					pre->right = p->right;
				if (p == root)
					root = NULL;
				delete p;
			}
			else {
				Node* q = p->left;
				while (q->right != NULL)
					q = q->right;
				p->info = q->info;
				if (q->left != NULL)
					p->left = q->left;
				delete q;
			}
		}
	}
}

void searchStandFor(Node*& p, Node*& q){
	if (q->left == NULL)
	{
		p->info == q->info;
		p = q;
		q = q->right;
	}
	else
		searchStandFor(p, q->left);
}

int Delete(Node*& T, int x)
{
	if (T == NULL) return 0;
	if (T->info == x)
	{
		Node* p = T;
		if (T->left == NULL) T = T->right;
		else if (T->right == NULL) T = T->left;
		else // có 2 con
			searchStandFor(p, T->right);
		delete p;
		return 1;
	}
	if (T->info < x) return Delete(T->right, x);
	if (T->info > x) return Delete(T->left, x);
}

int main() {
	Node* root;
	initBTree(root);
	recursiveInsert(root, 6);
	insert(root, 3);
	insert(root, 1);
	insert(root, 2);
	recursiveInsert(root, 12);
	insert(root, 9);
	insert(root, 13);
	insert(root, 8);
	LNR(root);
	cout << endl;
	Delete(root, 9);
	LNR(root);
	cout << endl;
	if (search(root, 7) != NULL) cout << "Tim thay!\n";
	else cout << "Khong tim thay!\n";
	system("pause");
	return 1;
}