#include <iostream>
using namespace std;
#define MAX 100

struct DSach {
	int arr[MAX];
	int n=0;
};

void swap(int &i,int &j) {
	int temp = i;
	i = j;
	j = temp;

}

void sapXep(DSach& ds) {
	for (int i = 0; i < ds.n-1; i++) {
		for (int j = i; j < ds.n; j++)
			if (ds.arr[i] > ds.arr[j])
				swap(ds.arr[i], ds.arr[j]);
	}
}

void themPhanTuDS(DSach& ds, int x) {
	if (ds.n <= MAX) {
		ds.arr[ds.n++] = x;
		sapXep(ds);
	}
	else cout << "Qua so luong toi da!\n";
}

void xuat(DSach ds) {
	cout << "Cac gia tri cua mang co " << ds.n << " phan tu:\n";
	for (int i = 0; i < ds.n; i++) {
		cout << ds.arr[i] << " ";
	}
	cout << endl;
}


int timKiemTuanTu(DSach ds, int x) {
	for (int i = 0; i < ds.n; i++) {
		if (ds.arr[i] == x) return i;
	}
	return -1;
}

bool timKiemNhiPhan(DSach ds, int x) {
	int left = 0, right = ds.n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (x == ds.arr[mid]) return true;
		else if (x > ds.arr[mid])
			left = mid + 1;
		else right = mid - 1;
	}
	return false;
}

void xoaPhanTuTaiViTrii(DSach& ds, int i) {
	if (ds.n == 0) {
		cout << "Danh sach trong!\n";
	}
	else {
		for (int j = i - 1; j < ds.n - 1; j++) {
			ds.arr[j] = ds.arr[j + 1];
		}
		ds.n--;
		cout << "Xoa thanh cong!\n";
	}
}

void timKiemVaXoa(DSach& ds, int x) {
	if (timKiemTuanTu(ds, x) < ds.n && timKiemTuanTu(ds, x) >= 0) {
		xoaPhanTuTaiViTrii(ds, timKiemTuanTu(ds, x) + 1);
	}
	else cout << "Khong co phan tu trong danh sach!\n";
}

void gopHaiDS(DSach& ds, DSach& ds1) {
	int temp = ds.n;
	if (ds.n + ds1.n > 100) cout << "Khong the gop!\n";
	else {
		for (int i = 0; i < ds1.n; i++) {
			ds.arr[temp++] = ds1.arr[i];
		}
		ds.n += ds1.n;
		sapXep(ds);
		cout << "Gop thanh cong!\n";
	}

}

int main() {
	DSach ds;
	int n, temp;
	do {
		cout << "Nhap so luong phan tu cho danh sach 1: (toi da " << MAX << "): ";
		cin >> n;
		if (n <= 0 || n > 100) cout << "So luong khong hop le!\n";
	} while (n <= 0 || n > 100);
	cout << "Nhap gia tri cho danh sach:\n";
	for (int i = 0; i < n; i++) {
		cin >> temp;
		themPhanTuDS(ds, temp);
	}
	xuat(ds);
	cout << "Nhap phan tu can tim kiem: ";
	cin >> temp;
	if (timKiemTuanTu(ds, temp) < ds.n && timKiemTuanTu(ds, temp) >= 0) cout << "Co phan tu trong danh sach!\n";
	else cout << "Khong co phan tu trong danh sach!\n";
	cout << "Nhap phan tu can tim kiem: ";
	cin >> temp;
	if (timKiemNhiPhan(ds, temp)) cout << "Co phan tu trong danh sach!\n";
	else cout << "Khong co phan tu trong danh sach!\n";
	cout << "Nhap phan tu can tim kiem va xoa: ";
	cin >> temp;
	timKiemVaXoa(ds, temp);
	xuat(ds);
	DSach ds1;
	do {
		cout << "Nhap so luong phan tu cho danh sach 2: (toi da " << MAX << "): ";
		cin >> n;
		if (n <= 0 || n > 100) cout << "So luong khong hop le!\n";
	} while (n <= 0 || n > 100);
	cout << "Nhap gia tri cho danh sach:\n";
	for (int i = 0; i < n; i++) {
		cin >> temp;
		themPhanTuDS(ds1, temp);
	}
	xuat(ds1);
	gopHaiDS(ds, ds1);
	xuat(ds);
	system("pause");
	return 0;
}