#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <conio.h>

#define MAXLOPTINCHI 10000
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
* — Cau truc Danh Sach Dang Ky —
*/

struct DANGKY{
	char MASV[15];
	float DIEM;
	
};
struct NodeDK{
	DANGKY SV;
	NodeDK *next;
};
typedef NodeDK* LISTDK;


/*
* — Cau truc Danh Sach Lop Tin Chi —
*/

struct LopTinChi{
	unsigned int MALOPTC; // Ma lop Tin Chi
	char MAMH[10]; //Ma Mon Hoc
	char NIENKHOA[15]; //Nien Khoa
	int HOCKY; //Hoc Ky (1 hoac 2 hoac 3)
	int NHOM; //Nhom
	int MINSV; //So Sinh Vien Toi Thieu
	int MAXSV; //So Sinh Vien Toi Da
	bool HUYLOP; //(true= Giu lop; false= xoa lop)
	LISTDK DSDK;
	LopTinChi() { static int id = 1; MALOPTC = id++; }
};

struct DSLOPTINCHI{
	unsigned int N;
	LopTinChi *LOP[MAXLOPTINCHI];
};


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
* — Cau truc Danh Sach Lop —
*/

struct NodeLop{
	char MALOP[15];
	NodeLop *next;
};
typedef NodeLop *DSLOPPTR;


/*
* — Ham xu ly Cau truc sinh vien —
*/
void Initialize_SV(LISTSV &First);
int Reccount_SV(LISTSV First, char *malophoc);
int Reccount_SV_With_Keyword(LISTSV First, char *malophoc, std::string keyword);
LISTSV Check_Is_New_Class(LISTSV First, char *malophoc);
LISTSV Search_Info_SV(LISTSV First, SinhVien x);
LISTSV Search_Info_SV_By_STT(LISTSV First, char *malophoc, std::string keyword, int select, int currentPage, LISTSV *pages);
int Delete_Info_SV(LISTSV &First, SinhVien x);
void ClearListSV(LISTSV &First);
void Traverse_SV(LISTSV First, char *malophoc, int &stt, int &pointX, int pointY, int currentPage, std::string &keyword, LISTSV *pages);
void Selection_Sort_SV(LISTSV &First, char *malophoc);
void Insert_Last_SV(LISTSV &First, SinhVien x);

void ClearRemainSinhVien(int total, int pointX, int pointY);
void CountHeaderSinhVienTable(int pointX, int pointY);
void CoutNodeSV(SinhVien p, int stt, int pointX, int pointY);
void DrawBoderThemSinhVien(std::string title, char *malophoc);
int ThemSinhVien(LISTSV &First, std::string state, char *malophoc, int is_new_class, LISTSV p);
void DrawTableSinhVien(char *malophoc, int is_draw_title);
void PrintDataSinhVien(LISTSV &First, int tab, std::string state, char *malophoc, int is_new_class);
void DrawInputGenger(int pointX, int pointY, int gender);

/*
* === END ===
*/





/*
* — Ham xu ly Danh Sach Dang Ky —
*/
int CheckExist_SV(LISTDK First, char *masinhvien);
int Reccount_DK(LISTDK First);
int Reccount_DK_WITH_ADD_SV(LISTDK First, LISTSV &DSSV);
void Initialize_DK(LISTDK& First);
void ClearListDK(LISTDK& First);
void Insert_Last_DK(LISTDK &First, DANGKY x);
int Delete_Info_DK(LISTDK &First, char *masinhvien);
void Create_DangKy(LISTDK &First, char *filename);
void SaveFileListDK(LISTDK &First, int index);

/*
* === END ===
*/


/*
* — Ham xu ly Danh Sach Lop Tin Chi —
*/
void ClearRemainLopTinChiPlus(int total, int pointX, int pointY, int index, int *list_dk, int n2);
void ClearRemainLopTinChi(int total, int pointX, int pointY);
void CountHeaderLopTinChiTable(int pointX, int pointY);
void CountHeaderLopTinChiTablePlus(int pointX, int pointY);
void CoutNodeLopTinChi(LopTinChi *ltc, int stt, int pointX, int pointY);
void DrawBoderThemLopTinChi(std::string title);
int ThemLopTinChi(DSLOPTINCHI &plist, std::string state, int check, TREE p);
void DrawTableLopTinChiPlus();
void DrawTableLopTinChi(int is_draw_title, int tab);

void Load_Into_Temp(DSLOPTINCHI dsloptc, DSLOPTINCHI &dsltc_temp, char *nienkhoa, int hocky);
void Huy_LopTinChi(DSLOPTINCHI &plist, char *nienkhoa, int hocky);
void Traverse_LTC(DSLOPTINCHI plist, int &pointX, int pointY, int currentPage, int &stt, std::string keyword, int &total);
void Traverse_LTC_Plus(DSLOPTINCHI plist, int &pointX, int pointY, int currentPage, int &stt, std::string keyword, int &total, int *list_dk, int n);
void Delete_Item_LopTC(DSLOPTINCHI &plist, int i);
int Search_Info_LTC(DSLOPTINCHI plist, int maloptc);
int Search_Info_LTC_By_STT(DSLOPTINCHI plist, std::string &keyword, int currentPage, int select);
int Search_Info_LTC_BY_MALOPHOC(DSLOPTINCHI plist, char *mamonhoc, int nhom, int hocky, char *nienkhoa);
void ClearList_LopTC(DSLOPTINCHI &plist);
void PrintDataLopTC(int tab, std::string state);
void SaveFileLopTC();
void Load_LopTC();
void ClearBoderHuyLopTinChi(int type);
void DrawBoderHuyLopTinChi();
void HuyLopTinChi();
void DrawTableLopTCEx();
int DrawTableMonHocEx(TREE &p);
void DrawTableSinhVienEx(LISTDK &First);
void DrawBoderInputHuyLopTC();
/*
* === END ===
*/


/*
* — Nhung Ham Xu Ly Mon Hoc —
*/
void ClearRemainMonHoc(int total, int pointX, int pointY, int currentPage);
void CountHeaderMonHocTable(int pointX, int pointY);
void CoutNodeMH(MonHoc p, int stt, int pointX, int pointY);

void InitializeTree(TREE &root);
int ReccountTree(TREE root);
int Reccount_MH_With_Keyword(TREE root, std::string &keyword);
TREE Rotate_Left(TREE root);
TREE Rotate_Right(TREE ya);
void Insert_Node(TREE &p, MonHoc x);
void Insert_Last_DSMH(TREE &DSMH, MonHoc x);
void Inorder(TREE p, TREE &DSMH);
void Traverse_DSMH(TREE DSMH, int &stt, int &pointX, int pointY, int currentPage, std::string &keyword, TREE *pages);
TREE Search_By_STT_DSMH(TREE DSMH, int select, int currentPage, std::string &keyword, TREE *pages);
TREE MinimumNodeMH(TREE curr);
TREE DeleteMH(TREE& root, char* mamh);
int DeleteMH_DSMH(TREE &DSMH, char *mamh);
void Selection_Sort_DSMH(TREE& DSMH);
void DeleteAllTree ( TREE &DSMH);
TREE SearchNodeMH(TREE root, char *mamh);
void InorderFile(TREE p, std::ofstream &outfile);
void SaveFileMonHoc();
void Load_MonHoc();

void DrawTableMonHoc(int is_draw_title);
void PrintDataMonHoc(int tab, std::string state);
void DrawBoderThemMonHoc(std::string title);
int ThemMonHoc(TREE &DSMH, std::string state, TREE p);

void LoadLopTCDaDK(DSLOPTINCHI dsloptc, int *list_dk, int &n2, char* masinhvien);
void DrawTableLopTCPlus(DSLOPTINCHI &dsltc_temp, char *nienkhoa, int hocky, char* masinhvien);
void DrawBorderNhap(int pointX, int pointY);
void DrawInfoSinhVien(int pointX, int pointY, SinhVien sv);
void DrawNhapNienKhoaHocKy(int pointX, int pointY);
void DrawNhapMaSinhVien();
/*
* === END ===
*/



/*
* — Nhung Ham Xu Ly Lop Hoc —
*/
void Initialize_LH(DSLOPPTR &ListLop);
int DeleteInfo_LH(DSLOPPTR &ListLop, char *malh);
void ClearList_LH(DSLOPPTR &ListLop);
int Reccount_LH(DSLOPPTR ListLop);
int Reccount_LH_With_Keyword(DSLOPPTR ListLop, std::string keyword);
void Selection_Sort_LH(DSLOPPTR& ListLop);
void Traverse_LH(DSLOPPTR ListLop, int &stt, int pointX, int pointY, int currentPage, std::string keyword, DSLOPPTR *pages);
DSLOPPTR Search_LH(DSLOPPTR ListLop, char *malh);
DSLOPPTR Search_LH_By_STT(DSLOPPTR ListLop, std::string keyword, int currentPage, int select, DSLOPPTR *pages);
void Insert_Last_LH(DSLOPPTR &ListLop, char *malh);
void SaveFileSinhVien();
void Load_SinhVien();

void ClearRemainLopHoc(int total, int pointX, int pointY);
void DrawCharArrow(int select, int total);
void PrintDataLopHoc(std::string state);
void DrawTableLopHoc(int &pointX, int &pointY);


/*
* === END ===
*/






void LoadAllDataFromFile();
void ClearListAll();
