#include<graphics.h>
#include<iostream> 
#include<string>
#include <fstream>
#include<vector>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#define NUM 3
#define HEIGH 600
#define WIDTH 600
#pragma warning(disable:4996)

using namespace std;
struct Side {
	char name;
	double ax, ay, bx, by;
};
struct Line {
	double x, deltax;
	double ymax;
};
typedef struct LinkList {
	Line Element;
	LinkList* next;
}LinkList;

void read_data(string file, Side S[]);
vector<string> split(const string& str, const string& delim);
void exchange(Side& S, Line* L);
void Yminmax(Side S[], double& ymin, double& ymax);
void saomiao(Side S[]);
LinkList* List_init();
void CreatList(LinkList* HeadNode, Line Element);
void NextLine(LinkList* a, LinkList* b);
void MaxPoint(Side S[]);
void DrawPix(int a, int b, int y);

int main() {
	Side s[NUM];
	string file = "data.txt";
	read_data(file, s);
	saomiao(s);
	system("pause");
}

void DrawPix(int a, int b, int y) {
	for (; a <= b; a++) {
		putpixel(a,y, BLACK);
		//putpixel(1, 1, BLACK);
		cout << a << " " << y << "\t";
	}
}
void MaxPoint(Side S[]) {
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			if (S[i].ax == S[j].bx && S[i].ay == S[j].by) {
				S[j].by -= 0.0001;
			}
		}
	}
}

void CreatList(LinkList* HeadNode, Line* Element) {
	LinkList* CurrentNode = (LinkList*)HeadNode;
	while (CurrentNode->next != NULL && CurrentNode->next->Element.x < Element->x) {
		CurrentNode = CurrentNode->next;
	}
	LinkList* n = (LinkList*)malloc(sizeof(LinkList));
	n->Element = *Element;
	n->next = CurrentNode->next;
	CurrentNode->next = n;
}

LinkList* List_init() {
	LinkList* HeadNode = (LinkList*)malloc(sizeof(LinkList));
	if (HeadNode == NULL) {
		printf("空间缓存不足");
		return HeadNode;
	}
	HeadNode->Element.x = -9999;
	HeadNode->next = NULL;
	return HeadNode;
}

void saomiao(Side S[]) {
	double ymin=0, ymax=0;
	Line L;
	Yminmax(S, ymin, ymax);
	int len = ymax - ymin;
	LinkList** range = new LinkList*[int(ymax - ymin)];
	for (int i = ymin; i <= ymax; i++) {
		LinkList* HeadNode;
		HeadNode = List_init();
		range[int(i - ymin)] = HeadNode;
		for (int j = 0; j < NUM; j++) {
			if (S[j].ay == i) {
				exchange(S[j], &L);
				CreatList(HeadNode, &L);
			}
		}
	}
	int i, j, driver = VGA, mode = VGAHI;
	initgraph(WIDTH, HEIGH);
	setbkcolor(WHITE);
	bar(0, 0, WIDTH, HEIGH);
	for (int i = 0; i < ymax - ymin; i++) {
		LinkList* a = range[i]->next, * b = range[i]->next;
		bool TF = true; int x1, x2;
		while (a != NULL) {
			if (TF) {
				x1 = a->Element.x;
				TF = !TF;
			}
			else {
				x2 = a->Element.x;
				DrawPix(x1, x2, i + ymin);
				TF = !TF;
			}
			if (a->Element.ymax >= i + ymin + 1) {
				NextLine(a, b);
				CreatList(range[i + 1], &(b->Element));
			}
			a = a->next;
		}
	}
}
void NextLine(LinkList* a, LinkList* b) {
	b->Element.x = a->Element.x + a->Element.deltax;
	b->Element.deltax = a->Element.deltax;
	b->Element.ymax = a->Element.ymax;
}
void Yminmax(Side S[], double& ymin, double& ymax) {
	ymin = S[0].ay; ymax = S[0].by;
	for (int i = 1; i < NUM; i++) {
		if (ymin > S[i].ay) ymin = S[i].ay;
		if (ymax < S[i].by) ymax = S[i].by;
	}
}

void exchange(Side& S, Line* L) {
	double a;
	double x, y;
	x = S.ax - S.bx;
	y = S.ay - S.by;
	if (x == 0) {
		a = 0;
	}
	else {
		a = 1.0 * x / y;
	}
	L->deltax = a;
	L->ymax = S.by;
	L->x = S.ax;
}

void read_data(string file, Side S[]) {
	string Str;
	vector<string> one_data;
	fstream input(file.c_str());
	if (!input.is_open()) {
		cout << "file is error!" << endl;
	}
	for (int i = 0; i < NUM; i++) {
		input >> Str;
		one_data = split(Str, ",");
		strcpy(&S[i].name, one_data[0].c_str());
		S[i].ax = strtod(one_data[1].c_str(), NULL);
		S[i].ay = strtod(one_data[2].c_str(), NULL);
		S[i].bx = strtod(one_data[3].c_str(), NULL);
		S[i].by = strtod(one_data[4].c_str(), NULL);
		if (S[i].ay > S[i].by) {
			int a = S[i].ay;
			S[i].ay = S[i].by;
			S[i].by = a;
			int b = S[i].ax;
			S[i].ax = S[i].bx;
			S[i].bx = b;
		}
	}
	MaxPoint(S);
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型  
	char* strs = new char[str.length() + 1];
	strcpy(strs, str.c_str());
	char* d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
	char* p = strtok(strs, d);
	while (p) {
		string s = p; //分割得到的字符串转换为string类型  
		res.push_back(s); //存入结果数组  
		p = strtok(NULL, d); 
	}
	delete[] strs;
	return res;
}
