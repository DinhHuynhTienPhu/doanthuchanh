#pragma once
#pragma pack (1)

struct book {
	char isbn[30], name[50], author[20], pubCom[20], pubY[5], ctg[20], bsh[10], amt[10];
};

struct BNode {
	book data;
	BNode* next;
};

struct BList {
	BNode* head;
	int num;
};

void print(BNode*);
void addData(book&);
BNode* makeNode(book);
void addList(BList&, book);
void readFile(FILE*, BList&);
void writeFile(FILE*, BList);
BNode* findISBN(BList, char*);
BNode* findName(BList, char*);
void edit(BNode*&);
void menu(FILE*, BList&, book, int);