#include <iostream>
using namespace std;
#define MAX 100

struct DSach {
	int arr[MAX];
	int n;
};

void nhap(DSach &ds) {
	do {
		cout << "Nhap so luong phan tu: (toi da " << MAX << "): ";
		cin >> ds.n;
		if (ds.n <= 0 || ds.n > 100) cout << "So luong khong hop le!\n";
	} while (ds.n <= 0 || ds.n > 100);
	cout << "Nhap gia tri cho mang co " << ds.n << " phan tu:\n";
	for (int i = 0; i < ds.n; i++) {
		cin >> ds.arr[i];
	}
}

void xuat(DSach ds) {
	cout << "Cac gia tri cua mang co " << ds.n << " phan tu:\n";
	for (int i = 0; i < ds.n; i++) {
		cout << ds.arr[i] <<" ";
	}
	cout << endl;
}

int timKiem(DSach ds, int x) {
	for (int i = 0; i < ds.n; i++) {
		if (ds.arr[i] == x) return i;
	}
	return -1;
}

void themPhanTuVaoCuoiDS(DSach &ds, int x) {
	if (ds.n <= MAX) {
		ds.arr[ds.n++] = x;
		cout << "Them phan tu thanh cong!\n";
	}
	else cout << "Qua so luong toi da!\n";
}

void xoaPhanTuVaoCuoiDS(DSach& ds) {
	if (ds.n == 0) {
		cout << "Danh sach trong!\n";
	}
	else {
		ds.n--;
		cout << "Xoa thanh cong!\n";
	}
}

void xoaPhanTuTaiViTrii(DSach& ds, int i) {
	if (ds.n == 0) {
		cout << "Danh sach trong!\n";
	}
	else {
		for (int j = i-1; j < ds.n - 1; j++) {
			ds.arr[j] = ds.arr[j + 1];
		}
		ds.n--;
		cout << "Xoa thanh cong!\n";
	}
}

void themPhanTuVaoViTrii(DSach& ds, int x, int i) {
	if (ds.n <= MAX) {
		for (int j = ds.n; j > i - 1; j--) {
			ds.arr[j] = ds.arr[j - 1];
		}
		ds.arr[i - 1] = x;
		ds.n++;
		cout << "Them phan tu thanh cong!\n";
	}
	else cout << "Qua so luong toi da!\n";
}

void timKiemVaXoa(DSach& ds, int x) {
	if (timKiem(ds, x) < ds.n && timKiem(ds, x) >= 0) {
		xoaPhanTuTaiViTrii(ds, timKiem(ds, x) + 1);
	}
	else cout << "Khong co phan tu trong danh sach!\n";
}

int main() {
	DSach ds;
	nhap(ds);
	xuat(ds);
	cout << "Nhap phan tu can tim kiem: ";
	int temp;
	cin >> temp;
	if (timKiem(ds, temp)<ds.n && timKiem(ds, temp)>=0) cout << "Co phan tu trong danh sach!\n";
	else cout << "Khong co phan tu trong danh sach!\n";
	cout << "Nhap gia tri can them vao cuoi danh sach: ";
	cin >> temp;
	themPhanTuVaoCuoiDS(ds, temp);
	xuat(ds);
	cout << "Xoa gia tri cuoi danh sach: ";
	xoaPhanTuVaoCuoiDS(ds);
	xuat(ds);
	cout << "Nhap vi tri can xoa: ";
	cin >> temp;
	xoaPhanTuTaiViTrii(ds, temp);
	xuat(ds);
	cout << "Nhap gia tri va vi tri can them vao danh sach: ";
	int temp1;
	cin >> temp >> temp1;
	themPhanTuVaoViTrii(ds, temp, temp1);
	xuat(ds);
	cout << "Nhap phan tu can tim kiem va xoa: ";
	cin >> temp;
	timKiemVaXoa(ds, temp);
	xuat(ds);
	system("pause");
	return 0;
}