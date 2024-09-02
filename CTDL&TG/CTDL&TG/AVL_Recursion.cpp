#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* left, * right;
	int height;
};

Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->left = p->right = NULL;
	p->height = 1;
	return p;
}

void initAVLTree(Node*& root) {
	root = NULL;
}

int height(Node* node) {
	if (node != NULL)
		return node->height;
	return 0;
}

void updateHeight(Node* node) {
	if (node != NULL) {
		node->height = 1 + max(height(node->left), height(node->right));
	}
}

int checkBalance(Node* node) {
	return height(node->left) - height(node->right);
}

void rotateLeft(Node*& node) {
	Node* p = node->right;
	node->right = p->left;
	p->left = node;
	updateHeight(node);
	node = p;
	updateHeight(node);
}

void rotateRight(Node*& node) {
	Node* p = node->left;
	node -> left = p->right;
	p->right = node;
	updateHeight(node);
	node = p;
	updateHeight(node);
}

void insert(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else if (root->info > x)
		insert(root->left, x);
	else if (root->info < x)
		insert(root->right, x);
	else if (root->info == x)
		return;
	updateHeight(root);
	int blc = checkBalance(root);
	if (blc > 1) {
		if (checkBalance(root->left) < -1) {
			rotateLeft(root->left);
			rotateRight(root);
		}
		else {
			rotateRight(root);
		}
	}
	else if (blc < -1) {
		if (checkBalance(root->right) > 1) {
			rotateRight(root->right);
			rotateLeft(root);
		}
		else {
			rotateLeft(root);
		}
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

void searchStandFor(Node*& p, Node*& q) {
	if (q->left == NULL) {
		p->info = q->info;
		p = q;
		q = q->right;
	}
	else
		searchStandFor(p, q->left);
}

void del(Node*& root, int key) {
	if (root == NULL)
		return;
	else if (root->info == key) {
		Node* p = root;
		if (root->left == NULL)
			root = root->right;
		else if (root->right == NULL)
			root = root->left;
		else searchStandFor(p, root->right);
		delete p;
		return;
	}
	else if (root->info > key)
		del(root->left, key);
	else if (root->info < key)
		del(root->right, key);
	updateHeight(root);
	int blc = checkBalance(root);
	if (blc > 1) {
		if (checkBalance(root->left) < -1) {
			rotateLeft(root->left);
			rotateRight(root);
		}
		else {
			rotateRight(root);
		}
	}
	else if (blc < -1) {
		if (checkBalance(root->right) > 1) {
			rotateRight(root->right);
			rotateLeft(root);
		}
		else {
			rotateLeft(root);
		}
	}
}

void NLR(Node* root) {
	if (root != NULL) {
		cout << root->info << "(" << root->height << ")" << " ";
		NLR(root->left);
		NLR(root->right);
	}
}

int countNode(Node* root) {
	if (root != NULL)
		return 1 + countNode(root->left) + countNode(root->right);
	return 0;
}

void printK(Node* root, int K, int k=0) {
	if (root != NULL) {
		k += 1;
		printK(root->left, K, k);
		if (k == K) {
			cout << root->info << "(" << root->height << ") ";
		}
		printK(root->right, K, k);
	}
}

int main() {
	Node* root;
	initAVLTree(root);
	insert(root, 10);
	insert(root, 5);
	insert(root, 15);
	insert(root, 3);
	insert(root, 20);
	//del(root, 10);
	cout << "So luong node trong cay AVL: " << countNode(root) << endl;
	NLR(root);
	system("pause");
	return 0;
}