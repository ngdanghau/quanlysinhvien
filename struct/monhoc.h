#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <conio.h>
/*
* — Cau truc Danh Sach Mon Hoc —
*/
struct MonHoc{
	char MAMH[10]; //Ma Mon Hoc
	char TENMH[50]; //ten Mon Hoc
	unsigned int STCLT;   // So TC Ly Thuyet
	unsigned int STCTH;   // So Tc Thuc Hanh
	
};

struct NodeMH{
	MonHoc MH;
	int bf;
	NodeMH *left, *right;
};


typedef NodeMH* TREE;
/*
* === END ===
*/


/*
* — Nhung Ham Xu Ly Chinh —
*/
void ClearRemainMonHoc(int total, int pointX, int pointY, int currentPage);
void CountHeaderMonHocTable(int pointX, int pointY);
void CoutNodeMH(MonHoc p, int stt, int pointX, int pointY);
void PrintPageMonHoc( int currentPage, int totalPage);
void ClearTableMonHoc(int is_clear_title);
void ClearInputThemMonHoc(int x, int y);
int InputMonHoc(std::string &keyword, int &x, int &y, int type);
int InputSearchMonHoc(std::string &keyword, int &x, int &y);
void PrintKeyWord(std::string keyword, int &x, int &y);
void PrintSearchInput(std::string keyword);
void DrawTitleYesNoMH(int select, std::string state);
void DrawButtonYesNoMH(std::string state);
void ClearButtonYesNoMH();

void InitializeTree(TREE &root);
int ReccountTree(TREE root);
TREE Rotate_Left(TREE root);
TREE Rotate_Right(TREE ya);
void Insert_Node(TREE &p, MonHoc x);
void Insert_Last_DSMH(TREE &DSMH, MonHoc x);
void Inorder(TREE p, TREE &DSMH);
void Traverse_DSMH(TREE DSMH, int &stt, int &pointX, int pointY, int currentPage, std::string &keyword);
TREE MinimumNodeMH(TREE curr);
TREE DeleteMH(TREE& root, char* mamh);
int DeleteMH_DSMH(TREE &DSMH, char *mamh);
void Selection_Sort_DSMH(TREE& DSMH);
TREE SearchNodeMH(TREE root, char *mamh);
void Load_MonHoc();

void DrawTableMonHoc();
void PrintDataMonHoc(int tab, std::string state);
void DrawTitleMonHoc(char *title, int x);
void DrawBoderThemMonHoc(std::string title);
void DrawInputThemMonHoc( int pointX, int pointY);
int ThemMonHoc(TREE &DSMH, std::string state);
void DrawHuongDanTableMonHoc(int pointX, int pointY);
void DrawTitleTableMonHoc(int pointX, int pointY, int select);
/*
* === END ===
*/

