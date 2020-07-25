#include "pch.h"
#include <iostream>
#include <fstream>
#include "function345.h"
#include "funtion12.h"
using namespace std;

void print(BNode* p) {
	cout << "Ma ISBN: ";
	cout << p->data.isbn << "\n";
	cout << "Ten sach: ";
	cout << p->data.name << "\n";
	cout << "Ten tac gia: ";
	cout << p->data.author << "\n";
	cout << "Nha xuat ban: ";
	cout << p->data.pubCom << "\n";
	cout << "Nam xuat ban: ";
	cout << p->data.pubY << "\n";
	cout << "The loai: ";
	cout << p->data.ctg << "\n";
	cout << "So thu tu cua gia sach: ";
	cout << p->data.bsh << "\n";
	cout << "So luong: ";
	cout << p->data.amt << "\n";
	cout << "\n";
}

void addData(book& b) {
	cout << "Nhap ma ISBN: ";
	cin.ignore();
	cin.getline(b.isbn, 30);
	cout << "Nhap ten sach: ";
	cin.getline(b.name, 50);
	cout << "Nhap ten tac gia: ";
	cin.getline(b.author, 20);
	cout << "Nhap ten nha xuat ban:";
	cin.getline(b.pubCom, 20);
	cout << "Nhap nam xuat ban: ";
	cin.getline(b.pubY, 5);
	cout << "Nhap the loai: ";
	cin.getline(b.ctg, 20);
	cout << "Nhap so thu tu cua gia sach: ";
	cin.getline(b.bsh, 10);
	cout << "Nhap so luong: ";
	cin.getline(b.amt, 10);
}

BNode* makeNode(book data) {
	BNode* n = new BNode;
	n->data = data;
	n->next = NULL;
	return n;
}

void addList(BList& b, book data) {
	BNode* n = makeNode(data);
	if (b.head == NULL) {
		b.head = n;
		return;
	}
	n->next = b.head;
	b.head = n;
	b.num++;
}

void readFile(FILE* inf, BList& b) {
	book bk;
	while (!feof(inf)) {
		fscanf_s(inf, "%[^,],", bk.isbn, 30);
		fscanf_s(inf, "%[^,],", bk.name, 50);
		fscanf_s(inf, "%[^,],", bk.author, 20);
		fscanf_s(inf, "%[^,],", bk.pubCom, 20);
		fscanf_s(inf, "%[^,],", bk.pubY, 5);
		fscanf_s(inf, "%[^,],", bk.ctg, 20);
		fscanf_s(inf, "%[^,],", bk.bsh, 10);
		fscanf_s(inf, "%[^\n]\n,", bk.amt, 10);
		addList(b, bk);
	}
}

void writeFile(FILE* outf, BList b) {
	for (BNode* p = b.head; p; p = p->next) {
		fprintf_s(outf, "%s,", p->data.isbn);
		fprintf_s(outf, "%s,", p->data.name);
		fprintf_s(outf, "%s,", p->data.author);
		fprintf_s(outf, "%s,", p->data.pubCom);
		fprintf_s(outf, "%s,", p->data.pubY);
		fprintf_s(outf, "%s,", p->data.ctg);
		fprintf_s(outf, "%s,", p->data.bsh);
		fprintf_s(outf, "%s\n", p->data.amt);
	}
}

BNode* findISBN(BList b, char* isbn) {
	BNode* p = b.head;
	for (BNode* p = b.head; p; p = p->next) {
		if (strcmp(p->data.isbn, isbn) == 0) {
			return p;
		}
	}
	return NULL;
}

BNode* findName(BList b, char* name) {
	BNode* p = b.head;
	for (BNode* p = b.head; p; p = p->next) {
		if (strcmp(p->data.name, name) == 0) {
			return p;
		}
	}
	return NULL;
}

void edit(BNode*& p) {
	int x;
	cout << "1:ISBN" << endl;
	cout << "2:Ten sach" << endl;
	cout << "3:Ten tac gia" << endl;
	cout << "4:Nha xuat ban" << endl;
	cout << "5:Nam xuat ban" << endl;
	cout << "6:The loai" << endl;
	cout << "7:Gia sach" << endl;
	cout << "8:So quyen sach" << endl;
	cout << "Nhap muc muon chinh sua: ";
	cin >> x;
	switch (x) {
	case 1: {
		cout << "Nhap ma ISBN moi: ";
		cin.ignore();
		cin.getline(p->data.isbn, 100);
		return;
	}
	case 2: {
		cout << "Nhap ten sach moi: ";
		cin.ignore();
		cin.getline(p->data.name, 100);
		return;
	}
	case 3: {
		cout << "Nhap ten tac gia moi: ";
		cin.ignore();
		cin.getline(p->data.author, 100);
		return;
	}
	case 4: {
		cout << "Nhap ten nha xuat ban moi: ";
		cin.ignore();
		cin.getline(p->data.pubCom, 100);
		return;
	}
	case 5: {
		cout << "Nhap nam xuat ban moi: ";
		cin.ignore();
		cin.getline(p->data.pubY, 100);
		return;
	}
	case 6: {
		cout << "Nhap the loai moi: ";
		cin.ignore();
		cin.getline(p->data.ctg, 100);
		return;
	}
	case 7: {
		cout << "Nhap so thu tu gia sach moi: ";
		cin.ignore();
		cin.getline(p->data.bsh, 100);
		return;
	}
	case 8: {
		cout << "Nhap so luong sach moi: ";
		cin.ignore();
		cin.getline(p->data.amt, 100);
		return;
	}
	}
}

void deleteBook(BList& b, BNode* bk) {
	BNode* p = b.head;
	if (p == bk) {
		BNode* n = p;
		b.head = p->next;
		delete n;
		return;
	}
	while (p->next) {
		if (p->next == bk) {
			BNode* n = p->next;
			p->next = p->next->next;
			delete n;
			return;
		}
		p = p->next;
	}
}

void menu(FILE* f, BList& b, book bk, int n) {
	cout << "0:Ket thuc chuong trinh" << endl;
	cout << "1:Xem danh sach cac sach trong thu vien" << endl;
	cout << "2:Them sach" << endl;
	cout << "3:Chinh sua thong tin sach" << endl;
	cout << "4:Xoa thong tin sach" << endl;
	cout << "5:Tim kiem sach theo ten sach" << endl;
	cout << "6:Tim kiem sach theo ISBN" << endl;
	cout << "Nhap hanh dong muon thuc hien: ";
	cin >> n;
	cout << endl;
	switch (n) {
	case 0: {
		return;
	}
	case 1: {

		for (BNode* p = b.head; p; p = p->next) {
			print(p);
		}
		menu(f, b, bk, n);
		return;
	}
	case 2: {
		addData(bk);
		addList(b, bk);
		cout << endl;
		menu(f, b, bk, n);
		return;
	}
	case 3: {
		int x;
		cout << "1:Tim sach theo ten" << endl;
		cout << "2:Tim sach theo ma ISBN" << endl;
		cin >> x;
		switch (x) {
		case 1: {
			char name[50];
			cout << "Nhap ten sach ban muon sua: ";
			cin.ignore();
			cin.getline(name, 50);
			BNode* p = findName(b, name);
			edit(p);
			print(p);
			menu(f, b, bk, n);
			return;
		}
		case 2: {
			char isbn[20];
			cout << "Nhap ma ISBN cua cuon sach ban muon sua: ";
			cin.ignore();
			cin.getline(isbn, 20);
			BNode* p = findISBN(b, isbn);
			edit(p);
			print(p);
			menu(f, b, bk, n);
			return;
		}
		}
	}
	case 4: {
		int x;
		cout << "1:Tim sach theo ten" << endl;
		cout << "2:Tim sach theo ma ISBN" << endl;
		cin >> x;
		switch (x) {
		case 1: {
			char name[50];
			cout << "Nhap ten cuon sach ban muon xoa: ";
			cin.ignore();
			cin.getline(name, 50);
			BNode* p = findName(b, name);
			deleteBook(b, p);
			cout << "Da xoa thanh cong" << endl;
			cout << endl;
			menu(f, b, bk, n);
			return;
		}
		case 2: {
			char isbn[20];
			cout << "Nhap ma ISBN cua cuon sach ban muon xoa: ";
			cin.ignore();
			cin.getline(isbn, 20);
			BNode* p = findISBN(b, isbn);
			deleteBook(b, p);
			cout << "Da xoa thanh cong" << endl;
			cout << endl;
			menu(f, b, bk, n);
			return;
		}
		}
	}
	case 5: {
		char name[50];
		cout << "Nhap ten sach ban muon tim: ";
		cin.ignore();
		cin.getline(name, 50);
		BNode* p = findName(b, name);
		print(p);
		menu(f, b, bk, n);
		return;
	}
	case 6: {
		char isbn[20];
		cout << "Nhap ma ISBN cua cuon sach ban muon tim: ";
		cin.ignore();
		cin.getline(isbn, 20);
		BNode* p = findISBN(b, isbn);
		print(p);
		menu(f, b, bk, n);
		return;
	}
	}
}