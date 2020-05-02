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
* — Nhung Ham Xu Ly Chinh —
*/
void ClearRemainMonHoc(int total, int pointX, int pointY, int currentPage);
void CountHeaderMonHocTable(int pointX, int pointY);
void CoutNodeMH(MonHoc p, int stt, int pointX, int pointY);
void ClearTableMonHoc(int is_clear_title);

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
void DrawBoderThemMonHoc(std::string title);
int ThemMonHoc(TREE &DSMH, std::string state);
/*
* === END ===
*/






/*
* — Cau truc Danh Sach Lop —
*/

struct NodeLop{
	char MALOP[15];
	NodeLop *next;
};
typedef NodeLop *DSLOPPTR;


void Initialize_LH(DSLOPPTR &ListLop);
int DeleteInfo_LH(DSLOPPTR &ListLop, char *malh);
void ClearList_LH(DSLOPPTR &ListLop);
int Reccount_LH(DSLOPPTR &ListLop);
void Traverse_LH(DSLOPPTR ListLop, int &stt, std::string keyword, int x, int y, std::string state);
DSLOPPTR Search_LH(DSLOPPTR ListLop, char *malh);
DSLOPPTR Search_LH_By_STT(DSLOPPTR ListLop, std::string keyword, int select);
void Insert_Last_LH(DSLOPPTR &ListLop, char *malh);
void Load_SinhVien();

void DrawCharArrow(int select, int total);
void ClearAutoComplete(int pointX, int pointY, int height);
void DrawBorderChonLopHoc(int &pointX, int &pointY, int &col1, int &height, int &width);
void DrawChonLopHoc(std::string state);
void DrawAutoComplete(int x, int y, int height);
void DrawBorderSearch(int &pointX, int &pointY);


/*
* === END ===
*/



/*
* — Cau truc Danh Sach Sinh Vien —
*/
struct SinhVien{
	char MASV[15]; //Ma SInh Vien
	char HO[30]; //Ho Va Ten Lot
	char TEN[10]; //Ten
	int PHAI;
	char SODT[15]; // So Dien Thoai
	char MALOP[15];
};

struct NodeSV
{
	SinhVien SV;
    NodeSV *next;
};

typedef NodeSV* LISTSV;

/*
* — Ham xu ly Cau truc sinh vien . Danh sach lien ket don —
*/
void Initialize_SV(LISTSV& First);
int Reccount_SV(LISTSV &First, char *malophoc);
int Reccount_SV_With_Keyword(LISTSV &First, char *malophoc, std::string keyword);
LISTSV Check_Is_New_Class(LISTSV First, char *malophoc);
LISTSV Search_Info_SV(LISTSV First, SinhVien x);
int Delete_Info_SV(LISTSV& First, SinhVien x);
void ClearListSV(LISTSV& First);
void Traverse_SV(LISTSV First, char *malophoc, int &stt, int &pointX, int pointY, int currentPage, std::string &keyword, LISTSV *pages);
void Selection_Sort_SV(LISTSV& First, char *malophoc);
void Insert_Last_SV(LISTSV &First, SinhVien x);

void ClearRemainSinhVien(int total, int pointX, int pointY, int currentPage);
void CountHeaderSinhVienTable(int pointX, int pointY);
void CoutNodeSV(SinhVien p, int stt, int pointX, int pointY);
void ClearTableSinhVien(int is_clear_title);
void DrawBoderThemSinhVien(std::string title, char *malophoc);
int ThemSinhVien(LISTSV &First, std::string state, char *malophoc, int is_new_class);
void DrawTableSinhVien(char *malophoc);
void PrintDataSinhVien(LISTSV &First, int tab, std::string state, char *malophoc, int is_new_class);
void CreateSinhVien(LISTSV &First, char *malophoc, int is_new_class, std::string state);
void DrawInputGenger(int pointX, int pointY, int gender);

/*
* === END ===
*/

void LoadAllDataFromFile();
