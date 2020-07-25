
#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include"funtion12.h"
using namespace std;




//dinh nghia ham of function 1
user signin() {
	cout << "\n***********tao tai khoan moi*************";
	user u;
	/*Tên đăng nhập, mật khẩu, họ tên, ngày sinh, CMND, Địa chỉ, Giới
tính, Tình trạng (activated hoặc block). Có 2 loại người dùng là quản lý thư viện và
chuyên viên.*/



	cout << "\nmoi nhap ten dang nhap(khong duoc co dau cach): ";
	cin >> u.account;
	
	cout << "\nmoi nhap mat khau(khong duoc co dau cach): ";
	cin >> u.pass;
	cin.ignore();
	cout << "\nmoi nhap ho ten cua ban: ";
	//gets( u.name);
	cin.getline(u.name, 50);
	cout << "\nmoi nhap ngay sinh: ";
	cin >> u.birth.ngay;
	cout << "\nmoi nhap thang sinh: ";
	cin >> u.birth.thang;
	cout << "\nmoi nhap nam sinh: ";
	cin >> u.birth.nam;
	cout << "\nmoi nhap cmnd: ";
	cin >> u.cmnd;
	cin.ignore();
	cout << "\nmoi nhap dia chi: ";
	//getline(cin, u.address);
	cin.getline(u.address, 80);
	cout << "\nban la nam hay nu \n1:nam \n0:nu   ";
	int sex;
	cin >> sex;
	if (sex == 1) u.sexmale = true;
	if (sex == 0)u.sexmale = false;
	cout << "\nmoi nhap loai nguoi dung muon tao: \n1:manager\n2:staff\n3:admin:  ";
	int z;
	cin >> z;
	if (z == 1) {

		u.managertype = true;
		u.isadmin = false;
		u.active = true;
	}
	if (z == 2) {
		u.managertype = false;
		u.isadmin = false;
		u.active = true;
	}
	if (z == 3) {
		//can kiem tra xem co admin chua
		
			//gia su chua co admin

		u.managertype = false;
		u.isadmin = true;
		u.active = true;

	}
	return u;
}
bool loadusers(Userlist& l) {

	FILE*f;
	fopen_s(&f, "userdata.bin", "rb");
	if (f == NULL) {
		return false;
	}

	l.head = NULL;
	int num;
	fread(&num, sizeof(num), 1, f);
	for (int i = 0; i < num; i++) {
		user temp;
		fread(&temp, sizeof(temp), 1, f);
		adduser(l, temp);


	}




	fclose(f);
	return true;
}
bool saveusers(Userlist l) {
	FILE*f;
	fopen_s(&f, "userdata.bin", "wb");
	int num = useramount(l);
	fwrite(&num, sizeof(num), 1, f);

	usernode*p = l.head;
	for (; p; p = p->next) {
		fwrite(&(*p), sizeof(user), 1, f);
	}


	fclose(f);
	return true;
}
usernode*findprevi(Userlist l, int i) {
	int k = 0;

	for (usernode*p = l.head; p; p = p->next) {
		if (k == i - 1) return p;
		k++;

	}

}
void adduser(Userlist& l, user user) {

	//cout << "l.num= " << useramount(l)<<endl;
	int num = useramount(l);

	usernode* newnode = new usernode;
	newnode->data = user;
	newnode->next = NULL;
	if (l.head == NULL) {
		l.head = newnode;

		return;
	}
	if (num > 2) {
		usernode*tail = findprevi(l, num - 1)->next;
		tail->next = newnode;

		return;
	}
	else if (num == 1) {
		usernode*tail = l.head;
		tail->next = newnode;
		num++;
		return;
	}
	else if (num == 2) {
		usernode*tail = l.head->next;

		tail->next = newnode;
		num++;
		return;

	}
}
int useramount(Userlist l) {
	if (l.head == NULL) return 0;
	if (l.head->next == NULL) return 1;
	if (l.head->next->next == NULL) return 2;
	int k = 0;
	for (usernode*p = l.head; p; p = p->next) {
		k++;
	}
	return k;
}
user dangnhapdangki(Userlist& l) {
	int z;
	if (findadmin(l)==false) z = 2;
	else z = 1;

	if (z == 1) {
	//dang nhap
		bool found = false;

		do
		{


			cout << "\nmoi nhap ten dang nhap: ";
			char account[50];
			cin >> account;
			cout << "\nmoi nhap mat khau: ";
			char pass[50];
			cin >> pass;
			for (usernode*p = l.head; p; p = p->next) {
				if (strcmp(account, p->data.account) == 0 && strcmp(pass, p->data.pass) == 0) {
					return p->data;
				}

			}
			cout << "\nten dang nhap hoac mat khau khong dung ";
		} while (!found);
		
	}
	else if (z == 2) {
		cout << "\nchua co admin, xin hay tao mot tai khoan admin\n";
		user u = signin();
		for (usernode*p = l.head; p; p = p->next) {
			while (strcmp(u.account, p->data.account) == 0) {
				cout << "\nXin loi, ten tai khoan da co nguoi su dung, moi nhap ten tai khoan khac";
				cin >> u.account;

			}

		}
		adduser(l, u);
		return u;
	}

}
user changepass(Userlist& l, user& u) {
	
	for (usernode*p = l.head; p; p = p->next) {
		if (strcmp(u.account, p->data.account) == 0 && strcmp(u.pass, p->data.pass) == 0) {
			{
				cin.ignore();
				cout << "\nmoi nhap mat khau moi: ";
				cin >> p->data.pass;
				cout << "\nda cap nhat mat khau moi";
				return p->data;
			}
		}

	}
}
user changeinfor(Userlist&l, user& u) {
	cout << "\nThay doi thong tin:\n";
	for (usernode*p = l.head; p; p = p->next) {
		if (strcmp(u.account, p->data.account) == 0 && strcmp(u.pass, p->data.pass) == 0) {
			{
				cin.ignore();
				cout << "\nmoi nhap ho ten cua ban: ";
				//gets( u.name);
				cin.getline(u.name, 50);
				cout << "\nmoi nhap ngay sinh: ";
				cin >> u.birth.ngay;
				cout << "\nmoi nhap thang sinh: ";
				cin >> u.birth.thang;
				cout << "\nmoi nhap nam sinh: ";
				cin >> u.birth.nam;
				cout << "\nmoi nhap cmnd: ";
				cin >> u.cmnd;
				cin.ignore();
				cout << "\nmoi nhap dia chi: ";
				//getline(cin, u.address);
				cin.getline(u.address, 80);
				cout << "\nban la nam hay nu \n1:nam \n0:nu   ";
				int sex;
				cin >> sex;
				if (sex == 1) u.sexmale = true;
				if (sex == 0)u.sexmale = false;
				p->data = u;


				return p->data;
			}
		}

	}
}
void showinfor(user u) {
	cout << "\nten dang nhap: ";
	cout << u.account<<endl;
	cout << "\mat khau: ";
	cout<< u.pass<<endl;
	
	cout << "\nho ten cua ban: ";
	//gets( u.name);
	cout << u.name<<endl;
	cout << "\nngay thang nam sinh: ";
	cout << u.birth.ngay << "/" << u.birth.thang << "/" << u.birth.nam << endl;
	cout << "\ncmnd: ";
	cout << u.cmnd<<endl;
	
	cout << "\ndia chi: ";
	cout<<(u.address);
	
	if (u.sexmale) cout << "\ngioi tinh nam";
	else cout << "\ngioi tinh nu";
	
}
bool findadmin(Userlist l) {
	for (usernode*p = l.head; p; p = p->next) {
		if (p->data.isadmin) return true;
	}
	return false;
}
void function1(Userlist& l, user& u) {
	cout << "\nHay chon thao tac ban muon lam: ";
	cout << "\n1:dang xuat";
	cout << "\n2:Thay doi mat khau";
	cout << "\n3:Thay doi thong tin ca nhan";
	cout << "\n4:tao nguoi dung (only admin)";
	cout << "\n5:phan quyen nguoi dung(only admin)";
	cout << "\n0:back";
	cout << "\n";
	int z;
	cin >> z;
	if (z == 0) {
		saveusers(l);
		return;
	}
	if (z == 1) {
		cout<<"\nDa dang xuat, moi dang nhap lai";
		u=dangnhapdangki(l);
		saveusers(l);

		return;
	}
	if (z == 2) {
		u=changepass(l, u);
		saveusers(l);

		return;
	}
	if (z == 3) {
		cout << "day la thong tin hien tai cua ban:\n";
		showinfor(u);

		u=changeinfor(l, u);
		saveusers(l);

		return;
	}
	if (z == 4) {
		if (u.isadmin) {
			user newuser = signin();
			if (newuser.isadmin) {
				cout << "\nxin loi, khong the tao them admin, tai khoan nay se mac dinh la manager";
				newuser.isadmin = false;
				newuser.managertype = true;
			}
			adduser(l, newuser);
			saveusers(l);

			return;
		}
		if (!u.isadmin) {
			cout << "\nXin loi, chuc nang nay chi dung cho admin";
			return;
		}
	}

	if (z == 5) {
		if (!u.isadmin) {
			cout << "\nXin loi, chuc nang nay chi dung cho admin";
			return;
		}
		else if(u.isadmin){
			cout << "\nsau day la danh sach users:\n ";
			int k = 0;
			for (usernode*p = l.head; p; p = p->next) {
				cout << "[" << k << "] :" << p->data.account << endl;
				k++;
			}
			cout << "\nmoi nhap so thu tu cua nguoi ban muon phan quyen: ";
			int m;
			cin >> m;
			usernode* thatuser;
			if (m != 0) { thatuser = findprevi(l, m)->next; }
			else {
				thatuser = l.head;
			}
			cout << "\nBan muon thay doi quyen cua " << thatuser->data.account << " thanh:\n1:manager\n2:chuyen vien";
			int a;
			cin >> a;
			if (a == 1) {
				thatuser->data.isadmin = false;
				thatuser->data.managertype = true;
			}
			if (a == 2) {
				thatuser->data.isadmin = false;
				thatuser->data.managertype = false;
			}
			cout << "\nphan quyen thanh cong";
			saveusers(l);

		}
	}
}


//dinh nghia ham of function 2

void rprint(RNode* p) {
	cout << "Ma ID: ";
	cout << p->data.id << "\n";
	cout << "Ten: ";
	cout << p->data.name << "\n";
	cout << "cmnd: ";
	cout << p->data.cmnd << "\n";
	cout << "ngay sinh: ";
	cout << p->data.birthday << "\n";
	cout << "email: ";
	cout << p->data.email << "\n";
	cout << "dia chi: ";
	cout << p->data.addr << "\n";
	cout << "gioi tinh: ";
	cout << p->data.sex; 
	cout << endl;
	cout << "ngay lap the: ";
	cout << p->data.makeday.ngay<<"/"<<p->data.makeday.thang<<"/"<<p->data.makeday.nam << "\n";
	cout << "\n";
}

void raddData(reader& b) {
	cout << "Nhap ma ID: ";
	cin.ignore();
	cin.getline(b.id, sizeof(b.id));
	cout << "Nhap ho ten: ";
	cin.getline(b.name, 50);
	cout << "Nhap cmnd: ";
	cin.getline(b.cmnd, 20);
	cout << "Nhap ngay thang nam sinh:";
	cin.getline(b.birthday, 20);
	cout << "Nhap email: ";
	
	cin.getline(b.email, 20);
	cout << "Nhap dia chi: ";
	cin.getline(b.addr, 10);
	cout << "Nhap gioi tinh (nam hay nu): ";
	cin.getline(b.sex, 10);
}

RNode* rmakeNode(reader data) {
	RNode* n = new RNode;
	n->data = data;
	n->next = NULL;
	return n;
}

void raddList(RList& b, reader data) {
	RNode* n = rmakeNode(data);
	if (b.head == NULL) {
		b.head = n;
		return;
	}
	n->next = b.head;
	b.head = n;
	b.num++;
}

void rreadFile(FILE* inf, RList& b) {
	reader bk;
	while (!feof(inf)) {
		fscanf_s(inf, "%[^,],", bk.id, 30);
		fscanf_s(inf, "%[^,],", bk.name, 50);
		fscanf_s(inf, "%[^,],", bk.cmnd, 20);
		fscanf_s(inf, "%[^,],", bk.birthday, 20);
		fscanf_s(inf, "%[^,],", bk.email, 20);
		fscanf_s(inf, "%[^,],", bk.addr, 50);
		fscanf_s(inf, "%[^\n]\n,", bk.sex, 10);
		raddList(b, bk);
	}
}

void rwriteFile(FILE* outf, RList b) {
	for (RNode* p = b.head; p; p = p->next) {
		fprintf_s(outf, "%s,", p->data.id);
		fprintf_s(outf, "%s,", p->data.name);
		fprintf_s(outf, "%s,", p->data.cmnd);
		fprintf_s(outf, "%s,", p->data.birthday);
	
		fprintf_s(outf, "%s,", p->data.email);
		fprintf_s(outf, "%s,", p->data.addr);
		fprintf_s(outf, "%s\n", p->data.sex);
	}
}

RNode* rfindISBN(RList b, char* id) {
	RNode* p = b.head;
	for (RNode* p = b.head; p; p = p->next) {
		if (strcmp(p->data.id, id) == 0) {
			return p;
		}
	}
	return NULL;
}

RNode* rfindName(RList b, char* name) {
	RNode* p = b.head;
	for (RNode* p = b.head; p; p = p->next) {
		if (strcmp(p->data.name, name) == 0) {
			return p;
		}
	}
	return NULL;
}

void redit(RNode*& p) {
	int x;
	cout << "1:ID" << endl;
	cout << "2:Ten" << endl;
	cout << "3:Cmnd" << endl;
	cout << "4:Ngay thang nam sinh" << endl;
	//cout << "5:Nam xuat ban" << endl;
	cout << "5:Email" << endl;
	cout << "6:Dia chi" << endl;
	cout << "7:Gioi tinh" << endl;
	cout << "Nhap muc muon chinh sua: ";
	cin >> x;
	switch (x) {
	case 1: {
		cout << "Nhap ma ID: ";
		cin.ignore();
		cin.getline(p->data.id, 100);
		return;
	}
	case 2: {
		cout << "Nhap ten moi: ";
		cin.ignore();
		cin.getline(p->data.name, 100);
		return;
	}
	case 3: {
		cout << "Nhap cmnd moi: ";
		cin.ignore();
		cin.getline(p->data.cmnd, 100);
		return;
	}
	case 4: {
		cout << "Nhap ten ngay sinh moi: ";
		cin.ignore();
		cin.getline(p->data.birthday, 100);
		return;
	}
	case 5: {
		cout << "Nhap emial moi: ";
		cin.ignore();
		cin.getline(p->data.email, 100);
		return;
	}
	case 6: {
		cout << "Nhap  dia chi moi: ";
		cin.ignore();
		cin.getline(p->data.addr, 100);
		return;
	}
	case 7: {
		cout << "Nhap gioi tinh moi: ";
		cin.ignore();
		cin.getline(p->data.sex, 100);
		return;
	}

	}
}

void rdelete(RList& b, RNode* bk) {
	RNode* p = b.head;
	if (p == bk) {
		RNode* n = p;
		b.head = p->next;
		delete n;
		return;
	}
	while (p->next) {
		if (p->next == bk) {
			RNode* n = p->next;
			p->next = p->next->next;
			delete n;
			return;
		}
		p = p->next;
	}
}

void rmenu(FILE* f, RList& b, reader bk, int n) {
	cout << "0:Ket thuc chuong trinh" << endl;
	cout << "1:Xem danh sach cac nguoi doc" << endl;
	cout << "2:Them nguoi doc" << endl;
	cout << "3:Chinh sua thong tin nguoi doc" << endl;
	cout << "4:Xoa thong tin nguoi doc" << endl;
	cout << "5:Tim kiem nguoi doc theo ten" << endl;
	cout << "6:Tim kiem nguoi doc theo ID" << endl;
	cout << "Nhap hanh dong muon thuc hien: ";
	cin >> n;
	cout << endl;
	switch (n) {
	case 0: {
		return;
	}
	case 1: {

		for (RNode* p = b.head; p; p = p->next) {
			rprint(p);
		}
		rmenu(f, b, bk, n);
		return;
	}
	case 2: {
		raddData(bk);
		raddList(b, bk);
		cout << endl;
		rmenu(f, b, bk, n);
		return;
	}
	case 3: {
		int x;
		cout << "1:Tim theo ten" << endl;
		cout << "2:Tim theo ma ID" << endl;
		cin >> x;
		switch (x) {
		case 1: {
			char name[50];
			cout << "Nhap ten nguoi doc ban muon sua: ";
			cin.ignore();
			cin.getline(name, 50);
			RNode* p = rfindName(b, name);
			redit(p);
			rprint(p);
			rmenu(f, b, bk, n);
			return;
		}
		case 2: {
			char isbn[20];
			cout << "Nhap ma ID cua nguoi doc ban muon sua: ";
			cin.ignore();
			cin.getline(isbn, 20);
			RNode* p = rfindISBN(b, isbn);
			redit(p);
			rprint(p);
			rmenu(f, b, bk, n);
			return;
		}
		}
	}
	case 4: {
		int x;
		cout << "1:Tim nguoi doc theo ten" << endl;
		cout << "2:Tim nguoi doc theo ma ID" << endl;
		cin >> x;
		switch (x) {
		case 1: {
			char name[50];
			cout << "Nhap ten cuon sach ban muon xoa: ";
			cin.ignore();
			cin.getline(name, 50);
			RNode* p = rfindName(b, name);
			rdelete(b, p);
			cout << "Da xoa thanh cong" << endl;
			cout << endl;
			rmenu(f, b, bk, n);
			return;
		}
		case 2: {
			char isbn[20];
			cout << "Nhap ma ID cua nguoi ban muon xoa: ";
			cin.ignore();
			cin.getline(isbn, 20);
			RNode* p = rfindISBN(b, isbn);
			rdelete(b, p);
			cout << "Da xoa thanh cong" << endl;
			cout << endl;
			rmenu(f, b, bk, n);
			return;
		}
		}
	}
	case 5: {
		char name[50];
		cout << "Nhap ten nguoi ban muon tim: ";
		cin.ignore();
		cin.getline(name, 50);
		RNode* p = rfindName(b, name);
		rprint(p);
		rmenu(f, b, bk, n);
		return;
	}
	case 6: {
		char isbn[20];
		cout << "Nhap ma ID cua nguoi doc ban muon tim: ";
		cin.ignore();
		cin.getline(isbn, 20);
		RNode* p = rfindISBN(b, isbn);
		rprint(p);
		rmenu(f, b, bk, n);
		return;
	}
	}
}