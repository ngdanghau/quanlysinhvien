#include <iostream>
/*
* — Cau truc Danh Sach Sinh Vien —
*/
struct SinhVien{
	char MASV[15]; //Ma SInh Vien
	char HO[30]; //Ho Va Ten Lot
	char TEN[10]; //Ten
	char PHAI[4]; //(Nam,Nu hoac Khac)
	char SODT[15]; // So Dien Thoai
	char MALOP[15];
};

struct NodeSV
{
	SinhVien SV;
    struct DSSV *next;
};

typedef NodeSV* LISTSV;


/*
* === END ===
*/

void test();
