#pragma once

#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

//khai bao struct
struct date {
	int ngay, thang, nam;
};


struct user {
	/*Tên đăng nhập, mật khẩu, họ tên, ngày sinh, CMND, Địa chỉ, Giới
tính, Tình trạng (activated hoặc block). Có 2 loại người dùng là quản lý thư viện và
chuyên viên.*/
	bool managertype; //true=manager=quản lí, false=staff=chuyên viên
	bool isadmin; //true=admin, only have 1 admin
	char account[50];
	char pass[50];
	char name[50];
	date birth;
	char cmnd[20];
	char address[80];
	bool sexmale;//true=male,fale=female
	bool active; // true=actived, false =block

};
struct usernode {
	user data;
	usernode* next;

};

struct Userlist {
	usernode* head;

};
struct card {
	/*Thông tin thẻ độc giả cần quản lí bao gồm: mã độc giả, họ tên, CMND, ngày tháng năm
sinh, giới tính, email, địa chỉ, ngày lập thẻ và ngày hết hạn của thẻ (48 tháng kể từ ngày
lập thẻ)*/
	char id[20]; //mã thẻ
	char name[50];
	char cmnd[20];
	date birth;
	bool sexmale; //true=male,fale=female
	char email[50];
	char address[80];
	date createdate;
	date outofdate; //48 thang sau ngay lap the



};




//khai bao ham
user signin();
bool loadusers(Userlist&); //neu danh sach rong thi tra ve false
bool saveusers(Userlist);
usernode*findprevi(Userlist, int);
void adduser(Userlist&, user);
int useramount(Userlist);
user dangnhapdangki(Userlist&);
user changepass(Userlist& , user&);
user changeinfor(Userlist&, user& );
void showinfor(user );
bool findadmin(Userlist l);
void function1(Userlist& l, user& u);



//function2

struct reader {
	/* mã độc giả, họ tên, CMND, ngày tháng năm
	sinh, giới tính, email, địa chỉ, ngày lập thẻ và ngày hết hạn của thẻ(48 tháng kể từ ngày
		lập thẻ).
		*/
	char id[30], name[50], cmnd[20], birthday[20], email[20], addr[50];
	char sex[10];
	date makeday, outofday;
};

struct RNode {
	reader data;
	RNode* next;
};

struct RList {
	RNode* head;
	int num;
};

void rprint(RNode*);
void raddData(reader&);
RNode* rmakeNode(reader);
void raddList(RList&, reader);
void rreadFile(FILE*, RList&);
void rwriteFile(FILE*, RList);
RNode* rfindISBN(RList, char*);
RNode* rfindName(RList, char*);
void redit(RNode*&);
void rdelete(RList&, RNode*);

void rmenu(FILE*, RList&, reader, int);