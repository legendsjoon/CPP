#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct DuLieuSV {
	string hoTen;
	long long MSSV;
	char Lop[9];
	long long SDT;
	double diemTB;
};

DuLieuSV taoDuLieuSVTu(string hoTen, long long MSSV, char* Lop, long long SDT, double diemTB) {
	DuLieuSV sv;
	sv.hoTen = hoTen;
	sv.MSSV = MSSV;
	strcpy_s(sv.Lop, Lop);
	sv.SDT = SDT;
	sv.diemTB = diemTB;
	return sv;
}

DuLieuSV taoDuLieuSVTuBanPhim() {
	string hoTen;
	long long MSSV;
	char Lop[9];
	long long SDT;
	double diemTB;
	cout << "Nhap ho va ten: ";
	getline(cin, hoTen);
	cout << "Nhap MSSV: ";
	cin >> MSSV;
	cin.ignore();
	cout << "Nhap lop: ";
	cin.getline(Lop, 9);
	cout << "Nhap so dien thoai: ";
	cin >> SDT;
	cin.ignore();
	cout << "Nhap diem trung binh: ";
	cin >> diemTB;
	DuLieuSV sv;
	sv.hoTen = hoTen;
	sv.MSSV = MSSV;
	strcpy_s(sv.Lop, Lop);
	sv.SDT = SDT;
	sv.diemTB = diemTB;
	return sv;
}

struct SV{
	DuLieuSV dl;
	SV* next, * prev;
};

SV* taoSV(DuLieuSV dl) {
	SV* sv = new SV;
	sv->dl = dl;
	sv->next = sv->prev = NULL;
	return sv;
}

struct DSSV {
	SV* head;
};

void khoiTaoDSSV(DSSV &ds){
	ds.head = NULL;
}

void nhapSV(DSSV &ds) {
	DuLieuSV dl = taoDuLieuSVTuBanPhim();
	if (ds.head == NULL) {
		ds.head = taoSV(dl);
	}
	else {
		SV* p = ds.head;
		while (p->next != NULL)
			p = p->next;
		p->next = taoSV(dl);
		p->next->prev = p;
	}
}

void nhapSV(DSSV& ds, string fileName) {
	ifstream inputFile;
	inputFile.open(fileName);
	DuLieuSV dltam;
	if (inputFile.is_open()) {
		while (inputFile.eof() == false) {
			getline(inputFile, dltam.hoTen, '#');
			inputFile >> dltam.MSSV;
			inputFile.ignore();
			inputFile.getline(dltam.Lop, 9,'#');
			inputFile >> dltam.SDT;
			inputFile.ignore();
			inputFile >> dltam.diemTB;
			inputFile.ignore();
			if (ds.head == NULL) {
				ds.head = taoSV(dltam);
			}
			else {
				SV* p = ds.head;
				while (p->next != NULL)
					p = p->next;
				p->next = taoSV(dltam);
				p->next->prev = p;
			}
		}
		inputFile.close();
	}
}

void xuatSV(SV* sv) {
	cout << "Ho va ten: " << sv->dl.hoTen << endl
		<< "MSSV: " << sv->dl.MSSV << endl
		<< "Lop: " << sv->dl.Lop << endl
		<< "SDT: " << sv->dl.SDT << endl
		<< "Diem trung binh: " << sv->dl.diemTB << endl << endl;
}

void xuatDSSV(DSSV ds) {
	SV* p = ds.head;
	int i = 1;
	while (p != NULL) {
		cout << "SINH VIEN THU " << i++ << ": "<<endl;
		xuatSV(p);
		p = p->next;
	}
}

void xuatDSSVRutGon(DSSV ds) {
	bool isEHT = false, isEMSSV = false, isELop = false, isESDT = false, isEDTB = false;
	bool isExport = false;
	int option;
	while (!isExport) {
		cout << "Cac thong tin se xuat: " << endl;
		cout << "1. Ho ten: " << ((isEHT) ? "Co" : "Khong")<< endl;
		cout << "2. MSSV: " << ((isEMSSV) ? "Co" : "Khong") << endl;
		cout << "3. Lop: " << ((isELop) ? "Co" : "Khong") << endl;
		cout << "4. SDT: " << ((isESDT) ? "Co" : "Khong") << endl;
		cout << "5. Diem trung binh: " << ((isEDTB) ? "Co" : "Khong") << endl;
		cout << "6. Xuat ngay" << endl;
		cout << "Nhap lua chon de thay doi: ";
		cin >> option;
		switch (option)
		{
		case 1:
			if (isEHT)
				isEHT = false;
			else
				isEHT = true;
			break;
		case 2:
			if (isEMSSV)
				isEMSSV = false;
			else
				isEMSSV = true;
			break;
		case 3:
			if (isELop)
				isELop = false;
			else
				isELop = true;
			break;
		case 4:
			if (isESDT)
				isESDT = false;
			else
				isESDT = true;
			break;
		case 5:
			if (isEDTB)
				isEDTB = false;
			else
				isEDTB = true;
			break;
		case 6:
			isExport = true;
		default:
			cout << "Khong hop le!\n";
			system("pause");
			break;
		}
		system("cls");
	}
	SV* p = ds.head;
	int i = 1;
	while (p != NULL) {
		cout << "SINH VIEN THU " << i++ << ": " << endl;
		if (isEHT)
			cout << "Ho va ten: " << p->dl.hoTen << endl;
		if (isEMSSV)
			cout << "MSSV: " << p->dl.MSSV << endl;
		if (isELop)
			cout << "Lop: " << p->dl.Lop << endl;
		if (isESDT)
			cout << "SDT: " << p->dl.SDT << endl;
		if (isEDTB)
			cout << "Diem trung binh: " << p->dl.diemTB << endl;
		cout << endl;
		p = p->next;
	}
}

void timSV(DSSV ds) {
	string hoTen;
	char Lop[9];
	cout << "Nhap ho ten sinh vien can tim kiem: ";
	getline(cin, hoTen);
	cout << "Nhap ten lop cua sinh vien can tim kiem: ";
	cin.getline(Lop, 9);
	SV* p = ds.head;
	bool isFound = false;
	while (p != NULL) {
		if (p->dl.hoTen == hoTen && strcmp(p->dl.Lop, Lop) == 0) {
			xuatSV(p);
			isFound = true;
		}
		p = p->next;
	}
	if (!isFound)
		cout << "Khong tim thay!\n";
}

void xoaSVTheoLop(DSSV& ds) {
	char Lop[9];
	cout << "Nhap ten lop cua sinh vien can tim kiem: ";
	cin.getline(Lop, 9);
	SV* p = ds.head;
	bool isFound = false;
	while (p != NULL) {
		if (strcmp(p->dl.Lop, Lop) == 0) {
			if (p != ds.head) {
				SV* q = p;
				p->prev->next = p->next;
				if(p->next!=NULL)
				p->next->prev = p->prev;
			}
			else {
				ds.head = p->next;
				if (ds.head != NULL)
					ds.head->prev = NULL;
			}
			isFound = true;
		}
		p = p->next;
	}
	if (!isFound)
		cout << "Khong tim thay!\n";
}

void sapXepSVTheoDTB(DSSV& ds) {
	SV* p = ds.head;
	while (p != NULL) {
		SV* q = p->next;
		while (q != NULL) {
			if (p->dl.diemTB < q->dl.diemTB) {
				DuLieuSV tmp;
				tmp = p->dl;
				p->dl = q->dl;
				q->dl = tmp;
			}
			q = q->next;
		}
		p = p->next;
	}
}

void themSVVaoDSCoTT(DSSV& ds) {
	DuLieuSV dl = taoDuLieuSVTuBanPhim();
	if (ds.head == NULL) {
		ds.head = taoSV(dl);
	}
	else {
		SV* p = ds.head;
		SV* pre = ds.head;
		while (p != NULL && p->dl.diemTB > dl.diemTB) {
			pre = p;
			p = p->next;
		}
		if (p == NULL) {
			pre->next = taoSV(dl);
			pre->next->prev = pre;
		}
		else {
			if (pre == p) {
				ds.head = taoSV(dl);
				ds.head->next = p;
				p->prev = ds.head;
			}
			else {
				pre->next = taoSV(dl);
				p->prev = pre->next;
				pre->next->next = p;
				pre->next->prev = pre;
			}
		}
	}
}

void xemTTSV(DSSV ds) {
	SV* p = ds.head;
	SV* pre = NULL;
	int i = 1;
	int option = 0;
	bool isNA = false;
	while (p != NULL && option != 3) {
		cout << "SINH VIEN THU " << i++ << ": " << endl;
		xuatSV(p);
		do {
			cout << "1. Sinh vien tiep theo\n"
				<< "2. Sinh vien truoc do\n"
				<< "3. Thoat\n"
				<< ">Nhap lua chon: ";
			cin >> option;
			switch (option)
			{
			case 1:
				pre = p;
				p = p->next;
				if (p == NULL) {
					cout << "Da toi cuoi danh sach!\n";
					p = pre;
					isNA = true;
				}
				else
					isNA = false;
				break;
			case 2:
				pre = p;
				p = p->prev;
				if (p == NULL) {
					cout << "Da toi dau danh sach!\n";
					p = pre;
					isNA = true;
				}
				else
					isNA = false;

				break;
			case 3:
				isNA = false;
				break;
			default:
				cout << "Khong hop le!\n";
				system("pause");
				break;
			}
		} while ((option != 1 && option != 2 && option != 3) || isNA);
		system("cls");
	}
}

void xuatDSSVRaFile(DSSV ds) {
	ofstream oF;
	oF.open("output.txt");
	if (oF.is_open()) {
		SV* sv = ds.head;
		while (sv != NULL) {
			oF << "Ho va ten: " << sv->dl.hoTen << endl
				<< "MSSV: " << sv->dl.MSSV << endl
				<< "Lop: " << sv->dl.Lop << endl
				<< "SDT: " << sv->dl.SDT << endl
				<< "Diem trung binh: " << sv->dl.diemTB << endl << endl;
			sv = sv->next;
		}
		oF.close();
	}
}

int main() {
	DSSV ds;
	khoiTaoDSSV(ds);
	nhapSV(ds, "dssv.txt");
	sapXepSVTheoDTB(ds);
	xuatDSSVRaFile(ds);
	//xuatDSSV(ds);
	//xoaSVTheoLop(ds);
	//themSVVaoDSCoTT(ds);
	//xuatDSSV(ds);
	//timSV(ds);
}