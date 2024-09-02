#include <iostream>
using namespace std;
#define	M 199

int hashFunc(int x) {
	return x%M;
}

struct IntVal {
	int key;
};

IntVal* initData(int x) {
	IntVal *p = new IntVal;
	p->key = x;
	return p;
}

struct Node {
	IntVal *data;
	int next;
};

struct HashTable{
	Node h[M];
	int r;
};

void initHashTable(HashTable &ht) {
	for (int i = 0; i < M; i++) {
		ht.h[i].data = NULL;
		ht.h[i].next = -1;
	}
	ht.r = M - 1;
}

void insert(HashTable &ht, int x) {
	int k = hashFunc(x);
	if (ht.h[k].data == NULL) {
		ht.h[k].data = new IntVal;
		ht.h[k].data = initData(x);
	}
	else {
		while (ht.h[k].next != -1) {
			k = ht.h[k].next;
		}
		if (ht.r >= 0) {
			ht.h[ht.r].data = initData(x);
			ht.h[k].next = ht.r;
		}
	}
	while (ht.r>=0 && ht.h[ht.r].data != NULL)
		ht.r--;
}

bool search(HashTable ht, int key) {
	int  k = hashFunc(key);
	while (k !=-1 && ht.h[k].data != NULL) {
			if (ht.h[k].data->key == key)
				return true;
			k = ht.h[k].next;
	}
	return false;
}

void del(HashTable &ht, int key) {
	int  k = hashFunc(key), prev = -1;
	while (k != -1 && ht.h[k].data != NULL && ht.h[k].data->key!=key) {
		prev = k;
		k = ht.h[k].next;
	}
	if (k == -1)
		return;
	IntVal* p = ht.h[k].data;
	delete p;
	while (ht.h[k].next != -1) {
		prev = k;
		k = ht.h[k].next;
		ht.h[prev].data = ht.h[k].data;
	}
	ht.h[k].data = NULL;
		if (prev != -1)
			ht.h[prev].next = -1;
		if (k > ht.r)
			ht.r = k;
}

void printHT(HashTable ht) {
	for (int i = 0; i < M; i++) {
		if (ht.h[i].data != NULL)
			cout << "BUCKET " << i << ": " << ht.h[i].data->key << " | NEXT: " << ht.h[i].next << endl;
	}
}

int main() {
	HashTable ht;
	initHashTable(ht);
	insert(ht, 1);
	insert(ht, 2);
	insert(ht, 3);
	insert(ht, 200);
	insert(ht, 201);
	insert(ht, 399);
	printHT(ht);
	if (search(ht, 4)) cout << "Tim thay!\n";
	else cout << "Khong tim thay!\n";
	cout << "Sau khi xoa:\n";
	del(ht, 1);
	printHT(ht);
	return 1;
}