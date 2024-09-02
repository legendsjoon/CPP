#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* left;
	Node* right;
	int height;
};

Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->left = p->right = NULL;
	p->height=1;
	return p;
}


void initAVLTree(Node*& root) {
	root = NULL;
}

int height(Node* node) {
	if (node == NULL)
		return 0;
	return 1 + max(height(node->left), height(node->right));
}

void updateHeight(Node*& root) {
	if (root == NULL) return;
	updateHeight(root->left);
	updateHeight(root->right);
	root->height = 1 + max(height(root->left), height(root->right));
}

int checkBalance(Node* root) {
	int left, right;
	if (root->left == NULL)
		left = 0;
	else
		left = root->left->height;
	if (root->right == NULL)
		right = 0;
	else
		right = root->right->height;
		return left - right;

}

Node* rotateLeft(Node*& node) {
	Node* p = node->right;
	node->right = p->left;
	p->left = node;
	return p;
}

Node* rotateRight(Node*& node) {
	Node* p = node->left;
	node->left = p->right;
	p->right = node;
	return p;
}

void insert(Node*& root, int x) {
	if (root == NULL) {
		root = createNode(x);
		updateHeight(root);
	}
	else {
		Node* p = root, * pre = root;
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
		updateHeight(root);
		//lech trai
		if (checkBalance(root) > 1) {
			if (checkBalance(root->left) < -1) {
				root->left = rotateLeft(root->left);
				updateHeight(root);
				root = rotateRight(root);
				updateHeight(root);
			}
			else {
				root = rotateRight(root);
				updateHeight(root);
			}
		}
		//lech phai
		else if (checkBalance(root) < -1) {
			if (checkBalance(root->right) > 1) {
				root->right = rotateRight(root->right);
				updateHeight(root);
				root = rotateLeft(root);
				updateHeight(root);
			}
			else {
				root = rotateLeft(root);
				updateHeight(root);
			}
		}
	}
}

void LNR(Node* root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->info << " : "<<root->height<<"  ||  ";
		LNR(root->right);
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
			updateHeight(root);
			if (checkBalance(root) > 1) {
				if (checkBalance(root->left) < -1) {
					root->left = rotateLeft(root->left);
					updateHeight(root);
					root = rotateRight(root);
					updateHeight(root);
				}
				else {
					root = rotateRight(root);
					updateHeight(root);
				}
			}
			else if (checkBalance(root) < -1) {
				if (checkBalance(root->right) > 1) {
					root->right = rotateRight(root->right);
					updateHeight(root);
					root = rotateLeft(root);
					updateHeight(root);
				}
				else {
					root = rotateLeft(root);
					updateHeight(root);
				}
			}
		}
	}
}

int main() {
	Node* root;
	initAVLTree(root);
	insert(root, 5);
	insert(root, 6);
	insert(root, 7);
	insert(root, 8);
	LNR(root);
	cout << endl;
	//del(root, 9);
	//LNR(root);
	//cout << endl;
	//if (search(root, 7) != NULL) cout << "Tim thay!\n";
	//else cout << "Khong tim thay!\n";
	system("pause");
	return 1;
}