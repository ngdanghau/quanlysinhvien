#include "sinhvien.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
/*
* — Cau truc Danh Sach Lop —
*/

struct NodeLop{
	char MALOP[15];
	NodeLop *next;
};
typedef NodeLop *DSLOPPTR;


/*
* === END ===
*/

void Initialize_LH(DSLOPPTR &ListLop);
int DeleteInfo_LH(DSLOPPTR &ListLop, char *malh);
void ClearList_LH(DSLOPPTR &ListLop);
int Reccount_LH(DSLOPPTR &ListLop);
void Traverse_LH(DSLOPPTR ListLop);
DSLOPPTR Search_LH(DSLOPPTR ListLop, char *malh);
void Insert_Last_LH(DSLOPPTR &ListLop, char *malh);
void Load_LopHoc();
void PrintDataLopHoc();

