#include "structs.h"
#include "../constant.h"
#include "../mylib/console.h"
#include "../mylib/helpers.h"
/*
* — Khai bao bien toan cuc —
*/
TREE tree = NULL;
DSLOPPTR ListLop = NULL;
LISTSV First = NULL;
DSLOPTINCHI dsloptc;
/*
* === END ===
*/

using namespace std;

/*
* — Tieu De Cho Chuc Nang Lop Tin Chi —
*/
const int NUMBER_ITEM_DANGSACHDANGKYTEXT = 3;
const int NUMBER_ITEM_DANGSACHDANGKY_FUNCTION_TEXT = 5;
char DanhSachDangKyText[NUMBER_ITEM_DANGSACHDANGKYTEXT][MENU_TEXT_LENGTH] = {
		"BANG DANH SACH DANG KY",
		" MO DS DANG KY ",
		" BANG DS LOP TC "
};

char DanhSachDangKyFunctionText[2][NUMBER_ITEM_DANGSACHDANGKY_FUNCTION_TEXT][30] = {
		{
			"ENTER",
			"CTR+F",
			"ESC",
			"TAB",
			"INSERT"
		},
		{
			": Xac Nhan",
			": Tim Kiem",
			": Thoat",
			": LTC Da DK",
			": Luu Ket Qua"
		}
};
/*
* === END ===
*/


/*
* — Tieu De Cho Chuc Nang Sinh Vien —
*/
const int NUMBER_ITEM_SINHVIENTEXT = 6;
const int NUMBER_ITEM_SINHVIEN_FUNCTION_TEXT = 5;

char SinhVienText[4][MENU_TEXT_LENGTH] = {
		"BANG DANH SACH CAC SINH VIEN",
		" BANG DANH SACH ",
		" THEM MOI/CHINH SUA ",
		"THEM SINH VIEN MOI"
};

char ThemSinhVienText[NUMBER_ITEM_SINHVIENTEXT][MENU_TEXT_LENGTH] = {
		"MA SINH VIEN: ",
		"HO SV: ",
		"TEN SV:",
		"MA LOP: ",
		"PHAI: ",
		"SDT:"
};

char SinhVienFunctionText[2][NUMBER_ITEM_SINHVIEN_FUNCTION_TEXT][30] = {
		{
			"TAB",
			"CTR+F",
			"DEL",
			"INSERT",
			"ENTER"
		},
		{
			": Chuyen Tab",
			": Tim Kiem",
			": Xoa",
			": Them",
			": Xac Nhan"
		}
};
/*
* === END ===
*/



/*
* — Tieu De Cho Chuc Nang Lop Tin Chi —
*/
const int NUMBER_ITEM_LOPTINCHITEXT = 6;
char LopTinChiText[NUMBER_ITEM_LOPTINCHITEXT][MENU_TEXT_LENGTH] = {
		"BANG DANH SACH LOP TIN CHI",
		" BANG DANH SACH ",
		" THEM MOI/CHINH SUA "
};

char ThemLopTinChiText[NUMBER_ITEM_LOPTINCHITEXT][MENU_TEXT_LENGTH] = {
		"MA MON HOC: ",
		"NIEN KHOA: ",
		"HOC KY: ",
		"NHOM: ",
		"SO SINH VIEN MIN: ",
		"SO SINH VIEN MAX: "
};

const int NUMBER_ITEM_LOPTINCHI_FUNCTION_TEXT = 5;
char LopTinChiFunctionText[2][NUMBER_ITEM_LOPTINCHI_FUNCTION_TEXT][30] = {
		{
			"TAB",
			"CTR+F",
			"DEL",
			"INSERT",
			"ENTER"
		},
		{
			": Chuyen Tab",
			": Tim Kiem",
			": Xoa",
			": Them",
			": Xac Nhan"
		}
};
/*
* === END ===
*/


/*
* — Tieu De Cho Chuc Nang Mon Hoc —
*/
const int NUMBER_ITEM_MONHOCTEXT = 4;
char MonHocText[NUMBER_ITEM_MONHOCTEXT][MENU_TEXT_LENGTH] = {
		"BANG DANH SACH CAC MON HOC",
		" BANG DANH SACH ",
		" THEM MOI/CHINH SUA ",
		"THEM MON HOC MOI"
};

char ThemMonHocText[NUMBER_ITEM_MONHOCTEXT][MENU_TEXT_LENGTH] = {
		"MA MON HOC: ",
		"TEN MON HOC: ",
		"SO TC LY THUYET:",
		"SO TC THUC HANH:"
};

char DangKyMonHocText[NUMBER_ITEM_MONHOCTEXT][MENU_TEXT_LENGTH] = {
		"BANG DANH SACH CAC MON HOC",
		"   THONG TIN SINH VIEN   ",
		"   DS MON HOC DA DK   ",
		"THEM MON HOC MOI"
};

const int NUMBER_ITEM_MONHOC_FUNCTION_TEXT = 5;
char MonHocFunctionText[2][NUMBER_ITEM_MONHOC_FUNCTION_TEXT][30] = {
		{
			"TAB",
			"CTR+F",
			"DEL",
			"INSERT",
			"ENTER"
		},
		{
			": Chuyen Tab",
			": Tim Kiem",
			": Xoa",
			": Them",
			": Xac Nhan"
		}
};
/*
* === END ===
*/



/*
* — Ham Xu Lu Cho Danh Sach Dang Ky —
*/

void Initialize_DK(LISTDK& First){
    First = NULL;
}

int CheckExist_SV(LISTDK First, char *masinhvien){
	if(First == NULL) return 0;
	LISTDK p = First;
	while(p != NULL){
		if(strcmp(p->SV.MASV, masinhvien) == 0) return 1;
		p = p->next;
	}
}

int Reccount_DK(LISTDK First) {
	if(First == NULL) return 0;
	
	int count = 0;
	LISTDK p = First;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

int Reccount_DK_WITH_ADD_SV(LISTDK FirstDK, LISTSV &DSSV) {
	if(FirstDK == NULL) return 0;
	
	int count = 0;
	LISTDK p = FirstDK;
	SinhVien x;
	while(p != NULL){
		strcpy(x.MASV, p->SV.MASV);
		Insert_Last_SV(DSSV , Search_Info_SV(First, x)->SV);
		count++;
		p = p->next;
	}
	return count;
}

void ClearListDK(LISTDK& First){
    LISTDK p;
    while (First != NULL)
    {
        p = First;
        First = First->next;
        delete p;
    }
}

void Insert_Last_DK(LISTDK &First, DANGKY x){
    LISTDK p = new NodeDK;
    p->SV = x;
    p->next = NULL;
      
    if(First == NULL) 
		First = p;
    else{
      	LISTDK Last = First;
      	for(; Last->next != NULL; Last = Last->next);
      	Last->next = p;
	}
}

void Create_DangKy(LISTDK &First, char *filename){
	DANGKY x;
  	ifstream file(filename);
	
	if (!file.is_open()) return;
	
	string temp;
	while (!file.eof())
	{
		file >> temp;
		if(temp == "\n" || temp == "") break;
		file >> x.DIEM;
		strcpy(x.MASV, temp.c_str());
		Insert_Last_DK(First, x);
		temp = "";
	}
	file.close();
}

int Delete_Info_DK(LISTDK &First, DANGKY x){
	LISTDK q, p = First;
    if (First == NULL)
        return 0;
    if ( strcmp(First->SV.MASV, x.MASV ) == 0)
    {
        p = First;
        First = p->next;
        delete p;
        return 1;
    }

    for (p = First; p->next != NULL && strcmp(p->next->SV.MASV, x.MASV  ) != 0; p = p->next);
    if (p->next != NULL)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        return 1;
    }
    return 0;
}

void SaveFileListDK(LISTDK &First, int index){
	string filename = "data\\DSDK\\"  + ConvertIntToString(index) + ".TXT";
	
	ofstream outfile;
    outfile.open(filename.c_str(), ios::out );
    
    if(First == NULL) {
    	
    	// xoa file
    	return;
	}
    LISTDK p = First;
	while(p != NULL){
    	outfile << p->SV.MASV << "\t" << p->SV.DIEM << "\n";
    	p = p->next;
	}	
    outfile.close();
}
/*
* === END ===
*/





/*
* — Ham Xu Lu Cho Lop Tin Chi —
*/

void Load_Into_Temp(DSLOPTINCHI dsloptc, DSLOPTINCHI &dsltc_temp, char *nienkhoa, int hocky){
	int count = 0;
	for(int i = 0; i < dsloptc.N; i++){
		if(strcmp(dsloptc.LOP[i]->NIENKHOA, nienkhoa) == 0 && dsloptc.LOP[i]->HOCKY == hocky){
			dsltc_temp.LOP[count] = dsloptc.LOP[i];
			count++;
		}
	}
	dsltc_temp.N = count;
}

void ClearRemainLopTinChi(int total, int pointX, int pointY){
	int row2 = 15-total;
	pointY = total*2+pointY;
	for(int i = 0; i < row2;i++){
		GoToXY(pointX, pointY+=2); printf("%-6s", " ");
		GoToXY(pointX + 10, pointY); printf("%-11s", " ");
		GoToXY(pointX + 25, pointY); printf("%-8s", " ");
		GoToXY(pointX + 47, pointY); printf("%-8s", " ");
		GoToXY(pointX + 57, pointY); printf("%-6s", " ");
		GoToXY(pointX + 65, pointY); printf("%-8s", " ");	
		GoToXY(pointX + 75, pointY); printf("%-8s", " ");
		GoToXY(pointX + 85, pointY); printf("%-11s", " ");
	}
}

void ClearRemainLopTinChiPlus(int total, int pointX, int pointY){
	int row2 = 15-total;
	pointY = total*2+pointY;
	for(int i = 0; i < row2;i++){
		GoToXY(pointX, pointY+=2); printf("%-6s", " ");
		GoToXY(pointX + 14, pointY); printf("%-11s", " ");
		GoToXY(pointX + 27, pointY); printf("%-8s", " ");
		GoToXY(pointX + 73, pointY); printf("%-6s", " ");
		GoToXY(pointX + 82, pointY); printf("%-8s", " ");
		GoToXY(pointX + 94, pointY); printf("%-8s", " ");
	}
}

void CountHeaderLopTinChiTable(int pointX, int pointY){
	GoToXY(pointX, pointY); cout << "STT";
	GoToXY(pointX + 10, pointY); cout << "MA MON HOC";
	GoToXY(pointX + 25, pointY); cout << "Nien Khoa";
	GoToXY(pointX + 47, pointY); cout << "Hoc Ky";
	GoToXY(pointX + 57, pointY); cout << "Nhom";
	GoToXY(pointX + 65, pointY); cout << "SV Min";
	GoToXY(pointX + 75, pointY); cout << "SV Max";
	GoToXY(pointX + 85, pointY); cout << "Tinh Trang";
}

void CountHeaderLopTinChiTablePlus(int pointX, int pointY){
	GoToXY(pointX, pointY); cout << "STT";
	GoToXY(pointX + 14, pointY); cout << "MA MON HOC";
	GoToXY(pointX + 27, pointY); cout << "TEN MON HOC";
	GoToXY(pointX + 73, pointY); cout << "NHOM";
	GoToXY(pointX + 82, pointY); cout << "SO SVDK";
	GoToXY(pointX + 94, pointY); cout << "SLOT CL";
}

void CoutNodeLopTinChiPlus(LopTinChi *ltc, int stt, int pointX, int pointY, int index, int *list_dk, int n){
	HideTyping();
	int total = Reccount_DK(ltc->DSDK);
	TREE p = SearchNodeMH(tree, ltc->MAMH);
	
	GoToXY(pointX, pointY); printf("%-7d", stt);
	if(InArray(index, list_dk, n) != -1) {
		cout << char(219)<< char(219)<< char(219);
	}
	GoToXY(pointX + 14, pointY); printf("%-11s", ltc->MAMH);
	GoToXY(pointX + 27, pointY); printf("%-8s", p != NULL ? p->MH.TENMH : "KHONG TIM THAY TEN MON HOC");
	GoToXY(pointX + 73, pointY); printf("%-6d", ltc->NHOM);
	GoToXY(pointX + 82, pointY); printf("%-8d", total);
	GoToXY(pointX + 94, pointY); printf("%-8d", ltc->MAXSV-total);
}

void CoutNodeLopTinChi(LopTinChi *ltc, int stt, int pointX, int pointY){
	HideTyping();
	GoToXY(pointX, pointY); printf("%-7d", stt);
	GoToXY(pointX + 10, pointY); printf("%-11s", ltc->MAMH);
	GoToXY(pointX + 25, pointY); printf("%-8s", ltc->NIENKHOA);
	GoToXY(pointX + 47, pointY); printf("%-8d", ltc->HOCKY);
	GoToXY(pointX + 57, pointY); printf("%-6d", ltc->NHOM);
	GoToXY(pointX + 65, pointY); printf("%-8d", ltc->MINSV);	
	GoToXY(pointX + 75, pointY); printf("%-8d", ltc->MAXSV);
	if(ltc->HUYLOP == FALSE){
		SetColor(GREEN);
		GoToXY(pointX + 85, pointY); printf("%-11s", "DANG MO");
	}else{
		SetColor(RED);
		GoToXY(pointX + 85, pointY); printf("%-11s", "DA HUY");
	}
	SetColor(BLACK);
}

void Traverse_LTC_Plus(DSLOPTINCHI plist, int &pointX, int pointY, int currentPage, int &stt, string keyword, int &total, int *list_dk, int n2){
	int n = (currentPage)*15;
	int m = (currentPage+1)*15;
	if(m > plist.N) m = plist.N; 
	stt = 0;
	if(keyword.length() == 0){
		total = plist.N;
		for(int i = n ; i < m ; i++){
			stt++;
			CoutNodeLopTinChiPlus(plist.LOP[i], (i+1), pointX, pointY+=2, i, list_dk, n2);
		}
		return;
	}
	
	int stt2 = 0;
	for(int i = 0 ; i < plist.N; i++){
		string maloptc = ConvertIntToString(plist.LOP[i]->MALOPTC);
		string mamonhoc = convertToString(plist.LOP[i]->MAMH, strlen(plist.LOP[i]->MAMH));
	   	if(maloptc.find(keyword) != string::npos || mamonhoc.find(keyword) != string::npos ){
	   		stt++;
			if(currentPage*15 < stt && stt < (currentPage+1)*15 +1) {
				stt2++;
				CoutNodeLopTinChiPlus(plist.LOP[i], (i+1), pointX, pointY+=2, i, list_dk, n);
			}
				
		}
	}	
	total = stt;
	stt = stt2;
}

void Traverse_LTC(DSLOPTINCHI plist, int &pointX, int pointY, int currentPage, int &stt, string keyword, int &total){
	int n = (currentPage)*15;
	int m = (currentPage+1)*15;
	if(m > plist.N) m = plist.N; 
	stt = 0;
	if(keyword.length() == 0){
		total = plist.N;
		for(int i = n ; i < m ; i++){
			stt++;
			CoutNodeLopTinChi(plist.LOP[i], (i+1), pointX, pointY+=2);
		}
		return;
	}
	
	int stt2 = 0;
	for(int i = 0 ; i < plist.N; i++){
		string maloptc = ConvertIntToString(plist.LOP[i]->MALOPTC);
		string mamonhoc = convertToString(plist.LOP[i]->MAMH, strlen(plist.LOP[i]->MAMH));
	   	if(maloptc.find(keyword) != string::npos || mamonhoc.find(keyword) != string::npos ){
	   		stt++;
			if(currentPage*15 < stt && stt < (currentPage+1)*15 +1) {
				stt2++;
				CoutNodeLopTinChi(plist.LOP[i], (i+1), pointX, pointY+=2);
			}
				
		}
	}	
	total = stt;
	stt = stt2;
}

void Delete_Item_LopTC(DSLOPTINCHI &plist, int i){
	for(int j = i; j < plist.N ; j++)
		plist.LOP[j-1] = plist.LOP[j];
	plist.N--;
}

void ClearList_LopTC(DSLOPTINCHI &plist){
	for(int i = 0; i < plist.N; i++){
		ClearListDK(plist.LOP[i]->DSDK);
		delete plist.LOP[i];
	}
	plist.N = 0;
	
}

void Huy_LopTinChi(DSLOPTINCHI &plist, char *nienkhoa, int hocky){
	for(int i = 0; i < plist.N;i++){
		if(Reccount_DK(plist.LOP[i]->DSDK) < plist.LOP[i]->MINSV && strcmp(plist.LOP[i]->NIENKHOA, nienkhoa) == 0 && plist.LOP[i]->HOCKY == hocky){
			plist.LOP[i]->HUYLOP = TRUE;
		}
	}
}

int Search_Info_LTC(DSLOPTINCHI plist, int maloptc){
	for ( int i = 0 ; i < plist.N ; i++)
  	     if (plist.LOP[i]->MALOPTC == maloptc) return i;
	return -1;
}

int Search_Info_LTC_By_STT(DSLOPTINCHI plist, string &keyword, int currentPage, int select){
	int n = (currentPage)*15;
	int m = (currentPage+1)*15;
	if(m > plist.N) m = plist.N; 
	
	int  j = 0;
	for ( int i = n ; i < m ; i++){
		string maloptc = ConvertIntToString(plist.LOP[i]->MALOPTC);
		string mamonhoc = convertToString(plist.LOP[i]->MAMH, strlen(plist.LOP[i]->MAMH));
	   	if(maloptc.find(keyword) != string::npos || mamonhoc.find(keyword) != string::npos ){
		   	if (j == select) return i;
			j++;
		}
	}
	return -1;
}

int Search_Info_LTC_BY_MALOPHOC(DSLOPTINCHI plist, char *mamonhoc, int nhom, int hocky, char *nienkhoa){
	for ( int i = 0 ; i < plist.N ; i++)
  	     if ( strcmp(plist.LOP[i]->MAMH, mamonhoc) == 0 && strcmp(plist.LOP[i]->NIENKHOA, nienkhoa) == 0 && plist.LOP[i]->HOCKY == hocky && plist.LOP[i]->NHOM == nhom ) return i;
	return -1;
}

void DrawBoderThemLopTinChi(string title){
	int pointX = 55, pointY = 5, width = 90, height = 30;
	
	SetColor(RED);
	GoToXY(pointX+30, pointY+1);
	printf("%-50s", title.c_str());
	SetColor(BLACK);
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	strcpy(LopTinChiFunctionText[1][1], ": Chon Mon Hoc");
	DrawTitleFunction(pointX+5, pointY+29, LopTinChiFunctionText, NUMBER_ITEM_LOPTINCHI_FUNCTION_TEXT, 0);
	
	for(int i = 0; i < NUMBER_ITEM_LOPTINCHITEXT; i++){
		GoToXY(pointX+5, pointY+3+i*4);
		printf("%-30s", ThemLopTinChiText[i]);
		DrawInput(85, pointY+2+i*4);
	}
	
	
	GoToXY(87, 8);
	Typing();

}

int ThemLopTinChi(DSLOPTINCHI &plist, string state, int check, TREE p){
	HideTyping();
	MonHoc mh;
	int x = 87, y = 8;
	string temp = "";
	int c, type = 2, index = 0, is_delete = 0, length = 50;;
	int maloptc, hocky, nhom, maxsv, minsv;
	char mamonhoc[10];
	char nienkhoa[15];
	
	if(state == "NEW"){
		DrawBoderThemLopTinChi("NHAP THONG TIN DE THEM LOP TIN CHI MOI!");
		if(p != NULL){
			y+=4, type = 2, length = 11;
			strcpy(mamonhoc, p->MH.MAMH);
			temp = p->MH.MAMH;
		}
	}else if(state == "EDIT"){
		DrawBoderThemLopTinChi("NHAP MA LOP TIN CHI DE CHINH SUA!");
		if(check != -1){
			DrawButtonYesNo(30, state);
	
			GoToXY(x, y);
			SetColor(BLACK);
			printf("%-50s", plist.LOP[check]->MAMH);
			strcpy(mamonhoc, plist.LOP[check]->MAMH);
	
							
			GoToXY(x, y+=4);
			printf("%-50s", plist.LOP[check]->NIENKHOA);
			strcpy(nienkhoa, plist.LOP[check]->NIENKHOA);
						
			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->HOCKY);
			hocky = plist.LOP[check]->HOCKY;

			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->NHOM);
			nhom = plist.LOP[check]->NHOM;
						
			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->MINSV);
			minsv = plist.LOP[check]->MINSV;
						
			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->MAXSV);
			maxsv = plist.LOP[check]->MAXSV;
								
			y = y-20, type = 0, index++;
			temp = plist.LOP[check]->MAMH;
			length = 15;
		}
	}else if(state == "DELETE"){
		DrawBoderThemLopTinChi("NHAP MA LOP TIN CHI DE XOA!");
		if(check != -1){
			DrawButtonYesNo(30, state);
			
			SetColor(RED);
			GoToXY(x, y);
			printf("%-50s", plist.LOP[check]->MAMH);
			strcpy(mamonhoc, plist.LOP[check]->MAMH);
							
			GoToXY(x, y+=4);
			printf("%-50s", plist.LOP[check]->NIENKHOA);
			strcpy(nienkhoa, plist.LOP[check]->NIENKHOA);
						
			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->HOCKY);
			hocky = plist.LOP[check]->HOCKY;

			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->NHOM);
			nhom = plist.LOP[check]->NHOM;
						
			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->MINSV);
			minsv = plist.LOP[check]->MINSV;
						
			GoToXY(x, y+=4);
			printf("%-50d", plist.LOP[check]->MAXSV);
			maxsv = plist.LOP[check]->MAXSV;
			
			type = 4, index = 7;
			DrawTitleYesNo(31, is_delete, state);
			temp = "DELETE";
			SetColor(BLACK);
		}
	}

	
	if(state == "NEW"){
		type = 0;
		do{
			c = InputValue(length, temp, x, y, type);
			switch (c) {
			    case EX_DEL:
				case TAB:
			        return c;
			    case CTRL_F:
			    	DrawTableMonHocEx(p);
			    	DrawBoderThemLopTinChi("NHAP THONG TIN DE THEM LOP TIN CHI MOI!");
			    	if(p != NULL){
						strcpy(mamonhoc, p->MH.MAMH);
						temp = p->MH.MAMH;
						PrintKeyWord("%-18s", temp, x, y);
					}
			    	break;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
					if(index == 0){
						strcpy(mamonhoc, temp.c_str());
						if( p == NULL || (p != NULL && strcmp(mamonhoc, p->MH.MAMH) != 0)){
							p = SearchNodeMH(tree, mamonhoc);
							if(p == NULL){
								Message("ERROR:", "Ma Mon Hoc Khong Ton Tai!", 0, 1000);
								GoToXY(x+temp.length(), y);
								break;
							}
						}
						y+=4, type = 7, length = 11;
					}else if(index == 1){
						y+=4;
						strcpy(nienkhoa, temp.c_str());
						type = 6, length = 1;
					}else if(index == 2){
						y+=4;
						sscanf(temp.c_str(), "%d", &hocky);
						type = 0;
					}else if(index == 3){
						sscanf(temp.c_str(), "%d", &nhom);
						int check2 = Search_Info_LTC_BY_MALOPHOC(plist, mamonhoc, nhom, hocky, nienkhoa);
						if(check2 != -1){
							Message("ERROR:", "Nien Khoa " + convertToString(nienkhoa, strlen(nienkhoa)) + " Da Ton Tai Nhom " + ConvertIntToString(nhom) + "!", 0, 1000);
							break;
						}
						y+=4, length = 3;
					}else if(index == 4){
						y+=4;
						sscanf(temp.c_str(), "%d", &minsv);
						temp = maxsv;
					}else if(index == 5){
						sscanf(temp.c_str(), "%d", &maxsv);
						if(maxsv < minsv){
							Message("ERROR:", "So SV MAX khong duoc be hon SO SV MIN!", 0, 1000);
							temp = ConvertIntToString (minsv);
							printf("%-13s"," ");
							y-=4, index--;
							break;
						}
					}
					index++;
					temp = "";
					if(index == 6){
							LopTinChi *ltc = new LopTinChi;
							strcpy(ltc->MAMH, mamonhoc);
							strcpy(ltc->NIENKHOA, nienkhoa);
							ltc->HOCKY = hocky;
							ltc->NHOM = nhom;
							ltc->MINSV = minsv;
							ltc->MAXSV = maxsv;
							ltc->HUYLOP = FALSE;
							ltc->DSDK = NULL;
							plist.LOP[plist.N] = ltc;
							plist.N++;
						Message("SUCCESS:", "Them Moi Lop Tin Chi Thanh Cong!", 1, 1000);
						y = 8, index = 0;
						ClearInput(x, 4, 7);
						length = 50;
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "EDIT"){
		do{
			c = InputValue(length, temp, x, y, type);
			switch (c) {				
			    case EX_INSERT:
			    case EX_DEL:
				case TAB:
			        return c;
			    case CTRL_F:
			    	if(index > 2) break;
			    	DrawTableMonHocEx(p);
			    	DrawBoderThemLopTinChi("NHAP MA LOP TIN CHI DE CHINH SUA!");
					if(check != -1){
						DrawButtonYesNo(30, state);
	
						GoToXY(x, y);
						SetColor(BLACK);
						if(p == NULL){
							strcpy(mamonhoc, plist.LOP[check]->MAMH);
							temp = plist.LOP[check]->MAMH;
						}else{
							strcpy(mamonhoc, p->MH.MAMH);
							temp = p->MH.MAMH;
						}
						
						printf("%-50s", mamonhoc);
				
										
						GoToXY(x, y+=4);
						printf("%-50s", plist.LOP[check]->NIENKHOA);
						strcpy(nienkhoa, plist.LOP[check]->NIENKHOA);
									
						GoToXY(x, y+=4);
						printf("%-50d", plist.LOP[check]->HOCKY);
						hocky = plist.LOP[check]->HOCKY;
			
						GoToXY(x, y+=4);
						printf("%-50d", plist.LOP[check]->NHOM);
						nhom = plist.LOP[check]->NHOM;
									
						GoToXY(x, y+=4);
						printf("%-50d", plist.LOP[check]->MINSV);
						minsv = plist.LOP[check]->MINSV;
									
						GoToXY(x, y+=4);
						printf("%-50d", plist.LOP[check]->MAXSV);
						maxsv = plist.LOP[check]->MAXSV;
											
						y = y-20, type = 0, index = 1;
						
						length = 15;
					}
			    	break;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index < 7) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNo(31, is_delete, state);
			        break;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
					if(index == 1){
						strcpy(mamonhoc, temp.c_str() );
						if( p == NULL || (p != NULL && strcmp(mamonhoc, p->MH.MAMH) != 0)){
							p = SearchNodeMH(tree, mamonhoc);
							if(p == NULL){
								Message("ERROR:", "Ma Mon Hoc Khong Ton Tai!", 0, 1000);
								GoToXY(x+temp.length(), y);
								break;
							}
						}
						
						temp = nienkhoa, type = 7;
						y+=4, index++, length = 11;
					}else if(index == 2){
						strcpy(nienkhoa, temp.c_str() );
						

						temp = ConvertIntToString( hocky );
						y+=4, index++, type = 6, length = 1;
					}else if(index == 3){
						sscanf(temp.c_str(), "%d", &hocky);
						
						temp = ConvertIntToString( nhom );	
					y+=4, index++, type = 2;
					}else if(index == 4){
						sscanf(temp.c_str(), "%d", &nhom);
						

						temp = ConvertIntToString( minsv );
						y+=4, index++, length = 3;
					}else if(index == 5){
						sscanf(temp.c_str(), "%d", &minsv);
						

						temp = ConvertIntToString( maxsv);
						y+=4, index++, length = 3;
					}else if(index == 6){
						sscanf(temp.c_str(), "%d", &maxsv);
						
						if(maxsv < minsv){
							index = 5;
							Message("ERROR:", "So SV MAX khong duoc be hon SO SV MIN!", 0, 1000);
							temp = ConvertIntToString( minsv );
			    			y-=4;
			    			break;
						}
						
						type = 4, index++;
						DrawTitleYesNo(31, is_delete, state);
						
					}else if(index == 7){
						if(is_delete == 0) {
							strcpy(plist.LOP[check]->MAMH, mamonhoc);
							strcpy(plist.LOP[check]->NIENKHOA, nienkhoa);
							plist.LOP[check]->HOCKY = hocky;
							plist.LOP[check]->NHOM = nhom;
							plist.LOP[check]->MINSV = minsv;
							plist.LOP[check]->MAXSV = maxsv;
							Message("SUCCESS:", "Da Luu Thay Doi Lop Tin Chi!", 1, 1000);
						}
						return TAB;
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "DELETE"){
		do{
			c = InputValue(50, temp, x, y, type);
			switch (c) {				
			    case EX_INSERT:
			    case EX_DEL:
				case TAB:
			        return c;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index < 7) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNo(31, is_delete, state);
			        break;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
					if(index == 7){
						if(is_delete == 0) {
							string filename = "data//DSDK//" + ConvertIntToString(plist.LOP[check]->MALOPTC) + ".TXT";
							Delete_Item_LopTC(plist, check+1);
							
							remove( filename.c_str()  );
							Message("SUCCESS:", "Da Xoa Lop Tin Chi!", 1, 1000);
						}
						return TAB;
					}
					break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
}

void DrawTableLopTinChi(int is_draw_title, int tab){
	int pointX = 45, pointY = 5, width = 106, height = 37;
	int col1 = 10, col2 = 25, col3 = 47, col4 = 57, col5 = 65, col6 = 75, col7 = 85;
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5 || j == col6 || j == col7)
					if(i > 0 && i < height-2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-2)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(HORIZONTAL_LINE);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else if(i%2 == 0){
			for(int j = 0; j < width; j++){
				if(j == 0)
					cout << char(LEFT_CENTER_SIMPLE);
				else if(j == width-1)
					cout << char(RIGHT_CENTER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5|| j == col6 || j == col7)
					if(i == 2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-3)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(PLUS_CENTER);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else {
			cout << char(VERTICAL_LINE);
			
			if(i > 2 && i < height - 2){
				GoToXY(pointX+col1, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col2, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col3, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col4, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col5, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col6, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col7, pointY+i);
				cout << char(VERTICAL_LINE);
				
			}
			
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	CountHeaderLopTinChiTable(pointX+2, pointY+3);
	
	if(is_draw_title == 0) return;
	DrawHuongDanTable(48, 40, LopTinChiFunctionText, NUMBER_ITEM_LOPTINCHI_FUNCTION_TEXT);
	
	DrawTitle(LopTinChiText[0], 87);
	DrawTitleTable(87, 1, tab, LopTinChiText);
}


void DrawTableLopTinChiPlus(){
	int pointX = 45, pointY = 5, width = 106, height = 37;
	int col1 = 14, col2 = 27, col3 = 73, col4 = 82, col5 = 94;
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5 )
					if(i > 0 && i < height-2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-2)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(HORIZONTAL_LINE);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else if(i%2 == 0){
			for(int j = 0; j < width; j++){
				if(j == 0)
					cout << char(LEFT_CENTER_SIMPLE);
				else if(j == width-1)
					cout << char(RIGHT_CENTER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5)
					if(i == 2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-3)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(PLUS_CENTER);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else {
			cout << char(VERTICAL_LINE);
			
			if(i > 2 && i < height - 2){
				GoToXY(pointX+col1, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col2, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col3, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col4, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col5, pointY+i);
				cout << char(VERTICAL_LINE);
				
			}
			
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	CountHeaderLopTinChiTablePlus(pointX+2, pointY+3);
	DrawHuongDanTable(pointX+3, pointY+35, DanhSachDangKyFunctionText, 5);

}

void PrintDataLopTC(int tab, string state){
	int c, a, b = -1;
	
	if(state != "NEW" && dsloptc.N == 0) {
		Message("ERROR:", "Danh Sach Lop Tin Chi Rong. Khong The Sua Hoac Xoa!", 0, 1000);
		return;
	}
	
	TREE p = NULL;
					
	if(tab == 2){
		DrawTitle(LopTinChiText[0], 87);
		DrawTitleTable(87, 1, tab, LopTinChiText);
		do{
			a = ThemLopTinChi(dsloptc, state, b, p);
			HideTyping();
			if(a == TAB) {
				tab = 1;
				ClearTable(0);
				break;
			}
			else if(a == EX_INSERT || a == EX_DEL) {
				Message("ERROR:", "Dang Tao Moi Khong The Xoa Sua!", 0, 1000);
				break;
			}else if(a == ESC){
				ClearTable(1);
		        return;
			}
		} while (1);
	}
	
	if(dsloptc.N == 0){
		Message("ERROR:", "Danh Sach Lop Tin Chi Rong!", 0, 1000);
		ClearTable(1);
		return;
	}
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = dsloptc.N;

	int n = (int)ceil((double)total/15);
	int currentPage = 0, select = 0;
	string keyword = "";

	
	Message("SUCCESS:", "Load Du Lieu Lop Tin Chi Thanh Cong!", 1, 500);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
	DrawTableLopTinChi(1, tab);
	Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
	DrawArrowTable(47, 8, select, currentPage, stt);
	PrintSearchInput(47, keyword);
	do {
	    c = InputSearch(keyword, x, y, 50);
	    switch (c) {
	    	case EX_UP:
	    	case EX_DOWN:
	    		if (c == EX_UP &&select + 1 > 1) select--; 
		        else if (c == EX_DOWN && select + 1 < stt) select++;
		        
	    		DrawArrowTable(47, 8, select, currentPage, stt);
	    		PrintSearchInput(47, keyword);
	    		break;
		    case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	if(tab > 1) break;
		    	
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
		        Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
		        n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				
				if(currentPage == n-1)
						ClearRemainLopTinChi(stt, pointX, pointY);
						
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintSearchInput(47, keyword);
				
		        break;
		    case EX_INSERT:
		    case TAB: 
		    	tab = tab == 1 ? 2 : 1;
		    	DrawTitleTable(87, 1, tab, LopTinChiText);
		    	
		    	 if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTable(0);
		    		PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
					DrawTableLopTinChi(1, tab);
					Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
					DrawArrowTable(47, 8, select = 0, currentPage, stt);
					PrintSearchInput(47, keyword);
				}else if(tab == 2){
					ClearTable(0);
					do{
						a = ThemLopTinChi(dsloptc, "NEW", b, p);
						if(a == TAB){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
						    PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
							DrawTableLopTinChi(1, tab);
							Traverse_LTC(dsloptc, pointX, pointY = 8, currentPage, stt, keyword, total);
							DrawArrowTable(47, 8, select = 0, currentPage, stt);
							PrintSearchInput(47, keyword);
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else if(a == EX_F3 || a == EX_DEL){
							Message("ERROR:", "Ban Dang Tao Moi Khong The Xoa Sua!", 0, 1500);
						}
					}while(1);
				}
		    	break;		    
			case EX_DEL:
			case ENTER:
				{
					if(stt == 0){
						Message("ERROR:", "Lop Tin CHi Khong Hop Le!", 0, 500);
						GoToXY(x+keyword.length(), y);
						break;
					}
					
					tab = 2;
			    	b = Search_Info_LTC_By_STT(dsloptc, keyword, currentPage, select);
			    	select = 0;
					ClearTable(0);
					DrawTitleTable(87, 1, tab, LopTinChiText);
					string state2 = c == EX_DEL ? "DELETE" : "EDIT";
					do{
						a = ThemLopTinChi(dsloptc, state2, b, p);
						if(a == TAB){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
					    	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
							DrawTableLopTinChi(1, tab);
							Traverse_LTC(dsloptc, pointX, pointY, currentPage = 0, stt, keyword, total);
							DrawArrowTable(47, 8, select = 0, currentPage, stt);
							PrintSearchInput(47, keyword);
							b = -1;
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else{
							if(state2 == "NEW"){
								Message("ERROR:", "Ban Dang Tao Moi Khong The Xoa Sua!", 0, 1500);
							}else{
								HideTyping();
								if(a == EX_INSERT) b = -1;	
								state2 = a == EX_INSERT ? "NEW" : ( a == EX_F3 ? "EDIT" : "DELETE");
							}
						}
					}while(1);
					break;
				}
		    case CTRL_F:
		    	if(tab ==  2) break;
				Traverse_LTC(dsloptc, pointX, pointY, currentPage = 0, stt, keyword, total);
				ClearRemainLopTinChi(stt, pointX, pointY = 8);
				n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
		    case ESC:
		    	ClearTable(1);
		        return;
	    }
	} while (1);
}

void SaveFileLopTC(){
	char filename[50] = "data\\DSLOPTC.TXT";
	ofstream outfile;
    outfile.open(filename, ios::out );
    
    
    if(dsloptc.N == 0) return;
    for(int i = 0 ; i < dsloptc.N; i++){
    	//SaveFileListDK(dsloptc.LOP[i]->DSDK, dsloptc.LOP[i]->MALOPTC);
		outfile << dsloptc.LOP[i]->MALOPTC << "," << dsloptc.LOP[i]->MAMH << "," << dsloptc.LOP[i]->NIENKHOA << "," << dsloptc.LOP[i]->HOCKY << "," << dsloptc.LOP[i]->NHOM << "," << dsloptc.LOP[i]->MINSV << "," << dsloptc.LOP[i]->MAXSV << "," << dsloptc.LOP[i]->HUYLOP << "\n";
	}	
    outfile.close();
}

void Load_LopTC(){ 
	ClearList_LopTC(dsloptc);
	char filename[50] = "data\\DSLOPTC.TXT";
	
  	ifstream file(filename);
	
	if (!file.is_open())
	{
		Message("ERROR:", "File DSLOPTC.TXT Khong Ton Tai", 0, 1000);
		return;
	}
	
	string temp;
	LopTinChi *ltc;
	int i = -1;
	while (!file.eof())
	{
		getline(file, temp, ',');
		if(temp == "\n" || temp == "") break;
		
		
		ltc = new LopTinChi;
		sscanf(temp.c_str(), "%d", &ltc->MALOPTC);
		
		
		getline(file, temp, ',');
		strcpy(ltc->MAMH, temp.c_str());
		
		getline(file, temp, ',');
		strcpy(ltc->NIENKHOA, temp.c_str());
		
		getline(file, temp, ',');
		sscanf(temp.c_str(), "%d", &ltc->HOCKY);
		
		getline(file, temp, ',');
		sscanf(temp.c_str(), "%d", &ltc->NHOM);
		
		getline(file, temp, ',');
		sscanf(temp.c_str(), "%d", &ltc->MINSV);
		
		getline(file, temp, ',');
		sscanf(temp.c_str(), "%d", &ltc->MAXSV);
		
		getline(file, temp);
		sscanf(temp.c_str(), "%d", &ltc->HUYLOP);
		
		if(Search_Info_LTC(dsloptc, ltc->MALOPTC) != -1) continue;
		
		if (dsloptc.N == MAXLOPTINCHI - 1) {
			Message("ERROR:","Danh sach Lop TC Da Day!", 0, 1200);
			return;
		}
	
		dsloptc.LOP[++i] = ltc;
		dsloptc.N++;
		char filename2[50] = "data\\DSDK\\";
		strcat(filename2, ConvertIntToString(ltc->MALOPTC).c_str());
		strcat(filename2, ".TXT");
		
		Initialize_DK(dsloptc.LOP[i]->DSDK);
		Create_DangKy(dsloptc.LOP[i]->DSDK, filename2);
	}
	file.close();
}

void ClearBoderHuyLopTinChi(int type){
	int pointX = 65, pointY = 15, width = 70, height = 10;
	
	if(type == 1)
		pointX = 55, pointY = 10, width = 90, height = 12;

	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(type == 1) printf("%-100s", " ");
		else printf("%-80s", " ");
	}
}

void DrawBoderHuyLopTinChi(){
	int pointX = 65, pointY = 15, width = 70, height = 10;
	
	
	SetColor(RED);
	GoToXY(pointX+30, pointY+1);
	printf("%-50s", "!!!NGUY HIEM!!!");
	GoToXY(pointX+15, pointY+2);
	printf("%-50s", "VIEC HUY LOP SE KHONG THE KHOI PHUC DUOC.");
	GoToXY(pointX+20, pointY+3);
	printf("%-50s", "HAY XAC NHAN HANH DONG CUA BAN!");
	SetColor(BLACK);
	
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	GoToXY(87, 8);
	HideTyping();

}

void HuyLopTinChi(){
	if(dsloptc.N == 0){
		Message("ERROR:", "Danh Sach Rong!", 0, 1000);
		return;	
	}
	
	
	DrawBoderInputHuyLopTC();
	int c, x = 87, y = 13, is_delete = 0, type = 7, length = 11, index = 0, hocky;
	string temp;
	char nienkhoa[15];
	
	do{
		c = InputValue(length, temp, x, y, type);
		if(c == ENTER){
			if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			if(temp.length() == 0 ) {
				Message("ERROR:", "Vui long khong de trong!", 0, 1000);
				GoToXY(x+temp.length(), y);
			}else {
				if(index == 0){
				  	strcpy(nienkhoa, temp.c_str() );
				  	index++, y+=4, length = 1, type = 2, temp = "";
				}else if(index == 1){
					sscanf(temp.c_str(), "%d", &hocky);
					HideTyping();
					ClearBoderHuyLopTinChi(1);
					break;
				}
			}
		}else if(c == ESC){
			HideTyping();
			ClearBoderHuyLopTinChi(1);
			return;
		}
	}while(1);
	
	
	DrawBoderHuyLopTinChi();
	x = 10, y = 20, type = 4;
	DrawButtonYesNo(y, "HUYLOPTC");
	DrawTitleYesNo(y+1, is_delete, "HUYLOPTC");
	do{
		c = InputValue(length, temp, x, y, type);
		switch (c) {
			case EX_LEFT:
			case EX_RIGHT:
			    is_delete = is_delete == 1 ? 0 : 1;
			    DrawTitleYesNo(y+1, is_delete, "HUYLOPTC");
			    break;
			   case ENTER:
			    	
			   	if(is_delete == 1) is_delete = 0;
			   	else{
			   		Huy_LopTinChi(dsloptc, nienkhoa, hocky);
					Message("SUCCESS:", "Da Huy Lop Tin Chi Thanh Cong!", 1, 1500);
				}
			case ESC:
			   	ClearBoderHuyLopTinChi(0);
			       return;
		}
	}while(1);
}

void DrawBoderInputHuyLopTC(){
	int pointX = 55, pointY = 10, width = 90, height = 12;
	
	
	SetColor(RED);
	GoToXY(pointX+34, pointY+1);
	printf("%-50s", "NHAP THONG TIN LOP TIN CHI!");
	SetColor(BLACK);
	
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	for(int i = 1; i < 3; i++){
		GoToXY(pointX+5, pointY+3+(i-1)*4);
		printf("%-30s", ThemLopTinChiText[i]);
		DrawInput(85, pointY+2+(i-1)*4);
	}
	
	GoToXY(87, 8);
	HideTyping();

}

void DrawTableLopTCEx(){
	int c, a;
	if(dsloptc.N == 0){
		Message("ERROR:", "Danh Sach Lop Tin Chi Rong!", 0, 1000);
		return ;
	}
	DrawTitle(DanhSachDangKyText[0], 88);
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = dsloptc.N;

	int n = (int)ceil((double)total/15);
	int currentPage = 0, select = 0;
	string keyword = "";

	
	Message("SUCCESS:", "Load Du Lieu Lop Tin Chi Thanh Cong!", 1, 500);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
	DrawTableLopTinChi(0, 0);
	
	DrawHuongDanTable(pointX+5, pointY+32, DanhSachDangKyFunctionText, 3);
	
	Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
	DrawArrowTable(47, 8, select = 0, currentPage, stt);
	PrintSearchInput(47, keyword);
	do {
	    c = InputSearch(keyword, x, y, 50);
	    switch (c) {
	    	case EX_UP:
	    	case EX_DOWN:
	    		if (c == EX_UP &&select + 1 > 1) select--; 
		        else if (c == EX_DOWN && select + 1 < stt) select++;
		        
	    		DrawArrowTable(47, 8, select, currentPage, stt);
	    		PrintSearchInput(47, keyword);
	    		break;
		    case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
		        Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
		        n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				
				if(currentPage == n-1)
						ClearRemainLopTinChi(stt, pointX, pointY);
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintSearchInput(47, keyword);
				
		    	break;
		    case ENTER:
		    	{
					if(stt == 0){
						Message("ERROR:", "Lop Tin CHi Khong Hop Le!", 0, 500);
						GoToXY(x+keyword.length(), y);
						break;
					}
					
			    	a = Search_Info_LTC_By_STT(dsloptc, keyword, currentPage, select);
			    	select = 0;
							
					if(dsloptc.LOP[a]->DSDK == NULL){
						Message("ERROR:", "Danh Sach Sinh Vien Rong!", 0, 1000);
						break;
					}
					DrawTableSinhVienEx(dsloptc.LOP[a]->DSDK);
					
					DrawTableLopTinChi(0, 0);
					DrawHuongDanTable(pointX+5, pointY+32, DanhSachDangKyFunctionText, 3);
					Traverse_LTC(dsloptc, pointX, pointY, currentPage = 0, stt, keyword, total);
					ClearRemainLopTinChi(stt, pointX, pointY = 8);
					n = (int)ceil((double)total/15);
					PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
					DrawArrowTable(47, 8, select = 0, currentPage, stt);
					PrintSearchInput(47, keyword);
					
					break;
				}
		    case CTRL_F:
				Traverse_LTC(dsloptc, pointX, pointY, currentPage = 0, stt, keyword, total);
				ClearRemainLopTinChi(stt, pointX, pointY = 8);
				n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
		    case ESC:
		    	ClearTable(1);
		        return;
	    }
	} while (1);
}

int DrawTableMonHocEx(TREE &p){
	TREE DSMH = NULL;
	int c, a;
	
	if(tree == NULL){
		Message("ERROR:", "Danh Sach Mon Hoc Rong!", 0, 1000);
		return -1;
	}
	ClearTable(0);
	Inorder(tree, DSMH); 
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = ReccountTree(tree);
	int n = (int)ceil((double)total/15);
	int currentPage = 0, select = 0;
	string keyword = "";
	
	TREE *pages = new TREE[n];
	Selection_Sort_DSMH(DSMH);
	
	Message("SUCCESS:", "Load Du Lieu Mon Hoc Thanh Cong!", 1, 500);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
	DrawTableMonHoc(0);
	Traverse_DSMH(DSMH, stt, pointX, pointY, currentPage, keyword, pages);
	DrawArrowTable(47, 8, select, currentPage, stt);
	PrintSearchInput(47, keyword);
	
	do {
	    c = InputSearch(keyword, x, y, 50);
	    switch (c) {
	    	case EX_UP:
	    	case EX_DOWN:
	    		if (c == EX_UP &&select + 1 > 1) select--; 
		        else if (c == EX_DOWN && select + 1 < stt) select++;
		        
	    		DrawArrowTable(47, 8, select, currentPage, stt);
	    		PrintSearchInput(47, keyword);
	    		break;
		    case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
				Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword, pages);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				
				if(currentPage == n-1)
						ClearRemainMonHoc(stt, pointX, pointY, currentPage);
						
				DrawArrowTable(47, 8, select, currentPage, stt);
				PrintSearchInput(47, keyword);
				
		        break;
		    case TAB: 
		    	delete DSMH;
		    	ClearTable(0);
		    	return 1;
		    case CTRL_F:
		    	Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage = 0, keyword, pages);
				ClearRemainMonHoc(stt, pointX, pointY = 8, 0);
				total = Reccount_MH_With_Keyword(DSMH, keyword);
				n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				DrawArrowTable(47, 8, select, currentPage, stt);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
		    case ENTER:
				if(stt == 0){
					Message("ERROR:", "Mon Hoc Khong Hop Le!", 0, 500);
					GoToXY(x+keyword.length(), y);
					break;
				}
					
			   	p = Search_By_STT_DSMH(DSMH, select, currentPage, keyword, pages);
				
				delete[] pages;
		    	DeleteAllTree(DSMH);
		    	ClearTable(0);
				return 2;
		    case ESC:
		    	delete[] pages;
		    	DeleteAllTree(DSMH);
		    	ClearTable(0);
				return -1;
	    }
	} while (1);
}

void DrawTableSinhVienEx(LISTDK &First){
	int c, stt = 0, pointX = 47, pointY = 8, x = 57, y = 6; 
	LISTSV DSSV = NULL;
	
	int total = Reccount_DK_WITH_ADD_SV(First, DSSV);
	ClearTable(0);
	
	int n = (int)ceil((double)total/15);
	int currentPage = 0;
	string keyword = "";
	char malophoc[2] = "";
	LISTSV *pages = new LISTSV[n];
	
	
	Message("SUCCESS:", "Load Du Lieu Sinh Vien Thanh Cong!", 1, 500);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
	DrawTableSinhVien(malophoc, 0);
	Selection_Sort_SV(DSSV, malophoc);
	Traverse_SV(DSSV, malophoc, stt, pointX, pointY, currentPage, keyword, pages);
	
	strcpy(SinhVienFunctionText[0][0], "ESC");
	strcpy(SinhVienFunctionText[1][0], ": Thoat");
	DrawHuongDanTable(pointX+5, pointY+32, SinhVienFunctionText, 2);
	PrintSearchInput(47, keyword);
	
	do {
	    c = InputSearch(keyword, x, y, 50);
	    switch (c) {
		    case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;

		        HideTyping();
				Traverse_SV(DSSV, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				
				if(currentPage == n-1)
					ClearRemainSinhVien(stt, pointX, pointY);
						
				PrintSearchInput(47, keyword);
				
		        break;
		    case CTRL_F:
				Traverse_SV(DSSV, malophoc, stt = 0, pointX, pointY = 8, currentPage = 0, keyword, pages);
				ClearRemainSinhVien(stt, pointX, pointY = 8);
				total = Reccount_SV_With_Keyword(DSSV, malophoc, keyword);
				n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				PrintKeyWord("%-50s", keyword, x, y);

				break; 
		    case ESC:
		    	delete[] pages;
		    	ClearListSV(DSSV);
		    	ClearTable(0);
		        return;
	    }
	} while (1);
	
} 


/*
* === END ===
*/




/*
* — Ham Xu ly Lop Hoc —
*/

void Initialize_LH(DSLOPPTR &ListLop){
   ListLop = NULL;
}

int DeleteInfo_LH(DSLOPPTR &ListLop, char *malh){  
	DSLOPPTR p = ListLop, q;
  	if (ListLop == NULL ) return 0;
  	if ( strcmp(ListLop->MALOP, malh) == 0 ) {
	    p = ListLop;
		ListLop = p->next;
		delete p; 
		
		return 1;
	}
    
	for ( p = ListLop; p->next!=NULL &&  strcmp(p->next->MALOP, malh) != 0; p = p->next);
	if (p->next!= NULL ) {
		q = p->next; 
		p->next=q->next;
		delete q; 
		return 1;
	}
	return 0;
}

void ClearList_LH(DSLOPPTR &ListLop){
   DSLOPPTR p, q;
   p = ListLop;
   while(ListLop != NULL)
   {
      p = ListLop;
      ListLop = ListLop->next;
      delete p;
   }
   ListLop = NULL;
}

int Reccount_LH(DSLOPPTR ListLop) {
	if(ListLop == NULL) return 0;
	
	int count = 0;
	DSLOPPTR p = ListLop;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

int Reccount_LH_With_Keyword(DSLOPPTR ListLop, std::string keyword){
	if(ListLop == NULL) return 0;
	
	int count = 0;
	DSLOPPTR p = ListLop;
	while(p != NULL){
		string malophoc = convertToString(p->MALOP, strlen(p->MALOP));
		if(malophoc.find(keyword) == string::npos) count++;
		p = p->next;
	}
	return count;
}

void Selection_Sort_LH(DSLOPPTR& ListLop){
    DSLOPPTR p, q, pmin;
    char min[50];
	if(ListLop == NULL) return;
	
    for (p = ListLop; p->next != NULL; p = p->next)
    {
        strcpy(min, p->MALOP);
        pmin = p;
        for (q = p->next; q != NULL; q = q->next){
	        if ( strcmp(min, q->MALOP ) > 0)
	        {
	            strcpy(min, q->MALOP);
	            pmin = q;
	        }
		}
            
        // hoan doi truong info cua hai nut p va pmin
        strcpy(pmin->MALOP, p->MALOP);
        strcpy(p->MALOP, min);
    }
}

void Traverse_LH(DSLOPPTR ListLop, int &stt, int pointX, int pointY, int currentPage, std::string keyword, DSLOPPTR *pages){
   	DSLOPPTR p;
   	
   	if(currentPage == 0)
    	p = ListLop;
	else if(pages[currentPage] != NULL)
		p = pages[currentPage];
		
   	while(p != NULL)
   	{
   		if( stt < 16){
	   		string malophoc = convertToString(p->MALOP, strlen(p->MALOP));
	   		if(malophoc.find(keyword) != string::npos){
	   			if(stt == 15){
        			pages[currentPage+1] = p;
	    			return;
				}
				if(stt == 0){
	    			pages[currentPage] = p;
				}
	    		++stt;
	    		if(stt == 16) break;
				GoToXY(pointX, pointY+=2);
	        	printf("%-6d", stt + 15*currentPage);
	        	GoToXY(pointX+8, pointY);
	        	printf("%-20s\n", p->MALOP);
			}
		}
		p = p->next;
   	}
}

DSLOPPTR Search_LH(DSLOPPTR ListLop, char *malh){
	if(ListLop == NULL) return NULL;
	DSLOPPTR p;
	for (p = ListLop;  p != NULL ; p=p->next ) 
        if ( strcmp(p->MALOP, malh) == 0  ) return p;
	return NULL;
}

DSLOPPTR Search_LH_By_STT(DSLOPPTR ListLop, string keyword, int currentPage, int select, DSLOPPTR *pages){
	if(ListLop == NULL) return NULL;
	DSLOPPTR p;
	int stt = 0;
	if(currentPage == 0)
    	p = ListLop;
	else if(pages[currentPage] != NULL)
		p = pages[currentPage];
		
	while (p != NULL ) {
		string malophoc = convertToString(p->MALOP, strlen(p->MALOP));
   		if(malophoc.find(keyword) != string::npos){ 
   		   if(select == stt) return p;
   		   stt++;
   		}
   		p=p->next;
	}
	return NULL;
}

void Insert_Last_LH(DSLOPPTR &ListLop, char *malh){
    DSLOPPTR p = new NodeLop;
    strcpy(p->MALOP, malh);
    p->next = NULL;
      
    DSLOPPTR q = Search_LH(ListLop, malh);
    if(ListLop == NULL) 
		ListLop = p;
    else if(q == NULL){
      	DSLOPPTR Last = ListLop;
      	for(; Last->next != NULL; Last = Last->next);
      	Last->next = p;
	}
}

void SaveFileSinhVien(){
	char filename[50] = "data\\DSSV.TXT";
	ofstream outfile;
    outfile.open(filename, ios::out );
    LISTSV p = First;
    if(p == NULL) return;
	while(p != NULL){
    	outfile << p->SV.MASV << "," << p->SV.HO << "," << p->SV.TEN << "," << p->SV.MALOP << "," << p->SV.PHAI << "," << p->SV.SODT << "\n";
    	p = p->next;
	}
    outfile.close();
}

void Load_SinhVien(){ 
	
	ClearListSV(First);
	Initialize_SV(First);
	
	char filename[50] = "data\\DSSV.TXT";
	SinhVien x;
  	ifstream file(filename);
	
	if (!file.is_open()) return;
	
	string temp;
	while (!file.eof())
	{
		getline(file, temp, ',');
		if(temp == "\n" || temp == "") break;
		strcpy(x.MASV, temp.c_str());
		
		getline(file, temp, ',');
		strcpy(x.HO, temp.c_str());
		
		getline(file, temp, ',');
		strcpy(x.TEN, temp.c_str());
		
		getline(file, temp, ',');
		strcpy(x.MALOP, temp.c_str());
		
		Insert_Last_LH(ListLop, x.MALOP);
		
		getline(file, temp, ',');
		sscanf(temp.c_str(), "%d", &x.PHAI);
		
		getline(file, temp);
		strcpy(x.SODT, temp.c_str());
		
		LISTSV p = Search_Info_SV(First, x);
		if(p != NULL) continue;
		
		Insert_Last_SV(First, x);
	}
	file.close();
}

void DrawTableLopHoc(int &pointX, int &pointY){
	int width = 50, height = 37;
	int col1 = 8;
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else if(j == col1 )
					if(i > 0 && i < height-2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-2)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(HORIZONTAL_LINE);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else if(i%2 == 0){
			for(int j = 0; j < width; j++){
				if(j == 0)
					cout << char(LEFT_CENTER_SIMPLE);
				else if(j == width-1)
					cout << char(RIGHT_CENTER_SIMPLE);
				else if(j == col1)
					if(i == 2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-3)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(PLUS_CENTER);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else {
			cout << char(VERTICAL_LINE);
			
			if(i > 2 && i < height - 2){
				GoToXY(pointX+col1, pointY+i);
				cout << char(VERTICAL_LINE);
			}
			
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	GoToXY(pointX+2, pointY+=3);
	printf("%-6s", "STT");
	GoToXY(pointX+10, pointY);
	printf("%-20s", "MA LOP HOC");
	
}

void ClearRemainLopHoc(int total, int pointX, int pointY){
	int row2 = 15-total;
	pointY = total*2+pointY;
	for(int i = 0; i < row2;i++){
		GoToXY(pointX, pointY+=2); printf("%-6s", " ");
		GoToXY(pointX+8, pointY); printf("%-20s", " ");
	}
}

void DrawCharArrow(int select, int total){
	HideTyping();
	int x = 78, y = 14;
	for(int i = 0; i < total; i++){
		GoToXY(x, y+2*i );
		if(select == i){
			SetColor(LIGHT_PURPLE);
			cout << "=====>>>>>";
			SetColor(BLACK);
		}else printf("%-10s"," ");
	}
}

void PrintDataLopHoc(string state){
	if(ListLop == NULL){
		if(state == "DATA_TABLE" || state == "EDIT"){
			Message("ERROR:", "Danh Sach Sinh Vien Rong", 0, 1000);
			return;	
		}
	}
	int pointX = 74, pointY = 5, x = 86, y = 6;
	int c, stt, select = 0, n, currentPage = 0, total;
	string keyword = "";
	
	total = Reccount_LH(ListLop);
	n = (int)ceil((double)total/15);
	DSLOPPTR *pages = new DSLOPPTR[n];
	DSLOPPTR p = NULL;
	
	
	DrawTableLopHoc(pointX, pointY);
	if(state == "NEW"){
		strcpy(DanhSachDangKyFunctionText[0][0], "INSETR");
		strcpy(DanhSachDangKyFunctionText[1][0], ": Them Moi");
	}
	
	DrawHuongDanTable(pointX+3, pointY+32, DanhSachDangKyFunctionText, 2);
	
	Selection_Sort_LH(ListLop);
	Traverse_LH(ListLop, stt = 0, pointX+=2, pointY, currentPage, keyword, pages);
	
	DrawArrowTable(pointX, 8, select, currentPage, stt);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 113);
	PrintSearchInput(pointX, keyword);
	do {
	    c = InputValue(25, keyword, x, y, 5);
	    switch (c) {
	    	case EX_UP:
	    	case EX_DOWN:
	    		if (c == EX_UP &&select + 1 > 1) select--; 
		        else if (c == EX_DOWN && select + 1 < stt) select++;
		        
	    		DrawArrowTable(pointX, 8, select, currentPage, stt);
	    		PrintSearchInput(pointX, keyword);
	    		
	    		break;
	    	case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;

		        HideTyping();
				Traverse_LH(ListLop, stt = 0, pointX, pointY, currentPage, keyword, pages);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 113);
				
				
				if(currentPage == n-1)
					ClearRemainLopHoc(stt, pointX, pointY);
					
				DrawArrowTable(pointX, 8, select = 0, currentPage, stt);
				PrintSearchInput(pointX, keyword);
		        break;
		    case CTRL_F:
				Traverse_LH(ListLop, stt = 0, pointX, pointY = 8, currentPage = 0, keyword, pages);
				ClearRemainLopHoc(stt, pointX, pointY = 8);
				total = Reccount_LH_With_Keyword(ListLop, keyword);
				n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 113);
				
				DrawArrowTable(pointX, 8, select = 0, currentPage, stt);
				PrintSearchInput(pointX, keyword);
		    	break;
		    case EX_INSERT:
		    	if(state == "NEW"){
		    		ClearTable(0);
		    		if(keyword.length() == 0){
		    			p = Search_LH_By_STT(ListLop, keyword, currentPage, select, pages);
		    			PrintDataSinhVien(First, 2, "NEW", p->MALOP, 0);
					}else{
						char temp[50];
						strcpy(temp, keyword.c_str());
						PrintDataSinhVien(First, 2, "NEW", temp, 1);
					}
					
					
					DrawTableLopHoc(pointX = 74, pointY = 5);
					strcpy(DanhSachDangKyFunctionText[0][0], "INSETR");
					strcpy(DanhSachDangKyFunctionText[1][0], ": Them Moi");
					DrawHuongDanTable(pointX+3, pointY+32, DanhSachDangKyFunctionText, 2);
					
					Selection_Sort_LH(ListLop);
					Traverse_LH(ListLop, stt = 0, pointX+=2, pointY, currentPage = 0, keyword, pages);
					DrawArrowTable(pointX, 8, select, currentPage, stt);
					PrintPageTable(n > 0 ? currentPage+1 : 0, n, 113);
					PrintSearchInput(pointX, keyword);
		    		
				}
		    	break;
		    case ENTER:
		    	{
		    		p = Search_LH_By_STT(ListLop, keyword, currentPage, select, pages);
				    if(p == NULL){
				    	Message("ERROR:", "Ma Lop Khong Ton Tai!", 0, 1000);
					    break;
					}
					ClearTable(0);
					if(state == "DATA_TABLE") PrintDataSinhVien(First, 1, state, p->MALOP, 0);
					else PrintDataSinhVien(First, 2, state, p->MALOP, 0);
					
					
					DrawTableLopHoc(pointX = 74, pointY = 5);
					if(state == "NEW"){
						strcpy(DanhSachDangKyFunctionText[0][0], "INSETR");
						strcpy(DanhSachDangKyFunctionText[1][0], ": Them Moi");
						Selection_Sort_LH(ListLop);
					}
					DrawHuongDanTable(pointX+3, pointY+32, DanhSachDangKyFunctionText, 2);
					
					Traverse_LH(ListLop, stt = 0, pointX+=2, pointY, currentPage = 0, keyword, pages);
					DrawArrowTable(pointX, 8, select, currentPage, stt);
					PrintPageTable(n > 0 ? currentPage+1 : 0, n, 113);
					PrintSearchInput(pointX, keyword);
				}
		    	break;
		    case ESC:
		    	HideTyping();
		    	ClearTable(0);
		    	return;
		}	
	}while(1);
}
/*
* === END ===
*/





/*
* — Ham xu ly Cau truc sinh vien  —
*/

void Initialize_SV(LISTSV &First){
    First = NULL;
}

int Reccount_SV_With_Keyword(LISTSV First, char *malophoc, string keyword){
	if( First == NULL ) return 0;
	
	int count = 0;
	LISTSV p = First;
	while(p != NULL ){
		string ten = convertToString(p->SV.TEN, strlen(p->SV.TEN));
        string ho = convertToString(p->SV.HO, strlen(p->SV.HO));
        string masv = convertToString(p->SV.MASV, strlen(p->SV.MASV));
		if( (strlen(malophoc) ==0 || strcmp(p->SV.MALOP, malophoc) == 0 ) && (ten.find(keyword) != string::npos || ho.find(keyword) !=  string::npos || masv.find(keyword) !=  string::npos) ) count++;
		p = p->next;
	}
	return count;
}

int Reccount_SV(LISTSV First, char *malophoc) {
	if( First == NULL ) return 0;
	
	int count = 0;
	LISTSV p = First;
	while(p != NULL ){
		if(strcmp(p->SV.MALOP, malophoc) == 0) count++;
		p = p->next;
	}
	return count;

}

LISTSV Search_Info_SV(LISTSV First, SinhVien x){
    LISTSV p;
    for (p = First; p != NULL; p = p->next)
        if (strcmp(p->SV.MASV, x.MASV ) == 0)
            return p;
    return NULL;
}

LISTSV Search_Info_SV_By_STT(LISTSV First, char *malophoc, std::string keyword, int select, int currentPage, LISTSV *pages){
	LISTSV p;
	if(currentPage == 0)
    	p = First;
	else if(pages[currentPage] != NULL)
		p = pages[currentPage];
		
	int stt = 0;
	while(p != NULL){
		string ten = convertToString(p->SV.TEN, strlen(p->SV.TEN));
		string ho = convertToString(p->SV.HO, strlen(p->SV.HO));
	    string masv = convertToString(p->SV.MASV, strlen(p->SV.MASV));
		if( (strlen(malophoc) ==0 || strcmp(p->SV.MALOP, malophoc) == 0 ) && (ten.find(keyword) != string::npos || ho.find(keyword) !=  string::npos || masv.find(keyword) !=  string::npos) ) {
			++stt;
			if(select == stt-1) return p;
		}
		p = p->next;
	}
	
	return NULL;
	
}

LISTSV Check_Is_New_Class(LISTSV First, char *malophoc){
    LISTSV p;
    for (p = First; p != NULL; p = p->next)
        if (strcmp(p->SV.MALOP, malophoc ) == 0)
            return p;
    return NULL;
}

int Delete_Info_SV(LISTSV& First, SinhVien x){
    LISTSV q, p = First;
    if (First == NULL)
        return 0;
    if ( strcmp(First->SV.MASV, x.MASV ) == 0)
    {
        p = First;
        First = p->next;
        delete p;
        return 1;
    }

    for (p = First; p->next != NULL && strcmp(p->next->SV.MASV, x.MASV ) != 0; p = p->next);
    if (p->next != NULL)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        return 1;
    }
    return 0;
}

void ClearListSV(LISTSV& First){
    LISTSV p;
    while (First != NULL)
    {
        p = First;
        First = First->next;
        delete p;
    }
}

void Traverse_SV(LISTSV First, char *malophoc, int &stt, int &pointX, int pointY, int currentPage, std::string &keyword, LISTSV *pages){
    LISTSV p;
    
    if(currentPage == 0)
    	p = First;
	else if(pages[currentPage] != NULL)
		p = pages[currentPage];
	
    while (p != NULL)
    {
        
    	if( stt < 16 && (strlen(malophoc) == 0 || strcmp(p->SV.MALOP, malophoc) == 0 ) ){
    		string ten = convertToString(p->SV.TEN, strlen(p->SV.TEN));
	        string ho = convertToString(p->SV.HO, strlen(p->SV.HO));
	        string masv = convertToString(p->SV.MASV, strlen(p->SV.MASV));
        	if( (ten.find(keyword) != string::npos || ho.find(keyword) !=  string::npos || masv.find(keyword) !=  string::npos) ){
        		if(stt == 15){
        			pages[currentPage+1] = p;
	    			return;
				}
				if(stt == 0){
	    			pages[currentPage] = p;
				}
	    		GoToXY(pointX, pointY+=2);
	    		++stt;
	    		if(stt == 16) break;
	    		CoutNodeSV(p->SV, stt + 15*currentPage, pointX, pointY);
			}
		}
        p = p->next;
    }
}

void Selection_Sort_SV(LISTSV& First, char *malophoc){
    LISTSV p, q, pmin;
    SinhVien min;
    char name[40], name2[40]; 

    for (p = First; p->next != NULL; p = p->next)
    {
        min = p->SV;
        pmin = p;
        for (q = p->next; q != NULL; q = q->next){
        	if( strlen(malophoc) == 0 || strcmp(q->SV.MALOP, malophoc) == 0 ){
        		strcpy(name, q->SV.TEN);
	        	strcat(name, q->SV.TEN);
	        	
	        	strcpy(name2, min.TEN);
	        	strcat(name2, min.HO);
	        	
	        	if ( strcmp(name, name2 ) < 0)
	            {
	                min = q->SV;
	                pmin = q;
	            }
			}
		}
            
        // hoan doi truong info cua hai nut p va pmin
        pmin->SV = p->SV;
        p->SV = min;
    }
}

void Insert_Last_SV(LISTSV &First, SinhVien x){
    LISTSV p = new NodeSV;
    p->SV = x;
    p->next = NULL;
      
    if(First == NULL) 
		First = p;
    else{
      	LISTSV Last = First;
      	for(; Last->next != NULL; Last = Last->next);
      	Last->next = p;
	}
}

void CountHeaderSinhVienTable(int pointX, int pointY){
	GoToXY(pointX, pointY); cout << "STT";
	GoToXY(pointX + 8, pointY); cout << "MASV";
	GoToXY(pointX + 22, pointY); cout << "HO";
	GoToXY(pointX + 63, pointY); cout << "TEN";
	GoToXY(pointX + 82, pointY); cout << "PHAI";
	GoToXY(pointX + 90, pointY); cout << "SODT";
}

void CoutNodeSV(SinhVien p, int stt, int pointX, int pointY){
	HideTyping();
	GoToXY(pointX, pointY); printf("%-6d", stt);
	GoToXY(pointX + 8, pointY); printf("%-11s", p.MASV);
	GoToXY(pointX + 22, pointY); printf("%-37s", p.HO);
	GoToXY(pointX + 63, pointY); printf("%-10s", p.TEN);
	GoToXY(pointX + 82, pointY); printf("%-4s", p.PHAI == 1 ? "Nam" : "Nu");
	GoToXY(pointX + 90, pointY); printf("%-10s", p.SODT);	
}

void DrawBoderThemSinhVien(string title, char *malophoc){
	int pointX = 55, pointY = 5, width = 90, height = 31;
	
	SetColor(RED);
	GoToXY(pointX+30, pointY+1);
	printf("%-50s", title.c_str());
	SetColor(BLACK);
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	DrawTitleFunction(pointX+15, pointY+30, SinhVienFunctionText, NUMBER_ITEM_SINHVIEN_FUNCTION_TEXT, 1);
	
	
	for(int i = 0; i < NUMBER_ITEM_SINHVIENTEXT; i++){
		GoToXY(pointX+5, pointY+3+i*4);
		cout << ThemSinhVienText[i];
		DrawInput(85, pointY+2+i*4);
	}
	
	GoToXY(87, 20);
	SetColor(PURPLE);
	cout << malophoc;
	SetColor(BLACK);
	
	GoToXY(87, 8);
	Typing();
}

void DrawInputGender(int pointX, int pointY, int gender){
	HideTyping();
	GoToXY(pointX, pointY);
	
	SetColor(BLACK);
	
	if(gender == 1){
		SetColor(WHITE);
		SetBGColor(GREEN);
	}
	cout << "          NAM           ";
	
	SetColor(BLACK);
	SetBGColor(WHITE);
	cout << char(219);
	SetColor(BLACK);
	SetBGColor(WHITE);
	
	if(gender == 0){
		SetColor(WHITE);
		SetBGColor(GREEN);
	}
	cout << "           NU            ";
	
	SetBGColor(WHITE);
	SetColor(BLACK);
}

int ThemSinhVien(LISTSV &First, string state, char *malophoc, int is_new_class, LISTSV p){
	
	
	SinhVien sv;
	int x = 87, y = 8, c, type = 0, index = 0, is_delete = 0, gender = 1, length = 15;
	string temp = "";
	
	if(state == "NEW"){
		DrawBoderThemSinhVien("NHAP THONG TIN DE THEM SINH VIEN!", malophoc);
	}
	else if(state == "EDIT"){
		DrawBoderThemSinhVien("NHAP MA SINH VIEN DE CHINH SUA!", malophoc);
		if(p != NULL){
			DrawButtonYesNo(31, state);
						
			GoToXY(x, y);
			SetColor(RED);
			printf("%-50s", p->SV.MASV);
						
			GoToXY(x, y+=4);
			SetColor(BLACK);
			printf("%-50s", p->SV.HO);
							
			GoToXY(x, y+=4);
			printf("%-50s", p->SV.TEN);
							
			GoToXY(x, y+=4);
			SetColor(RED);
			printf("%-50s", p->SV.MALOP);
					
			DrawInputGender(x, y+=4, p->SV.PHAI);

			GoToXY(x, y+=4);
			printf("%-50s", p->SV.SODT);
						
			SetColor(BLACK);		
						
			y = y-16, type = 1, index++;
			temp = p->SV.HO;
			strcpy(sv.MASV, p->SV.MASV);
			strcpy(sv.MALOP, malophoc);
		}
		
	}
	else if(state == "DELETE"){
		DrawBoderThemSinhVien("NHAP MA SINH VIEN DE XOA!", malophoc);
		if(p != NULL){
			GoToXY(x, y);
			SetColor(RED);
			printf("%-50s", p->SV.MASV);
						
			GoToXY(x, y+=4);
			printf("%-50s", p->SV.HO);
							
			GoToXY(x, y+=4);
			printf("%-50s", p->SV.TEN);
							
			GoToXY(x, y+=4);
			printf("%-50s", p->SV.MALOP);
					
			DrawInputGender(x, y+=4, p->SV.PHAI);
						
			SetColor(RED);
			GoToXY(x, y+=4);
			printf("%-50s", p->SV.SODT);
						
			SetColor(BLACK);
						
			index = 6;
			type = 4;
			GoToXY(x , y);
			is_delete = 0;
			DrawButtonYesNo(31, state);
			DrawTitleYesNo(32, is_delete, state);
			strcpy(sv.MASV, p->SV.MASV);
			strcpy(sv.MALOP, malophoc);
		}
	}
	
	
	
	if(state == "NEW"){
		DrawInputGender(87, 24, -1);
			do{
			c = InputValue(length, temp, x, y, type);
			switch (c) {				
			    case EX_DEL:
			    	if(is_new_class){
			    		ClearButtonYesNo(31);
			    		Message("ERROR:", "Danh Sach Sinh Vien Rong Khong The Xoa Hoac Sua!", 0, 1500);
			    		break;
					}
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index < 4) break;
			    	gender = gender == 1 ? 0 : 1;
			    	DrawInputGender(x, y, gender);
			        break;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(index == 0){
			    		if(temp.length() == 0 ) return 0;
			    		strcpy(sv.MASV, temp.c_str());
			    		p = Search_Info_SV(First, sv);
			    		if(p != NULL) {
			    			Message("ERROR:", "Ma Sinh Vien Da Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
						type = 1, length = 30;
						strcpy(sv.MALOP, malophoc);
					}else if(index == 1){
						strcpy(sv.HO, temp.c_str());
						length = 10;
					}else if(index == 2){
						strcpy(sv.TEN, temp.c_str());
						type = 4, index = 3, y+=4;
						DrawInputGender(x, y+4, gender);
					}else if(index == 4){
						temp = gender == 1 ? "Nam" : "Nu";
						sv.PHAI = gender;
						type = 3, length = 15;
					}else if(index == 5){
						strcpy(sv.SODT, temp.c_str());
					}
					
					if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					temp = "";
				    index++;
				    if(index == 6) {
				    	GoToXY(x, y);
						printf("%-50s"," ");
						gender = 0;
						DrawInputGender(x, 24, gender-1);
						
						Insert_Last_SV(First, sv);
						
				    	type = 0, y = 4;
						index = 0;
				    	ClearInput(x, y, 3);
				    	Message("SUCCESS:", "Them Sinh Vien Thanh Cong!", 1, 1000);
				    	if(is_new_class){
				    		LISTSV q = Check_Is_New_Class(First, malophoc);
					    	if(q != NULL){
					    		Insert_Last_LH(ListLop, malophoc);
							}
							is_new_class = 0;
						}	
					}
					GoToXY(x, y+=4);
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "EDIT"){	
		DrawInputGender(87, 24, p != NULL ? p->SV.PHAI : -1);
			do{
			c = InputValue(50, temp, x, y, type);
			switch (c) {				
			    case EX_INSERT:
			    case EX_DEL:
			    	ClearButtonYesNo(31);
			    	return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index == 4) {
			    		gender = gender == 1 ? 0 : 1;
			    		DrawInputGender(x, y, gender);
					}else if( index == 6 ){
						is_delete = is_delete == 1 ? 0 : 1;
			    		DrawTitleYesNo(32, is_delete, state);
					}
			        break;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(index != 4 && temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
			    	if(index == 1){
						strcpy(sv.HO, temp.c_str());
						temp = p->SV.TEN;
						y+=4, index++;
					}else if(index == 2){
						strcpy(sv.TEN, temp.c_str());
						temp = "";
						gender = p->SV.PHAI;
						type = 4, y+=8, index = 4;
						DrawInputGender(x, y, gender);
					}else if(index == 4){
						sv.PHAI = gender;
						temp = p->SV.SODT;
						type = 2, y+=4, index++;
					}else if(index == 5){
						type = 4, y+=4, index++;
						strcpy(sv.SODT, temp.c_str());
						DrawTitleYesNo(32, is_delete, state);
					}else if(index == 6) {
				    	GoToXY(x, y-4);
						printf("%-50s"," ");
						gender = 0;
						DrawInputGender(x, 24, gender-1);
						
						if(is_delete == 0) {
							p->SV = sv;
							Message("SUCCESS:", "Luu Sinh Vien Thanh Cong!", 1, 1000);
						}
				    	return 0;
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "DELETE"){
		DrawInputGender(87, 24, p != NULL ? p->SV.PHAI : -1);
		do{
			c = InputValue(50, temp, x, y, type);
			switch (c) {				
			    case EX_INSERT:
			    case EX_DEL:
			    	ClearButtonYesNo(31);
			    	return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index < 6) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNo(32, is_delete, state);
			        break;
			    case ENTER:
					if(index < 6 && temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
					if(index == 6){
						if(is_delete == 0) {
							Delete_Info_SV(First, sv);
							Message("SUCCESS:", "Xoa Sinh Vien Thanh Cong!", 1, 800);
						}
						return 0;
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
}

void DrawTableSinhVien(char *malophoc, int is_draw_title){
	int pointX = 45, pointY = 5, width = 106, height = 37;
	int col1 = 8, col2 = 22, col3 = 63, col4 = 82, col5 = 90;
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5)
					if(i > 0 && i < height-2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-2)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(HORIZONTAL_LINE);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else if(i%2 == 0){
			for(int j = 0; j < width; j++){
				if(j == 0)
					cout << char(LEFT_CENTER_SIMPLE);
				else if(j == width-1)
					cout << char(RIGHT_CENTER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5)
					if(i == 2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-3)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(PLUS_CENTER);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else {
			cout << char(VERTICAL_LINE);
			
			if(i > 2 && i < height - 2){
				GoToXY(pointX+col1, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col2, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col3, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col4, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col5, pointY+i);
				cout << char(VERTICAL_LINE);
			}
			
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	CountHeaderSinhVienTable(pointX+2, pointY+3);
	
	if(is_draw_title == 0) return;
	DrawHuongDanTable(48, 40, SinhVienFunctionText, NUMBER_ITEM_SINHVIEN_FUNCTION_TEXT);
	
	char title[50];
	strcpy(title, SinhVienText[0]);
	strcat(title, " LOP: ");
	strcat(title, malophoc);
	
	DrawTitle(title, 78);
	DrawTitleTable(87, 1, 1, SinhVienText);
}

void ClearRemainSinhVien(int total, int pointX, int pointY){
	int row2 = 15-total;
	pointY = total*2+pointY;
	for(int i = 0; i < row2;i++){
		GoToXY(pointX, pointY+=2); printf("%-6s", " ");
		GoToXY(pointX + 8, pointY); printf("%-11s", " ");
		GoToXY(pointX + 22, pointY); printf("%-37s", " ");
		GoToXY(pointX + 63, pointY); printf("%-6s", " ");
		GoToXY(pointX + 82, pointY); printf("%-4s", " ");
		GoToXY(pointX + 90, pointY); printf("%-10s", " ");	
	}
}

void PrintDataSinhVien(LISTSV &First, int tab, string state, char *malophoc, int is_new_class){
	int c, a; 
	LISTSV p = NULL;
	
	if(tab == 2){
		char title[50];
		strcpy(title, SinhVienText[0]);
		strcat(title, " LOP: ");
		strcat(title, malophoc);
		
		DrawTitle(title, 78);
		DrawTitleTable(87, 1, tab, SinhVienText);
		do{
			a = ThemSinhVien(First, state, malophoc, is_new_class, p);
			HideTyping();
			switch(a){
				case 0:
					break;				
				case EX_DEL:
					Message("ERROR:", "Dang Tao Moi Khong The Xoa Sua!", 0, 1000);
					break;
				case ESC:
					ClearTable(1);
		        	return;
			}
		    if (a == 0) break;
		} while (1);
		
		ClearTable(0);
		tab = 1;
	}
	
	if(First == NULL){
		Message("ERROR:", "Danh Sach Sinh Vien Rong!", 0, 1000);
		ClearTable(1);
		return;
	}
	
	int total = Reccount_SV(First, malophoc);
	if(total == 0){
		Message("ERROR:", "Danh Sach Sinh Vien Rong!", 0, 1000);
		ClearTable(1);
		return;
	}
	
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int n = (int)ceil((double)total/15);
	int currentPage = 0, select = 0;
	string keyword = "";
	
	LISTSV *pages = new LISTSV[n];
	
	Message("SUCCESS:", "Load Du Lieu Sinh Vien Thanh Cong!", 1, 500);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
	DrawTableSinhVien(malophoc, 1);
	Selection_Sort_SV(First, malophoc);
	Traverse_SV(First, malophoc, stt, pointX, pointY, currentPage, keyword, pages);
	DrawArrowTable(47, 8, select, currentPage, stt);
	PrintSearchInput(47, keyword);
	do {
	    c = InputSearch(keyword, x, y, 50);
	    switch (c) {
	    	case EX_UP:
	    	case EX_DOWN:
	    		if (c == EX_UP &&select + 1 > 1) select--; 
		        else if (c == EX_DOWN && select + 1 < stt) select++;
		        
	    		DrawArrowTable(47, 8, select, currentPage, stt);
	    		PrintSearchInput(47, keyword);
	    		break;
		    case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	if(tab ==  2) break;
		    	
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;

		        HideTyping();
				Traverse_SV(First, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				
				if(currentPage == n-1)
					ClearRemainSinhVien(stt, pointX, pointY);
				
				PrintSearchInput(47, keyword);
				
		        break;
		    case EX_INSERT:
		    case TAB: 
		    	tab = (tab == 1) ? 2 : 1;
		    	DrawTitleTable(87, 1, tab, SinhVienText);
		    	if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTable(0);
				    PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
					DrawTableSinhVien(malophoc, 1);
					Selection_Sort_SV(First, malophoc);
					Traverse_SV(First, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
					DrawArrowTable(47, 8, select, currentPage, stt);
					PrintSearchInput(47, keyword);
				}else{
					ClearTable(0);
					do{
						a = ThemSinhVien(First, "NEW", malophoc, is_new_class, p);
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
				    		PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
							DrawTableSinhVien(malophoc, 1);
							Selection_Sort_SV(First, malophoc);
							Traverse_SV(First, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
							DrawArrowTable(47, 8, select, currentPage, stt);
							PrintSearchInput(47, keyword);
							p = NULL;
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else if(a == EX_F3 || a == EX_DEL){
							Message("ERROR:", "Ban Dang Tao Moi Khong The Xoa Sua!", 0, 1500);
						} 
					}while(1);
				}
		    	break;		    
			case EX_DEL:
			case ENTER:
				{
					if(stt == 0){
						Message("ERROR:", "Sinh Vien Khong Hop Le!", 0, 500);
						GoToXY(x+keyword.length(), y);
						break;
					}
					
					tab = 2;
			    	if(select > -1){
			    		p = Search_Info_SV_By_STT(First, malophoc, keyword, select, currentPage ,pages);
			    		select = 0;
					}
					ClearTable(0);
					DrawTitleTable(87, 1, tab, SinhVienText);
					string state2 = c == EX_DEL ? "DELETE" : "EDIT";
					do{
						a = ThemSinhVien(First, state2, malophoc, is_new_class, p);
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
					    	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
							DrawTableSinhVien(malophoc, 1);
							Selection_Sort_SV(First, malophoc);
							Traverse_SV(First, malophoc, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
							DrawArrowTable(47, 8, select = 0, currentPage, stt);
							PrintSearchInput(47, keyword);
							p = NULL;
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else {
							if(state2 == "NEW"){
								Message("ERROR:", "Ban Dang Tao Moi Khong The Xoa Sua!", 0, 1500);
							}else{
								HideTyping();
								if(a == EX_INSERT) p = NULL;	
								state2 = a == EX_INSERT ? "NEW" : ( a == EX_F3 ? "EDIT" : "DELETE");
							}
							
						} 
					}while(1);
					break;
				}
		    case CTRL_F:
		    	if(tab ==  2) break;
				Traverse_SV(First, malophoc, stt = 0, pointX, pointY = 8, currentPage = 0, keyword, pages);
				ClearRemainSinhVien(stt, pointX, pointY = 8);
				total = Reccount_SV_With_Keyword(First, malophoc, keyword);
				n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintKeyWord("%-50s", keyword, x, y);
		    	break;
		    case ESC:
		    	delete[] pages;
		    	ClearTable(1);
		        return;
	    }
	} while (1);
}

/*
* === END ===
*/



/*
* — Ham xu ly voi cay nhi phan can bang —
*/

void InitializeTree(TREE &root){
   root = NULL;
}

int ReccountTree(TREE root){
	if (root != NULL)
		return (ReccountTree(root->left) + ReccountTree(root->right) + 1);
	else return 0;
}

int Reccount_MH_With_Keyword(TREE root, string &keyword){
	if( root == NULL ) return 0;
	
	int count = 0;
	TREE p = root;
	while(p != NULL ){
		string ten = convertToString(p->MH.TENMH, strlen(p->MH.TENMH));
        string ma = convertToString(p->MH.MAMH, strlen(p->MH.MAMH));
        if(ten.find(keyword) != string::npos || ma.find(keyword) !=  string::npos) count++;
		p = p->right;
	}
	return count;
}

TREE Rotate_Left(TREE root){
    TREE p;
    if (root == NULL)
        Message("Loi Cau Truc:", "Khong the xoay trai vi cay bi rong.", 0, 1000);
    else if (root->right == NULL)
    	Message("Loi Cau Truc:", "Khong the xoay trai vi khong co nut con ben phai.", 0, 1000);
    else
    {
        p = root->right;
        root->right = p->left;
        p->left = root;
    }
    return p;
}

TREE Rotate_Right(TREE ya){
    TREE s;
    if (ya == NULL)
    	Message("Loi Cau Truc:", "Khong the xoay phai vi cay bi rong.", 0, 1000);
    else if (ya->left == NULL)
        Message("Loi Cau Truc:", "Khong the xoay phai vi khong co nut con ben trai.", 0, 1000);
    else
    {
        s = ya->left;
        ya->left = s->right;
        s->right = ya;
    }
    return s;
}

void Insert_Node(TREE& pavltree, MonHoc x){
    TREE fp, p, q, fya, ya, s; 
    int imbal;
    fp = NULL;
    p = pavltree;
    fya = NULL;
    ya = p;
    while (p != NULL)
    {
        if (strcmp(x.MAMH, p->MH.MAMH) == 0)
            return;
        if (strcmp(x.MAMH, p->MH.MAMH) < 0)
            q = p->left;
        else
            q = p->right;
        if (q != NULL)
            if (q->bf != 0)
            {
                fya = p;
                ya = q;
            }
        fp = p;
        p = q;
    }
    q = new NodeMH;
    q->MH = x;
    q->bf = 0;
    q->left = NULL;
    q->right = NULL;
    if (strcmp(x.MAMH, fp->MH.MAMH) < 0)
        fp->left = q;
    else
        fp->right = q;
  
    if (strcmp(x.MAMH, ya->MH.MAMH) < 0)
        p = ya->left;
    else
        p = ya->right;
    s = p; 
    while (p != q)
    {
        if (strcmp(x.MAMH, p->MH.MAMH) < 0)
        {
            p->bf = 1;
            p = p->left;
        }
        else
        {
            p->bf = -1;
            p = p->right;
        }
    }

    if (strcmp(x.MAMH, ya->MH.MAMH) < 0)
        imbal = 1;
    else
        imbal = -1;

    if (ya->bf == 0)
    {
        ya->bf = imbal;
        return;
    }
    if (ya->bf != imbal)
    {
        ya->bf = 0;
        return;
    }

    if (s->bf == imbal)
    {
        if (imbal == 1)
            p = Rotate_Right(ya);
        else 
            p = Rotate_Left(ya);
        ya->bf = 0;
        s->bf = 0;
    }
    else
    {
        if (imbal == 1)
        {
            ya->left = Rotate_Left(s);
            p = Rotate_Right(ya);
        }
        else 
        {
            ya->right = Rotate_Right(s);
            p = Rotate_Left(ya);
        }
        if (p->bf == 0)
        {
            ya->bf = 0;
            s->bf = 0;
        }
        else if (p->bf == imbal)
        {
            ya->bf = -imbal;
            s->bf = 0;
        }
        else
        {
            ya->bf = 0;
            s->bf = imbal;
        }
        p->bf = 0;
    }
    if (fya == NULL)
        pavltree = p;
    else if (ya == fya->right)
        fya->right = p;
    else
        fya->left = p;
}

void Traverse_DSMH(TREE DSMH, int &stt, int &pointX, int pointY, int currentPage, string &keyword, TREE *pages){
   	TREE p;
   	if(currentPage == 0)
    	p = DSMH;
	else 
		p = pages[currentPage];
		
   	while(p != NULL)
   	{
   		if( stt < 16 ){
    		string ten = convertToString(p->MH.TENMH, strlen(p->MH.TENMH));
        	string ma = convertToString(p->MH.MAMH, strlen(p->MH.MAMH));
        	if(ten.find(keyword) != string::npos || ma.find(keyword) !=  string::npos){
        		if(stt == 15){
        			if(pages[currentPage+1] == NULL)
	    				pages[currentPage+1] = p;
	    			return;
				}
	    		if(stt == 0 && pages[currentPage] == NULL){
	    			pages[currentPage] = p;
				}
	    		GoToXY(pointX, pointY+=2);
	    		++stt;
	    		if(stt == 16) break;
	    		CoutNodeMH(p->MH, stt + 15*currentPage, pointX, pointY);
			}
		}
      	p = p->right;
   	}
}

TREE Search_By_STT_DSMH(TREE DSMH, int select, int currentPage, string &keyword, TREE *pages){
   	TREE p = NULL;
   	if(currentPage == 0)
    	p = DSMH;
	else 
		p = pages[currentPage];
	
	int stt = 0;
   	while(p != NULL)
   	{
   		if( stt < 16 ){
    		string ten = convertToString(p->MH.TENMH, strlen(p->MH.TENMH));
        	string ma = convertToString(p->MH.MAMH, strlen(p->MH.MAMH));
        	if(ten.find(keyword) != string::npos || ma.find(keyword) !=  string::npos){
	    		++stt;
	    		if(select == stt-1) return p;
			}
		}
      	p = p->right;
   	}
   	return NULL;
}

void Selection_Sort_DSMH(TREE &DSMH){
    if(DSMH == NULL)return; 
	TREE p, q, pmin;
	MonHoc min;
	for(p = DSMH; p->right != NULL; p = p->right)
	{
		min = p->MH;
		pmin = p;
		for(q = p->right; q != NULL; q = q->right)
		if( strcmp(q->MH.TENMH, min.TENMH) < 0 )
		{
			min = q->MH;
			pmin = q;
		}
		pmin->MH = p->MH;
		p->MH = min;
	}
}

void Insert_Last_DSMH(TREE &DSMH, MonHoc x){
    TREE p = new NodeMH;
    p->MH = x;
    p->right = NULL;
    p->left = NULL;
    p->bf = 0;
    
    if(DSMH == NULL) 
		DSMH = p;
    else{
      	TREE Last = DSMH;
      	for(; Last->right != NULL; Last = Last->right);
      	Last->right = p;
	}
}

void Inorder(TREE p, TREE &DSMH){
    if (p != NULL)
    {
        Inorder(p->left, DSMH);
        Insert_Last_DSMH(DSMH, p->MH);
        Inorder(p->right, DSMH);
    }
}

TREE SearchNodeMH(TREE root, char *mamh){
   if (root == NULL)
        return NULL;
        
	if(strcmp(mamh, root->MH.MAMH ) == 0 )
			return root;
    	if(strcmp(mamh, root->MH.MAMH ) < 0)
    		SearchNodeMH(root->left, mamh);
    	else
         	SearchNodeMH(root->right, mamh);
}

TREE MinimumNodeMH(TREE curr){
	while(curr->left != NULL) {
		curr = curr->left;
	}
	return curr;
}

TREE DeleteMH(TREE& root, char* mamh){
    if (root == NULL) return root; 
  
    if (strcmp(mamh, root->MH.MAMH) < 0) 
        root->left = DeleteMH(root->left, mamh); 
  
    else if (strcmp(mamh, root->MH.MAMH) > 0) 
        root->right = DeleteMH(root->right, mamh); 
  
    else
    { 
        if (root->left == NULL) 
        { 
            TREE temp = root->right; 
            delete root; 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            TREE temp = root->left; 
            delete root; 
            return temp; 
        } 
  
        TREE temp = MinimumNodeMH(root->right); 
  
        root->MH = temp->MH; 
  
        root->right = DeleteMH(root->right, temp->MH.MAMH); 
    }  
    return root;
}

int DeleteMH_DSMH(TREE &DSMH, char *mamh){  
	TREE p = DSMH, q;
  	if (DSMH == NULL ) return 0;
  	if ( strcmp(DSMH->MH.MAMH, mamh) == 0 ) {
	    p = DSMH;
		DSMH = p->right;
		delete p;
		
		return 1;
	}
    
	for ( p = DSMH; p->right!=NULL && strcmp(p->right->MH.MAMH, mamh) != 0; p = p->right);
	if (p->right!= NULL ) {
		q = p->right; 
		p->right = q->right;
		delete q; 
		return 1;
	}
	return 0;
}

void DeleteAllTree ( TREE &DSMH){  
if ( DSMH == NULL )
    return;
 
  DeleteAllTree ( DSMH->left );
  DeleteAllTree ( DSMH->right );
  delete DSMH;
}

void ClearRemainMonHoc(int total, int pointX, int pointY, int currentPage){
	int row2 = 15-total;
	pointY = total*2+pointY;
	for(int i = 0; i < row2;i++){
		GoToXY(pointX, pointY+=2); printf("%-6s", " ");
		GoToXY(pointX + 8, pointY); printf("%-11s", " ");
		GoToXY(pointX + 22, pointY); printf("%-60s", " ");
		GoToXY(pointX + 84, pointY); printf("%-8s", " ");
		GoToXY(pointX + 95, pointY); printf("%-8s", " ");
	}
}

void DrawTableMonHoc(int is_draw_title){
	int pointX = 45, pointY = 5, width = 106, height = 37;
	int col1 = 8, col2 = 22, col3 = 84, col4 = 95;
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4)
					if(i > 0 && i < height-2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-2)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(HORIZONTAL_LINE);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else if(i%2 == 0){
			for(int j = 0; j < width; j++){
				if(j == 0)
					cout << char(LEFT_CENTER_SIMPLE);
				else if(j == width-1)
					cout << char(RIGHT_CENTER_SIMPLE);
				else if(j == col1 || j == col2 || j == col3 || j == col4)
					if(i == 2)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-3)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(PLUS_CENTER);
				else cout << char(HORIZONTAL_LINE);
			}
		}
		else {
			cout << char(VERTICAL_LINE);
			
			if(i > 2 && i < height - 2){
				GoToXY(pointX+col1, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col2, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col3, pointY+i);
				cout << char(VERTICAL_LINE);
				
				GoToXY(pointX+col4, pointY+i);
				cout << char(VERTICAL_LINE);
			}
			
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	CountHeaderMonHocTable(pointX+2, pointY+3);
	if(is_draw_title == 0) return;
	DrawHuongDanTable(48, 40, MonHocFunctionText, NUMBER_ITEM_MONHOC_FUNCTION_TEXT);
	
	DrawTitle(MonHocText[0], 87);
	
	DrawTitleTable(87, 1, 1, MonHocText);
}

void InorderFile(TREE p, ofstream &outfile){
    if (p != NULL)
    {
        InorderFile(p->left, outfile);
        outfile << p->MH.MAMH << "\t" << p->MH.STCLT << "\t" << p->MH.STCTH << "\t" << p->MH.TENMH << "\n";
        InorderFile(p->right, outfile);
    }
}

void SaveFileMonHoc(){
	char filename[50] = "data\\DSMH.TXT";
	ofstream outfile;
    outfile.open(filename, ios::out );
    InorderFile(tree, outfile);
    outfile.close();
}

void Load_MonHoc(){
	InitializeTree(tree);
	char filename[50] = "data\\DSMH.TXT";
	MonHoc x;
  	ifstream file(filename);
	
	if (!file.is_open())
	{
		return;
	}
	
	string temp;
	while (!file.eof())
	{
		file >> temp;
		if(temp == "\n" || temp == "") break;
		file >> x.STCLT >> x.STCTH;
		strcpy(x.MAMH, temp.c_str());
		file.ignore(1);
		file.getline(x.TENMH, 256);
		
		TREE p = SearchNodeMH(tree, x.MAMH);
		if(p != NULL) continue;
		if(tree == NULL)
	    {
	     	TREE p = new NodeMH;
	     	p->MH = x;
	        p->bf = 0;
	        p->left = NULL;
	        p->right = NULL;
	        tree = p;
	   	}
		else
			Insert_Node(tree, x);
	}
	file.close();
}

void CountHeaderMonHocTable(int pointX, int pointY){
	GoToXY(pointX, pointY); cout << "STT";
	GoToXY(pointX + 8, pointY); cout << "MAMH";
	GoToXY(pointX + 22, pointY); cout << "Ten Mon Hoc";
	GoToXY(pointX + 84, pointY); cout << "STCLT";
	GoToXY(pointX + 95, pointY); cout << "STCTH";
}

void CoutNodeMH(MonHoc p, int stt, int pointX, int pointY){
	HideTyping();
	GoToXY(pointX, pointY); printf("%-6d", stt);
	GoToXY(pointX + 8, pointY); printf("%-11s", p.MAMH);
	GoToXY(pointX + 22, pointY); printf("%-60s", p.TENMH);
	GoToXY(pointX + 84, pointY); printf("%-8d", p.STCLT);
	GoToXY(pointX + 95, pointY); printf("%-8d", p.STCTH);	
}

void DrawBoderThemMonHoc(string title){
	int pointX = 55, pointY = 5, width = 90, height = 21;
	
	SetColor(RED);
	GoToXY(pointX+30, pointY+1);
	printf("%-50s", title.c_str());
	SetColor(BLACK);
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	DrawTitleFunction(pointX+15, pointY+20, MonHocFunctionText, NUMBER_ITEM_MONHOC_FUNCTION_TEXT, 1);
	
	for(int i = 0; i < NUMBER_ITEM_MONHOCTEXT; i++){
		GoToXY(pointX+5, pointY+3+i*4);
		cout << ThemMonHocText[i];
		DrawInput(85, pointY+2+i*4);
	}
	GoToXY(87, 8);
	Typing();

}

int ThemMonHoc(TREE &DSMH, string state, TREE p){
	MonHoc mh;
	int x = 87, y = 8, c, type = 0, is_delete = 0, length = 10;
	string temp = "";
	
	if(state == "NEW"){
		DrawBoderThemMonHoc("NHAP THONG TIN DE THEM MON HOC!");
	}
	else if(state == "EDIT"){
		DrawBoderThemMonHoc("NHAP MA MON HOC DE CHINH SUA!");
		if(p != NULL){
			DrawButtonYesNo(22, state);
								
			GoToXY(x, y);
			SetColor(RED);
			printf("%-50s", p->MH.MAMH);
			SetColor(BLACK);
								
			GoToXY(x, y+=4);
			printf("%-50s", p->MH.TENMH);
								
			GoToXY(x, y+=4);
			printf("%-50d", p->MH.STCLT);
								
			GoToXY(x, y+=4);
			printf("%-50d", p->MH.STCTH);
								
			y = y-8;
			type = 1;
			temp = p->MH.TENMH;
			strcpy(mh.MAMH, p->MH.MAMH);
			GoToXY(x + temp.length(), y);
		}
		
	}
	else if(state == "DELETE"){
		DrawBoderThemMonHoc("NHAP MA MON HOC DE XOA!");
		if(p != NULL){
			GoToXY(x, y);
			SetColor(RED);
			printf("%-50s", p->MH.MAMH);
						
			GoToXY(x, y+=4);
			printf("%-50s", p->MH.TENMH);
							
			GoToXY(x, y+=4);
			printf("%-50d", p->MH.STCLT);
							
			GoToXY(x, y+=4);
			printf("%-50d", p->MH.STCTH);
			SetColor(BLACK);
						
			type = 4;
			GoToXY(x , y);
			is_delete = 0;
			DrawButtonYesNo(22, state);
			DrawTitleYesNo(23, is_delete, state);
		}
	}


	if(state == "NEW"){
		do{
			c = InputValue(length, temp, x, y, type);
			switch (c) {				
			    case EX_DEL:
			    	ClearButtonYesNo(22);
			        return c;
				case TAB:
			        return 0;
			    case ENTER:
			    	if(type == 0){
			    		strcpy(mh.MAMH, temp.c_str());
			    		p = SearchNodeMH(tree, mh.MAMH);
			    		if(p != NULL) {
			    			Message("ERROR:", "Ma Mon Hoc Da Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
						length = 50;
					}else if(type == 1){
						if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
						strcpy(mh.TENMH, temp.c_str());
						length = 2;
					}else if(type == 2){
						sscanf(temp.c_str(), "%d", &mh.STCLT);
					}else if(type == 3){
						sscanf(temp.c_str(), "%d", &mh.STCTH);
					}
					if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					temp = "";
				    type++;
				    if(type == 4) {
				    	type = 0, y = 4, length = 10;
				    	if(tree == NULL)
					    {
					     	TREE p = new NodeMH;
					     	p->MH = mh;
					        p->bf = 0;
					        p->left = NULL;
					        p->right = NULL;
					        tree = p;
					   	}
						else Insert_Node(tree, mh);
						
						Insert_Last_DSMH(DSMH, mh);
						
				    	ClearInput(x, y, 4);
				    	Message("SUCCESS:", "Them Mon Hoc Thanh Cong!", 1, 1000);
					}
					GoToXY(x, y+=4);
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "EDIT"){
		do{
			c = InputValue(50, temp, x, y, type);
			switch (c) {				
			    case EX_INSERT:
			    case EX_DEL:
			    	ClearButtonYesNo(22);
			        return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(type < 3) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNo(23, is_delete, state);
			        break;
			    case ENTER:
			    	if(type < 4 && temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
			    	if(type == 1){
						if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
						strcpy(mh.TENMH, temp.c_str());
						temp = ConvertIntToString(p->MH.STCLT );
						y+=4, type++;
					}else if(type == 2){
						sscanf(temp.c_str(), "%d", &mh.STCLT);
						temp = ConvertIntToString(p->MH.STCTH );
						y+=4, type++;
					}else if(type == 3){
						sscanf(temp.c_str(), "%d", &mh.STCTH);
						temp = "";
						y+=4, type++;
						DrawTitleYesNo(23, is_delete, state);
					}else if(type == 4){
						if(is_delete == 0) {
							p->MH = mh;
							Message("SUCCESS:", "Luu Mon Hoc Thanh Cong!", 1, 800);
						}
						return 0;
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "DELETE"){
		do{
			c = InputValue(50, temp, x, y, type);
			switch (c) {				
			    case EX_INSERT:
			    case EX_DEL:
			    	ClearButtonYesNo(22);
			    	return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(type < 3) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNo(23, is_delete, state);
			        break;
			    case ENTER:
					if(type < 4 && temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					if(type == 4){
						if(is_delete == 0) {
							tree = DeleteMH(tree, p->MH.MAMH);
							DeleteMH_DSMH(DSMH, p->MH.MAMH);
							Message("SUCCESS:", "Xoa Mon Hoc Thanh Cong!", 1, 800);
						}
						return 0;
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
}

void LoadLopTCDaDK(DSLOPTINCHI plist, int *list_dk, int &n2, char* masinhvien){
	for(int i = 0; i < plist.N; i++){
		if(CheckExist_SV(plist.LOP[i]->DSDK, masinhvien)){
			list_dk[n2]	= i;
			n2++;
		}
	}
}

void DrawTableLopTCPlus(DSLOPTINCHI &dsltc_temp, char *nienkhoa, int hocky, char* masinhvien){
	int c, a, p;
	int total = dsltc_temp.N;
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int n = (int)ceil((double)total/15);
	int n2 = 0;
	int currentPage = 0, select = 0;
	string keyword = "";

	
	Message("SUCCESS:", "Load Du Lieu Lop Tin Chi Thanh Cong!", 1, 500);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
	DrawTableLopTinChiPlus();
	
	int *list_dk = new int[total];
	
	LoadLopTCDaDK(dsltc_temp, list_dk, n2, masinhvien);
	
	Traverse_LTC_Plus(dsltc_temp, pointX, pointY, currentPage, stt, keyword, total, list_dk, n2);
	DrawArrowTable(47, 8, select = 0, currentPage, stt);
	PrintSearchInput(47, keyword);
	
	do {
	    c = InputSearch(keyword, x, y, 50);
	    switch (c) {
	    	case EX_UP:
	    	case EX_DOWN:
	    		if (c == EX_UP &&select + 1 > 1) select--; 
		        else if (c == EX_DOWN && select + 1 < stt) select++;
		        
	    		DrawArrowTable(47, 8, select, currentPage, stt);
	    		PrintSearchInput(47, keyword);
	    		break;
		    case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
		        Traverse_LTC_Plus(dsltc_temp, pointX, pointY, currentPage, stt, keyword, total, list_dk, n2);
		        n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				
				if(currentPage == n-1)
						ClearRemainLopTinChiPlus(stt, pointX, pointY);
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintSearchInput(47, keyword);
				
		    	break;
		    case EX_INSERT:
		    	{
		    		
		    		DANGKY dk;
					dk.DIEM = 0;
					strcpy(dk.MASV, masinhvien);
					
					for(int i = 0; i < dsltc_temp.N; i++)
						Delete_Info_DK(dsltc_temp.LOP[i]->DSDK, dk);
					
					
					for(int i = 0; i < n2; i++)
						Insert_Last_DK(dsltc_temp.LOP[list_dk[i]]->DSDK, dk);
					
					for(int i = 0; i < dsltc_temp.N; i++)
						SaveFileListDK(dsltc_temp.LOP[i]->DSDK, dsltc_temp.LOP[i]->MALOPTC);
	
					
					HideTyping();
					Message("SUCCESS:", "Luu Ket Qua Dang Ky Thanh Cong!", 1, 500);
					GoToXY(x+keyword.length(), y);
				
					break;
					
				}
		    case ENTER:
		    	{
		    		
					if(stt == 0){
						Message("ERROR:", "Lop Tin Chi Khong Hop Le!", 0, 500);
						GoToXY(x+keyword.length(), y);
						break;
					}
					p = Search_Info_LTC_By_STT(dsltc_temp, keyword, currentPage, select);
					
					HideTyping();
					GoToXY(54, 10 + select*2);
					if(AddLopTC(list_dk, p , n2)){
						cout << char (219) << char (219) << char (219);
					}else{
						cout << "   ";
					}
					GoToXY(x+keyword.length(), y);
					
					break;
				}
		    case CTRL_F:
				Traverse_LTC_Plus(dsltc_temp, pointX, pointY, currentPage = 0, stt, keyword, total, list_dk, n2);
				ClearRemainLopTinChi(stt, pointX, pointY = 8);
				n = (int)ceil((double)total/15);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
		    case ESC:
		    	delete list_dk;
		    	ClearTable(1);
		        return;
	    }
	} while (1);
	
}

void DrawBorderEditMonHoc(){
	int pointX = 65, pointY = 15, width = 70, height = 13;
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			printf("%-69s"," ");
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
}

void PrintDataMonHoc(int tab, string state){
	
	TREE DSMH = NULL, p = NULL;
	int c, a;
	
	if(state !="NEW" && tree == NULL){
		Message("ERROR:", "Danh Sach Mon Hoc Rong!", 0, 1000);
		return;
	}
	
	Inorder(tree, DSMH); 
	
	if(tab == 2){
		DrawTitle(MonHocText[0], 87);
		DrawTitleTable(87, 1, tab, MonHocText);
		do{
			a = ThemMonHoc(DSMH, state, p);
			HideTyping();
			switch(a){
				case 0:
					break;				
				case EX_DEL:
					Message("ERROR:", "Dang Tao Moi Khong The Xoa Sua!", 0, 1000);
					break;
				case ESC:
					ClearTable(1);
		        	return;
			}
		    if (a == 0) break;
		} while (1);
		
		ClearTable(0);
		tab = 1;
	}
	
	if(tree == NULL){
		Message("ERROR:", "Danh Sach Mon Hoc Rong!", 0, 1000);
		ClearTable(1);
		return;
	}
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = ReccountTree(tree);
	int n = (int)ceil((double)total/15);
	int currentPage = 0, select = 0;
	string keyword = "";
	
	TREE *pages = new TREE[n];
	
	Selection_Sort_DSMH(DSMH);
	
	Message("SUCCESS:", "Load Du Lieu Mon Hoc Thanh Cong!", 1, 500);
	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
	DrawTableMonHoc(1);
	Traverse_DSMH(DSMH, stt, pointX, pointY, currentPage, keyword, pages);
	DrawArrowTable(47, 8, select, currentPage, stt);
	PrintSearchInput(47, keyword);
	
	
	do {
	    c = InputSearch(keyword, x, y, 50);
	    switch (c) {
	    	case EX_UP:
	    	case EX_DOWN:
	    		if (c == EX_UP &&select + 1 > 1) select--; 
		        else if (c == EX_DOWN && select + 1 < stt) select++;
		        
	    		DrawArrowTable(47, 8, select, currentPage, stt);
	    		PrintSearchInput(47, keyword);
	    		break;
		    case EX_PAGEUP:
		    case EX_PAGEDOWN:
		    	if(tab ==  2) break;
		    	
		    	if (c == EX_PAGEUP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_PAGEDOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
				Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword, pages);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				
				if(currentPage == n-1)
						ClearRemainMonHoc(stt, pointX, pointY, currentPage);
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintSearchInput(47, keyword);
				
		        break;
		    case EX_INSERT: 
		    case TAB: 
		    	tab = (tab == 1) ? 2 : 1;
		    	DrawTitleTable(87, 1, tab, MonHocText);
		    	if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTable(0);
		    		PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
					DrawTableMonHoc(1);
					Selection_Sort_DSMH(DSMH);
					Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword, pages);
					DrawArrowTable(47, 8, select, currentPage, stt);
					PrintSearchInput(47, keyword);
				}else{
					ClearTable(0);
					do{
						a = ThemMonHoc(DSMH, "NEW", p);
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
				    		PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
							DrawTableMonHoc(1);
							Selection_Sort_DSMH(DSMH);
							Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
							DrawArrowTable(47, 8, select, currentPage, stt);
							PrintSearchInput(47, keyword);
							p = NULL;
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else if(a == EX_F3 || a == EX_DEL){
							Message("ERROR:", "Ban Dang Tao Moi Khong The Xoa Sua!", 0, 1500);
						} 
					}while(1);
				}
		    	break;
			case CTRL_F:
		    	if(tab ==  2) break;
		    	select = 0;
				Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage = 0, keyword, pages);
				ClearRemainMonHoc(stt, pointX, pointY = 8, 0);
				
				total = Reccount_MH_With_Keyword(DSMH, keyword);
				n = (int)ceil((double)total/15);
				
				DrawArrowTable(47, 8, select = 0, currentPage, stt);
				PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
				PrintKeyWord("%-50s", keyword, x, y);
				
				break;			
			case EX_DEL:
			case ENTER:
				{
					if(stt == 0){
						Message("ERROR:", "Mon Hoc Khong Hop Le!", 0, 500);
						GoToXY(x+keyword.length(), y);
						break;
					}
					
					tab = 2;
			    	if(select > -1){
			    		p = Search_By_STT_DSMH(DSMH, select, currentPage, keyword, pages);
			    		select = 0;
					}
					ClearTable(0);
					DrawTitleTable(87, 1, tab, MonHocText);
					string state2 = c == EX_DEL ? "DELETE" : "EDIT";
					do{
						a = ThemMonHoc(DSMH, state2, p);
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
					    	PrintPageTable(n > 0 ? currentPage+1 : 0, n, 140);
							DrawTableMonHoc(1);
							Selection_Sort_DSMH(DSMH);
							Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
							DrawArrowTable(47, 8, select, currentPage, stt);
							PrintSearchInput(47, keyword);
							p = NULL;
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else {
							if(state2 == "NEW"){
								Message("ERROR:", "Ban Dang Tao Moi Khong The Xoa Sua!", 0, 1500);
							}else{
								HideTyping();
								if(a == EX_INSERT) p = NULL;	
								state2 = a == EX_INSERT ? "NEW" : ( a == EX_F3 ? "EDIT" : "DELETE");
							}
							
						} 
					}while(1);
					break;
				}
		    case ESC:
		    	DeleteAllTree(DSMH);
		    	delete[] pages;
		    	ClearTable(1);
		        return;
	    }
	} while (1);
}

void DrawBorderNhap(int pointX, int pointY){
	int width = 90, height = 8;
	SetColor(RED);
	GoToXY(pointX+34, pointY+1);
	printf("%-50s", "NHAP THONG TIN SINH VIEN!");
	SetColor(BLACK);
	
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	int index = 0;
	GoToXY(pointX+5, pointY+3+index*4);
	printf("%-30s", ThemSinhVienText[index]);
	DrawInput(85, pointY+2+index*4);
	
	GoToXY(87, 8);
	HideTyping();

}

void DrawInfoSinhVien(int pointX, int pointY, SinhVien sv){
	HideTyping();
	int width = 60, height = 4;
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	GoToXY(87, 2);
	cout << sv.HO << " " <<  sv.TEN << " ( "  <<  sv.MASV  << " ) ";
	GoToXY(79, 3);
	printf("LOP: %-15sSDT: %-15sPHAI: %-5s", sv.MALOP, sv.SODT, sv.PHAI == 0 ? "Nu" : "Nam" );

}

void DrawNhapNienKhoaHocKy(int pointX, int pointY){

	int width = 90, height = 10;
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		printf("%-90s", " ");
	}
	SetColor(RED);
	GoToXY(pointX+34, pointY+1);
	printf("%-50s", "NHAP THONG TIN LOP TIN CHI!");
	SetColor(BLACK);
	
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		if(i == 0 || i == height-1){
			for(int j = 0; j < width; j++){
				if(j == 0)
					if(i == height-1)
						cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
					else 
						cout << char(TOP_LEFT_CORNER_SIMPLE);
				else if(j == width-1)
					if(i == height-1)
						cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
					else 
						cout << char(TOP_RIGHT_CORNER_SIMPLE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
	
	int index = 1;
	GoToXY(pointX+5, pointY+3+(index-1)*4);
	printf("%-30s", ThemLopTinChiText[index]);
	DrawInput(85, pointY+2+(index-1)*4);
	
	index = 2;
	GoToXY(pointX+5, pointY+3+(index-1)*4);
	printf("%-30s", ThemLopTinChiText[index]);
	DrawInput(85, pointY+2+(index-1)*4);
	
	GoToXY(87, pointY+3);
	Typing();
}

void DrawNhapMaSinhVien(){
	int x = 75, y = 10, type = 0, length = 15;
	DrawBorderNhap(x-20, y);
	string temp = "";
	x = x+12, y = y+3;
	int c, stt;
	
	SinhVien sv;
	LISTSV p;
	TREE mh;
	do{
		c = InputValue(length, temp, x, y, type);
			switch (c) {
			    case ENTER:
			    	{
			    		if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    		if(temp.length() == 0){
			    			Message("ERROR:", "Vui long khong de trong!", 0, 1000);
			    			break;
						}
			    		strcpy(sv.MASV, temp.c_str());
			    		
			    		p = Search_Info_SV(First, sv);
			    		if(p == NULL) {
			    			Message("ERROR:", "Ma Sinh Vien Khong Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
						
						DrawInfoSinhVien(73, 1, p->SV);
						// ve khung nhap nien khoa va hoc ky
						DrawNhapNienKhoaHocKy(55, y-3);
						
						type = 7, temp = "";
						int hocky;
						char nienkhoa[15];
						DSLOPTINCHI dsltc_temp;
						do{
							c = InputValue(length, temp, x, y, type);
							if(c == ENTER){
								if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
								if(temp.length() == 0){
								    Message("ERROR:", "Vui long khong de trong!", 0, 1000);
								    break;
								}
								
								if(type == 7){
									strcpy(nienkhoa, temp.c_str() );
									temp = "";
									y+=4, type = 2, length = 1;
								}else if(type == 2){
									sscanf(temp.c_str(), "%d", &hocky);
									temp = "";
									
									Load_Into_Temp(dsloptc, dsltc_temp, nienkhoa, hocky);
									if(dsltc_temp.N == 0){
										Message("ERROR:", "Danh Sach Lop Tin Chi Rong!", 0, 1000);
										GoToXY(x, y); cout << "   ";
										y-=4, type = 7, length = 15, temp = nienkhoa;
									}else break;
								}
								
							}else if(c == ESC){
								ClearTable(1);
								return;
							}
						}while(1);
						
						ClearTable(0);
						DrawTableLopTCPlus(dsltc_temp, nienkhoa, hocky, sv.MASV);
						return;
					}
			    case ESC:
			    	ClearTable(1);
			        return;
			}
	}while(1);
}


/*
* === END ===
*/





void LoadAllDataFromFile(){
	Load_MonHoc();
	Load_SinhVien();
	Load_LopTC();
}

void ClearListAll(){
	ClearListSV(First);
	DeleteAllTree(tree);
	ClearList_LH(ListLop);
	ClearList_LopTC(dsloptc);
}
