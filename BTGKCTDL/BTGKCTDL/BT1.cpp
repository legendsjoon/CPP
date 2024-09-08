#include <iostream>
using namespace std;
#define MAX 100
int arr[MAX];
int n;

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

void importList(int arr[], int& n) {
	do {
		cout << "Nhap so phan tu: ";
		cin >> n;
		if (n <= 0 || n > MAX) {
			cout << "Khong hop le!\n";
			system("pause");
			system("cls");
		}
	} while (n <= 0 || n > MAX);
	cout << "Nhap gia tri cho danh sach dac:\n";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

void exportList(int arr[], int n) {
	cout << "Gia tri trong danh sach dac:\n";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int find(int arr[], int n, int key) {
	for (int i = 0; i < n; i++) {
		if (key == arr[i])
			return i;
	}
	return -1;
}

void insertLast(int arr[], int& n, int x) {
	if (n == MAX)
		cout << "Danh sach day!\n";
	else {
		arr[n++] = x;
	}
}

void delByPos(int arr[], int& n, int pos) {
	if (n == 0)
		cout << "Danh sach rong!\n";
	else {
		for (int i = pos; i < n - 1; i++) {
			arr[i] = arr[i + 1];
		}
		n--;
	}
}

void addByPos(int arr[], int& n, int pos, int x) {
	if (n == MAX)
		cout << "Danh sach day!\n";
	else {
		if (pos > n || pos < 0)
			cout << "Vi tri khong hop le!\n";
		else {
			for (int i = n; i > pos; i--) {
				arr[i] = arr[i - 1];
			}
			arr[pos] = x;
			n++;
		}
	}
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void selectionSort(int arr[], int n) {
	int minpos;
	for (int i = 0; i < n - 1; i++) {
		minpos = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[minpos] < arr[j])
				minpos = j;
		}
		if (minpos != i)
			swap(arr[i], arr[minpos]);
	}
}

void insertionSort(int arr[], int n) {
	for (int i = 1; i < n; i++) {
		int x = arr[i], j = i - 1;
		while (j >= 0 && arr[j] < x) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = x;
	}
}

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (arr[j] > arr[j - 1])
				swap(arr[j], arr[j - 1]);
		}
	}
}

void interchangeSort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] < arr[j])
				swap(arr[i], arr[j]);
		}
	}
}

void quickSort(int arr[], int left, int right) {
	int pivot = left + (right - left) / 2;
	int l = left, r = right;
	while (l <= r) {
		while (arr[l] > arr[pivot])
			l++;
		while (arr[r] < arr[pivot])
			r--;
		if (l <= r) {
			swap(arr[l++], arr[r--]);
		}
	}
	if (r > left)
		quickSort(arr, left, r);
	if (l < right)
		quickSort(arr, l, right);
}

void quickSortNoRecursion(int arr[], int left, int right) {
	Stack s;
	initStack(s);
	push(s, left);
	push(s, right);
	while (!isEmpty(s)) {
		int rt = pop(s), lf = pop(s);
		int r = rt, l = lf;
		int pivot = l + (r - l) / 2;
		while (l <= r) {
			while (arr[l] > arr[pivot])
				l++;
			while (arr[r] < arr[pivot])
				r--;
			if (l <= r) {
				swap(arr[l++], arr[r--]);
			}
		}
		if (r > lf) {
			push(s, lf);
			push(s, r);
		}
		if (l < rt) {
			push(s, l);
			push(s, rt);
		}
	}
}
void merge(int arr[], int left, int mid, int right) {
	int N1[MAX], N2[MAX];
	int n1 = 0, n2 = 0;
	for (int i = left; i <= mid; i++) {
		N1[n1++] = arr[i];
	}
	for (int i = mid + 1; i <= right; i++) {
		N2[n2++] = arr[i];
	}
	int x = 0, y = 0, z = left;
	while (x < n1 && y < n2) {
		if (N1[x] > N2[y]) {
			arr[z++] = N1[x++];
		}
		else
			arr[z++] = N2[y++];
	}
	while (x < n1)
		arr[z++] = N1[x++];
	while (y < n2)
		arr[z++] = N2[y++];;
}

void mergeSort(int arr[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

void heapify(int arr[], int n, int root) {
	int left = root * 2 + 1;
	int right = root * 2 + 2;
	int min = root;
	if (left < n && arr[min] > arr[left])
		min = left;
	if (right < n && arr[min] > arr[right])
		min = right;
	if (min != root) {
		swap(arr[root], arr[min]);
		heapify(arr, n, min);
	}
}

void heapSort(int arr[], int n) {
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int main() {
	importList(arr, n);
	exportList(arr, n);
	//if (find(arr, n, 5)!=-1) cout << "Tim thay!\n";
	//else cout << "Khong tim thay!\n";
	//insertLast(arr, n, 20);
	//exportList(arr, n);
	//delByPos(arr, n, 2);
	//exportList(arr, n);
	//addByPos(arr, n, 3, 10);
	//exportList(arr, n);
	heapSort(arr, n);
	exportList(arr, n);
	system("pause");
	return 0;
}