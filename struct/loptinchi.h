#include <iostream>
#include <string>

#define MAXLOPTINCHI 10000
/*
* — Cau truc Danh Sach Lop Tin Chi —
*/

struct LopTinChi{
	unsigned int MALOPTC; // Ma lop Tin Chi
	char MAMH[10]; //Ma Mon Hoc
	int NIENKHOA; //Nien Khoa
	int HOCKY; //Hoc Ky (1 hoac 2 hoac 3)
	int NHOM; //Nhom
	int MINSV; //So Sinh Vien Toi Thieu
	int MAXSV; //So Sinh Vien Toi Da
	bool HUYLOP; //(true= Giu lop; false= xoa lop)
	LISTDK DSDK;
	LopTinChi() { static int id = 0; MALOPTC = id++; }
};

struct DSLOPTINCHI{
	unsigned int N;
	LopTinChi *LOP[MAXLOPTINCHI];
};

/*
* === END ===
*/

