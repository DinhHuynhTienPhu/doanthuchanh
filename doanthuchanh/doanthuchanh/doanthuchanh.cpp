// doanthuchanh.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include"funtion12.h"
#include "function345.h"

using namespace std;
//khaibao struct

//khai bao bien global
Userlist myuserlist;
user u;
//khaibao ham
void mainmenu();

//dinhnghia ham
void mainmenu() {
	system("PAUSE");
	system("CLS");

	cout << "\n*******DAY LA CHUONG TRINH QUAN LI THU VIEN********";
	cout << "\nBan muon lam gi?\n1:quan li tai khoan\n2:quan li nguoi doc\n3:quan li sach\n4:in phieu muon sach\n5:in phieu tra sach\n6:thong ke so luong";
	cout << "\n0:thoat chuong trinh";

	int b;
	cin >> b;
	system("CLS");
	if (b == 0) {
		return;
	}
	else if (b == 1) {
		function1(myuserlist, u);
	}
	else if (b == 2) {

		RList b;
		reader* bk = new reader;
		b.head = NULL;
		b.num = 0;
		int n = 0;
		FILE* f;
		fopen_s(&f, "nguoidoc.csv", "r");
		if (f != NULL) {
			rreadFile(f, b);
			fclose(f);
		}
		fopen_s(&f, "nguoidoc.csv", "w");
		rmenu(f, b, *bk, n);
		rwriteFile(f, b);
		fclose(f);
	}
	else if (b == 3) {
		
		BList b;
		book* bk = new book;
		b.head = NULL;
		b.num = 0;
		int n = 0;
		FILE* f;
		fopen_s(&f, "thuvien.csv", "r");
		if (f != NULL) {
			readFile(f, b);
			fclose(f);
		}
		fopen_s(&f, "thuvien.csv", "w");
		menu(f, b, *bk, n);
		writeFile(f, b);
		fclose(f);

		
		
	}

	mainmenu();
}
//khai báo biến global





int main()
{


	loadusers(myuserlist);
	//dangnhap
	u=dangnhapdangki(myuserlist);

	mainmenu();



}


