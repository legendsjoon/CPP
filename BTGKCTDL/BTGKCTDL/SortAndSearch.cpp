#include <iostream>
using namespace std;
#define MAX 100
int a[] = { 5, 4, 2, 1, 3, 9, 15, 7 };
int n = sizeof(a) / sizeof(a[0]);

struct Stack {
	int a[MAX];
	int top;
};

void initStack(Stack& s) {
	s.top = -1;
}

void push(Stack& s, const int x) {
	if (s.top < MAX) {
		s.top++;
		s.a[s.top] = x;
	}
}

bool isEmpty(Stack s) {
	return s.top == -1;
}

int pop(Stack& s) {
	if (!isEmpty(s)) {
		return s.a[s.top--];
	}
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void selectionSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int minpos = i;
		for (int j = i + 1; j < n; j++) {
			if (a[minpos] > a[j])
				minpos = j;
		}
		if (minpos != i) {
			swap(a[minpos], a[i]);
		}
	}
}

void insertionSort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		int backup = a[i], j = i - 1;
		while (j >= 0 && backup < a[j]) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = backup;
	}
}

void bubbleSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j > i; j--) {
			if (a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
		}
	}
}

void interchangeSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[i] > a[j])
				swap(a[i], a[j]);
}

void quickSort(int a[], int left, int right) {
	int l = left, r = right;
	int pivot = l + (r - l) / 2;
	while (l <= r) {
		while (a[l] < a[pivot])
			l++;
		while (a[r] > a[pivot])
			r--;
		if (l <= r) {
			swap(a[l++], a[r--]);
		}
	}
	if (r > left)
		quickSort(a, left, r);
	if (l < right)
		quickSort(a, l, right);
}

void quickSortNoRecursion(int a[], int n) {
	int left = 0, right = n - 1;
	Stack s;
	initStack(s);
	push(s, left);
	push(s, right);
	while (!isEmpty(s)) {
		int r = right = pop(s);
		int l = left = pop(s);
		int pivot = l + (r - l) / 2;
		while (l <= r) {
			while (a[l] < a[pivot])
				l++;
			while (a[r] > a[pivot])
				r--;
			if (l <= r) {
				swap(a[l++], a[r--]);
			}
		}
		if (r > left) {
			push(s, left);
			push(s, r);
		}
		if (l < right) {
			push(s, l);
			push(s, right);
		}
	}
}

void merge(int a[], int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;
	int a1[MAX];
	int a2[MAX];
	for (int i = 0; i < n1; i++)
		a1[i] = a[l + i];
	for (int i = 0; i < n2; i++)
		a2[i] = a[m + 1 + i];
	int i = 0, j = 0, k = l;
	while (i < n1 && j < n1) {
		if (a1[i] < a2[j])
			a[k++] = a1[i++];
		else
			a[k++] = a2[j++];
	}
	while (i < n1)
		a[k++] = a1[i++];
	while(j<n2)
		a[k++] = a2[j++];
}

void mergeSort(int a[], int left, int right) {
	int mid = left + (right - left) / 2;
	if (left < right) {
		quickSort(a, left, mid);
		quickSort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}

void heapify(int a[], int n, int i) {
	int l = i * 2 + 1;
	int r = i * 2 + 2;
	int largest = i;
	if (l<n && a[l]>a[largest])
		largest = l;
	if (r<n && a[r]>a[largest])
		largest = r;
	if (largest != i) {
		swap(a[i], a[largest]);
		heapify(a, n, largest);
	}
}

void heapSort(int a[], int n) {
	for (int i = (n / 2) - 1; i >= 0 ; i--) {
		heapify(a, n, i);
	}
	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {
	heapSort(a,n);
	print(a, n);
	system("pause");
	return 0;
}