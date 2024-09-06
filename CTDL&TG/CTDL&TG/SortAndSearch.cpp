#include <iostream>
#include <ctime>
#include <random>
using namespace std;
#define MAX 8
int a[] = { 40, 60, 15, 50, 90, 20, 10, 70 };
//int a[MAX];
void printList(int a[]) {
	for (int i = 0; i < MAX; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void initList(int a[]) {
	for (int i = 0; i < MAX; i++) {
		a[i] = rand() / 100;
	}
}

void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}

void selectionSort(int a[]) {
	int minpos;
	for (int i = 0; i < MAX - 1; i++) {
		minpos = i;
		for (int j = i+1; j < MAX; j++) {
			if (a[minpos] > a[j]) {
				minpos = j;
			}
		}
		swap(a[minpos], a[i]);
	}
}

void insertionSort(int a[]) {
	for (int i = 1; i < MAX; i++) {
		int x = a[i], j = i - 1;
		while (j >= 0 && a[j] > x) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = x;
	}
}

void bubbleSort(int a[]) {
	for (int i = 0; i < MAX - 1; i++) {
		for (int j = MAX - 1; j > i; j--) {
			if (a[j - 1] > a[j])
				swap(a[j], a[j - 1]);
		}
	}
}

void interchangeSort(int arr[]) {
	for (int i = 0; i <MAX-1; i++) {
		for (int j = i + 1; j < MAX; j++) {
			if (a[i] > a[j])
				swap(a[i], a[j]);
		}
	}
}

void merge(int arr[], int l, int m, int r) {
	//Tinh so luonh phan tu cua mang trai va mang phai
	int n1 = m - l + 1;
	int n2 = r - m;
	//Chuyen gia tri cua mang trai va phai vao 2 mang tam
	int* L = new int[n1];
	int* R = new int[n2];
	for (int i = 0; i < n1; i++) {
		L[i] = a[l + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = a[m + 1 + j];
	}
	int i = 0, j = 0, k = l;
	//Sap xep 2 mang vao mang chinh bat dau tu l
	while (i < n1 && j < n2) {
		if (L[i] < R[j]) 
			a[k++] = L[i++];
		else
			a[k++] = R[j++];
	}
	//Chuyen nhung gia tri con lai vao mang chinh
	while (i < n1) {
		a[k++] = L[i++];
	}
	while (j < n2) {
		a[k++] = R[j++];
	}
	delete[]L;
	delete[]R;
}

void mergeSort(int a[], int l, int r) {
	if (l < r) {
		//Tuong tu (l+r)/2 nhung tranh duoc tran so
		int m = l + (r - l) / 2;
		mergeSort(a, l, m);
		mergeSort(a, m + 1, r);
		merge(a, l, m, r);
	}
}

void quickSort(int a[], int l, int r) {
	//Chon pivot o giua
	int pivot = a[(l + r) / 2], left = l, right = r;
	//Chuyen tat ca phan tu nho hon pivot ve phia ben trai va lon hon ve phia ben phai pivot
	while (left <= right) {
		while (a[left] < pivot)
			left++;
		while (a[right] > pivot)
			right--;
		if (left <= right) {
			swap(a[left++], a[right--]);
		}
	}
	//Tiep tuc sap xep mang phia ben trai pivot
	if (left < r)
		quickSort(a, left, r);
	//Tiep tuc sap xep mang phia ben phai pivot
	if (right > l)
		quickSort(a, l, right);
}

void heapify(int a[], int n, int root) {
	int left = root * 2 + 1;
	int right = root * 2 + 2;
	int largest = root;
	if (left < n && a[largest] < a[left])
		largest = left;
	if (right < n && a[largest] < a[right])
		largest = right;
	if (largest != root) {
		swap(a[largest], a[root]);
		heapify(a, n, largest);
	}
}

void heapSort(int a[]) {
	//Xay dung cay heap
	for (int root = MAX / 2 - 1; root >= 0; root--)
		heapify(a,MAX, root);
	for (int i = MAX - 1; i > 0; i--) {
		//Chuyen phan tu lon nhat xuong cuoi cung
		swap(a[0], a[i]);
		//Xay dung lai cay heap de dam bao tinh chat cay
		heapify(a, i, 0);
	}
}

bool sequentialSearch(int a[], int key, int n) {
	for (int i = 0; i < n; i++)
		if (a[i] == key)
			return true;
	return false;
}

bool binarySearch(int a[], int key, int n) {
	int left = 0, right = n - 1, mid;
	while (left<=right) {
		mid = left + (right - left) / 2;
		if (a[mid] == key)
			return true;
		else {
			if (a[mid] < key)
				left = mid + 1;
			else
				right = mid - 1;
		}
	}
}

int main() {
	srand((int)time(NULL));
	//initList(a);
	//quickSort(a,0,MAX-1);
	heapSort(a);
	if (binarySearch(a, 15, MAX)) cout << "Tim thay!\n";
	else cout << "Khong tim thay!\n";
	printList(a);
	system("pause");
	return 1;
}