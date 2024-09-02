#include <iostream>
using namespace std;
#define MAX 100

struct DSach {
	int arr[MAX];
	int n = 0;
};
//Cac ham cua danh sach co thu tu
void swap(int& i, int& j) {
	int temp = i;
	i = j;
	j = temp;

}

void sapXep(DSach& ds) {
	for (int i = 0; i < ds.n - 1; i++) {
		for (int j = i; j < ds.n; j++)
			if (ds.arr[i] > ds.arr[j])
				swap(ds.arr[i], ds.arr[j]);
	}
}

void themPhanTuDSCTT(DSach& ds, int x) {
	if (ds.n <= MAX) {
		ds.arr[ds.n++] = x;
		sapXep(ds);
	}
	else cout << "Qua so luong toi da!\n";
}

void xuatDSCTT(DSach ds) {
	cout << "Cac gia tri cua mang co " << ds.n << " phan tu:\n";
	for (int i = 0; i < ds.n; i++) {
		cout << ds.arr[i] << " ";
	}
	cout << endl;
}

struct Node {
	int info;
	Node *link;
};
//Cac ham cua danh sach lien ket don
void xuatDSLKD(Node* first) {
	Node* temp;
	if (first != NULL) {
		temp = first;
		while (temp != NULL) {
			cout << temp->info << " ";
			temp = temp->link;
		}
		cout << endl;
	}
	else cout << "Danh sach trong!\n";
}

bool timKiem(Node* first,int x) {
	Node* temp;
	if (first != NULL) {
		temp = first;
		while (temp != NULL) {
			if (temp->info == x) return true;
			temp = temp->link;
		}
		cout << endl;
	}
	return false;
}

void themPhanTuDauDS(Node*& first, int x) {
	if (first == NULL) {
		first = new Node;
		first->info = x;
		first->link = NULL;
	}
	else {
		Node* temp = first;
		first = new Node;
		first->info = x;
		first->link = temp;
	}
}

void xoaPhanTuDauDS(Node*& first) {
	if (first == NULL) {
		cout << "Danh sach trong!\n";
	}
	else {
		Node* temp = first->link;
		delete first;
		first = temp;
	}
}

void themPhanTuCuoiDS(Node*& first, int x) {
	if (first == NULL) {
		first = new Node;
		first->info = x;
		first->link = NULL;
	}
	else {
		Node* temp = first,* last = NULL;
		while (temp != NULL) {
			last = temp;
			temp = temp->link;
		}
		temp = new Node;
		temp->info = x;
		temp->link = NULL;
		last->link = temp;

	}
}

void xoaPhanTuCuoiDS(Node*& first) {
	if (first == NULL) {
		cout << "Danh sach trong!\n";
	}
	else {
		Node* temp = first, * pre = NULL, *last = NULL;
		while (temp != NULL) {
			pre = last;
			last = temp;
			temp = temp->link;
		}
		delete last;
		pre->link = NULL;

	}
}

void timKiemVaXoa(Node*& first, int x) {
	if (first == NULL) {
		cout << "Danh sach trong!\n";
	}
	else if (first->link == NULL && first->info == x) {
		delete first;
		first = NULL;
		cout << "Xoa thanh cong!\n";
	}
	else if (first->link != NULL && first->info == x) {
		xoaPhanTuDauDS(first);
	}
	else if (first->link != NULL && first->info != x) {
		Node* temp = first, * pre_del = first, * del = first;
		bool isFound = false;
		while (temp != NULL) {
			pre_del = del;
			del = temp;
			if (temp->info == x) {
				pre_del->link = temp->link;
				delete temp;
				isFound = true;
				break;
			}
			temp = temp->link;

		}
		if (!isFound) cout << "Khong co phan tu nao co gia tri " << x << "!\n";
	}
	else cout << "Khong co phan tu nao co gia tri " << x << "!\n";
}

void chuyenThanhDSCoThuTu(Node* first, DSach& ds) {
	Node* temp;
	if (first != NULL) {
		temp = first;
		while (temp != NULL) {
			themPhanTuDSCTT(ds, temp->info);
			temp = temp->link;
		}
	}
	else cout << "Danh sach trong!\n";
}

int main() {
	Node* first = NULL;
	themPhanTuDauDS(first, 1);
	xuatDSLKD(first);
	themPhanTuDauDS(first, 2);
	xuatDSLKD(first);
	themPhanTuDauDS(first, 3);
	xuatDSLKD(first);
	xoaPhanTuDauDS(first);
	xuatDSLKD(first);
	themPhanTuCuoiDS(first, 4);
	xuatDSLKD(first);
	xoaPhanTuCuoiDS(first);
	xuatDSLKD(first);
	cout << "Nhap gia tri phan tu can xoa: ";
	int temp;
	cin >> temp;
	timKiemVaXoa(first, temp);
	xuatDSLKD(first);
	DSach ds;
	chuyenThanhDSCoThuTu(first, ds);
	xuatDSCTT(ds);
	system("pause");
	return 1;
}
