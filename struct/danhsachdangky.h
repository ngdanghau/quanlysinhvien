#include <iostream>
#include <string>
/*
* — Cau truc Danh Sach Dang Ky —
*/

struct DANGKY{
	char MASV[15];
	float DIEM;
	
};
struct NodeDK{
	DANGKY SV;
	NodeDK *Next;
};
typedef NodeDK* LISTDK;

/*
* === END ===
*/


