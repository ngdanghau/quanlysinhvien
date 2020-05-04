#include "structs.h"
#include "../constant.h"
#include "../mylib/console.h"
#include "../mylib/helpers.h"
/*
* — Khai bao bien toan cuc —
*/
TREE tree = NULL;
DSLOPPTR ListLop;
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
char DanhSachDangKyText[NUMBER_ITEM_DANGSACHDANGKYTEXT][MENU_TEXT_LENGTH] = {
		"BANG DANH SACH DANG KY",
		" MO DS DANG KY ",
		" BANG DS LOP TC "
};

/*
* === END ===
*/

void Initialize_DK(LISTDK& First){
    First = NULL;
}

int Reccount_DK(LISTDK &First) {
	if(First == NULL) return 0;
	
	int count = 0;
	LISTDK p = First;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

int Reccount_DK_WITH_ADD_SV(LISTDK &FirstDK, LISTSV &DSSV) {
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
	
	if (!file.is_open())
	{
		return;
	}
	
	string temp;
	while (!file.eof())
	{
		file >> temp >> x.DIEM;
		strcpy(x.MASV, temp.c_str());
		Insert_Last_DK(First, x);
	}
	file.close();
}



/*
* — Tieu De Cho Chuc Nang Lop Tin Chi —
*/
const int NUMBER_ITEM_LOPTINCHITEXT = 7;
char LopTinChiText[NUMBER_ITEM_LOPTINCHITEXT][MENU_TEXT_LENGTH] = {
		"BANG DANH SACH LOP TIN CHI",
		" BANG DANH SACH ",
		" THEM MOI/CHINH SUA ",
		" DANH SACH MON HOC "
};

char ThemLopTinChiText[NUMBER_ITEM_LOPTINCHITEXT][MENU_TEXT_LENGTH] = {
		"MA LOP TIN CHI: ",
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
			"F3",
			"DEL",
			"INSERT",
			"ENTER"
		},
		{
			": Chuyen Tab",
			": Chinh Sua",
			": Xoa",
			": Them",
			": Xac Nhan"
		}
};
/*
* === END ===
*/
void ClearRemainLopTinChi(int total, int pointX, int pointY){
	int row2 = 15-total;
	pointY = total*2+pointY;
	for(int i = 0; i < row2;i++){
		GoToXY(pointX, pointY+=2); printf("%-6s", " ");
		GoToXY(pointX + 10, pointY); printf("%-8s", " ");
		GoToXY(pointX + 20, pointY); printf("%-11s", " ");
		GoToXY(pointX + 33, pointY); printf("%-8s", " ");
		GoToXY(pointX + 47, pointY); printf("%-8s", " ");
		GoToXY(pointX + 57, pointY); printf("%-6s", " ");
		GoToXY(pointX + 65, pointY); printf("%-8s", " ");	
		GoToXY(pointX + 75, pointY); printf("%-8s", " ");
		GoToXY(pointX + 85, pointY); printf("%-11s", " ");
	}
}

void CountHeaderLopTinChiTable(int pointX, int pointY){
	GoToXY(pointX, pointY); cout << "STT";
	GoToXY(pointX + 10, pointY); cout << "MALOPTC";
	GoToXY(pointX + 20, pointY); cout << "MA MON HOC";
	GoToXY(pointX + 33, pointY); cout << "Nien Khoa";
	GoToXY(pointX + 47, pointY); cout << "Hoc Ky";
	GoToXY(pointX + 57, pointY); cout << "Nhom";
	GoToXY(pointX + 65, pointY); cout << "SV Min";
	GoToXY(pointX + 75, pointY); cout << "SV Max";
	GoToXY(pointX + 85, pointY); cout << "Tinh Trang";
}

void CoutNodeLopTinChi(LopTinChi *ltc, int stt, int pointX, int pointY){
	HideTyping();
	GoToXY(pointX, pointY); printf("%-6d", stt);
	GoToXY(pointX + 10, pointY); printf("%-8d", ltc->MALOPTC);
	GoToXY(pointX + 20, pointY); printf("%-11s", ltc->MAMH);
	GoToXY(pointX + 33, pointY); printf("%-8d", ltc->NIENKHOA);
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
		string nienkhoa = ConvertIntToString(plist.LOP[i]->NIENKHOA);
		string hocky = ConvertIntToString(plist.LOP[i]->HOCKY);
		string nhom = ConvertIntToString(plist.LOP[i]->NHOM);
	   	if(maloptc.find(keyword) != string::npos || mamonhoc.find(keyword) != string::npos || nienkhoa.find(keyword) != string::npos || hocky.find(keyword) != string::npos || nhom.find(keyword) != string::npos){
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

void Huy_LopTinChi(DSLOPTINCHI &plist){
	for(int i = 0; i < plist.N;i++){
		if(Reccount_DK(plist.LOP[i]->DSDK) < plist.LOP[i]->MINSV){
			plist.LOP[i]->HUYLOP = TRUE;
		}
	}
}

int Search_Info_LTC(DSLOPTINCHI plist, int maloptc){
	for ( int i = 0 ; i < plist.N ; i++)
  	     if (plist.LOP[i]->MALOPTC == maloptc) return i;
	return -1;
}

int Search_Info_LTC_BY_MALOPHOC(DSLOPTINCHI plist, char *mamonhoc, int nhom, int hocky, int nienkhoa){
	for ( int i = 0 ; i < plist.N ; i++)
  	     if ( strcmp(plist.LOP[i]->MAMH, mamonhoc) == 0 && plist.LOP[i]->NIENKHOA == nienkhoa && plist.LOP[i]->HOCKY == hocky && plist.LOP[i]->NHOM == nhom ) return i;
	return -1;
}

void DrawBoderThemLopTinChi(string title, int index){
	int pointX = 55, pointY = 5, width = 90, height = index == 0 ? 34 : 30;
	
	if(index == 1){
		for(int i = 0; i < 10; i++){
			if( i > 3) {
				GoToXY(pointX-2, 30+i);
				printf("%-94s", "");
			}	
			else {
				GoToXY(pointX+1, 30+i);
				printf("%-88s", "");
			}
				
			
		}	
	}
	
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
	
	int a = index == 0 ? 33 : 29;
	for(int i = 0; i < NUMBER_ITEM_LOPTINCHI_FUNCTION_TEXT; i++){
		GoToXY(pointX+17*i+ 5, pointY+a);
		SetBGColor(14);
		SetColor(RED);
		cout << LopTinChiFunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << LopTinChiFunctionText[1][i];
	}
	
	for(int i = index; i < NUMBER_ITEM_LOPTINCHITEXT; i++){
		GoToXY(pointX+5, pointY+3+(i-index)*4);
		printf("%-30s", ThemLopTinChiText[i]);
		DrawInput(85, pointY+2+(i-index)*4);
	}
	
	if(index == 0){
		for(int i = 0; i < 1; i++){
			GoToXY(pointX+1, 34+i*4);
			printf("%-88s", "");
		}	
	}
	
	GoToXY(87, 8);
	Typing();

}

int ThemLopTinChi(DSLOPTINCHI &plist, string state){
	DrawTitle(LopTinChiText[0], 87);
	MonHoc mh;
	TREE p;
	int x = 87, y = 8;
	string temp = "";
	int c, type = 2, index = 0, is_delete = 0, check;
	int maloptc, nienkhoa, hocky, nhom, maxsv, minsv;
	char mamonhoc[10];
	
	int length = 50;
	if(state == "NEW"){
		type = 0;
		DrawBoderThemLopTinChi("NHAP THONG TIN DE THEM LOP TIN CHI MOI!", 1);
		do{
			c = InputValue(length, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
			    case EX_INSERT:
			    case EX_DEL:
			    	ClearButtonYesNo(34);
			        return c;
				case TAB:
			        return 3;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
					if(index == 0){
						strcpy(mamonhoc, temp.c_str());
						p = SearchNodeMH(tree, mamonhoc);
			    		if(p == NULL) {
			    			Message("ERROR:", "Ma Mon Hoc Khong Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
						
						y+=4, type = 2, length = 4;
					}else if(index == 1){
						y+=4;
						sscanf(temp.c_str(), "%d", &nienkhoa);
						type = 6, length = 1;
					}else if(index == 2){
						y+=4;
						sscanf(temp.c_str(), "%d", &hocky);
						type = 0;
					}else if(index == 3){
						sscanf(temp.c_str(), "%d", &nhom);
						int check2 = Search_Info_LTC_BY_MALOPHOC(plist, mamonhoc, nhom, hocky, nienkhoa);
						if(check2 != -1){
							Message("ERROR:", "Nien Khoa " + ConvertIntToString(nienkhoa) + " Da Ton Tai Nhom " + ConvertIntToString(nhom) + "!", 0, 1000);
							break;
						}
						y+=4, length = 3;
					}else if(index == 4){
						y+=4;
						sscanf(temp.c_str(), "%d", &minsv);
						temp = ConvertIntToString(maxsv);
					}else if(index == 5){
						sscanf(temp.c_str(), "%d", &maxsv);
						if(maxsv < minsv){
							Message("ERROR:", "So SV MAX khong duoc be hon SO SV MIN!", 0, 1000);
							temp = ConvertIntToString(minsv);
							y-=4, index--;
							break;
						}
					}
					index++;
					temp = "";
					if(index == 6){
							LopTinChi *ltc = new LopTinChi;
							strcpy(ltc->MAMH, mamonhoc);
							ltc->NIENKHOA = nienkhoa;
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
		DrawBoderThemLopTinChi("NHAP MA LOP TIN CHI DE CHINH SUA!", 0);
		do{
			c = InputValue(length, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
			    case EX_INSERT:
			    case EX_DEL:
			    	ClearButtonYesNo(34);
			        return c;
				case TAB:
			        return 3;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index < 7) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNo(35, is_delete, state);
			        break;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
					if(index == 0){
						sscanf(temp.c_str(), "%d", &maloptc);
						check = Search_Info_LTC(plist, maloptc);
			    		if(check == -1) {
			    			Message("ERROR:", "Ma Lop Tin Chi Khong Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
						DrawButtonYesNo(34, state);
						GoToXY(x, y);
						SetColor(RED);
						
						printf("%-50d", plist.LOP[check]->MALOPTC);
						
						GoToXY(x, y+=4);
						SetColor(BLACK);
						printf("%-50s", plist.LOP[check]->MAMH);
						strcpy(mamonhoc, plist.LOP[check]->MAMH);
	
							
						GoToXY(x, y+=4);
						printf("%-50d", plist.LOP[check]->NIENKHOA);
						nienkhoa = plist.LOP[check]->NIENKHOA;
						
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
					}else if(index == 1){
						strcpy(mamonhoc, temp.c_str() );
						
						p = SearchNodeMH(tree, mamonhoc);
						if(p == NULL){
							Message("ERROR:", "Ma Mon Hoc Khong Ton Tai!", 0, 1000);
							break;
						}
						length = 4;
						temp = ConvertIntToString( nienkhoa );
						y+=4, index++, length = 4;
					}else if(index == 2){
						sscanf(temp.c_str(), "%d", &nienkhoa);
						
						length = 1;
						temp = ConvertIntToString( hocky );
						y+=4, index++, type = 6, length = 1;
					}else if(index == 3){
						sscanf(temp.c_str(), "%d", &hocky);
						
						temp = ConvertIntToString( nhom );	
					y+=4, index++, type = 2;
					}else if(index == 4){
						sscanf(temp.c_str(), "%d", &nhom);
						
						length = 3;
						temp = ConvertIntToString( minsv );
						y+=4, index++, length = 3;
					}else if(index == 5){
						sscanf(temp.c_str(), "%d", &minsv);
						
						length = 3;
						temp = ConvertIntToString( maxsv);
						y+=4,index++;
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
						DrawTitleYesNo(35, is_delete, state);
						
					}else if(index == 7){
						if(is_delete == 1) {
							is_delete = 0;
						}else if(is_delete == 0) {
							strcpy(plist.LOP[check]->MAMH, mamonhoc);
							plist.LOP[check]->NIENKHOA = nienkhoa;
							plist.LOP[check]->HOCKY = hocky;
							plist.LOP[check]->NHOM = nhom;
							plist.LOP[check]->MINSV = minsv;
							plist.LOP[check]->MAXSV = maxsv;
							Message("SUCCESS:", "Da Luu Thay Doi Lop Tin Chi!", 1, 1000);
						}
						length = 50;
						temp = "";
						type = 0;
						y = 8;
						DrawTitleYesNo(35, -1, state);
						ClearInput(x, 4, 7);
						ClearButtonYesNo(34);
						index = 0;
						temp = "";
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "DELETE"){
		DrawBoderThemLopTinChi("NHAP MA LOP TIN CHI DE XOA!", 0);
		do{
			c = InputValue(50, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
			    case EX_INSERT:
			    case EX_DEL:
			    	ClearButtonYesNo(34);
			    	return c;
				case TAB:
			        return 3;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index < 7) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNo(35, is_delete, state);
			        break;
			    case ENTER:
			    	if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
			    	if(temp.length() == 0 ) {
						Message("ERROR:", "Vui long khong de trong!", 0, 1000);
						GoToXY(x+temp.length(), y);
						break;
					}
					
					if(index == 0){
						sscanf(temp.c_str(), "%d", &maloptc);
						check = Search_Info_LTC(plist, maloptc);
			    		if(check == -1) {
			    			Message("ERROR:", "Ma Lop Tin Chi Khong Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
						DrawButtonYesNo(34, state);
						GoToXY(x, y);
						SetColor(RED);
						
						printf("%-50d", plist.LOP[check]->MALOPTC);
						
						GoToXY(x, y+=4);
						printf("%-50s", plist.LOP[check]->MAMH);
						strcpy(mamonhoc, plist.LOP[check]->MAMH);
							
						GoToXY(x, y+=4);
						printf("%-50d", plist.LOP[check]->NIENKHOA);
						nienkhoa = plist.LOP[check]->NIENKHOA;
						
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
						DrawTitleYesNo(35, is_delete, state);
					}else if(index == 7){
						if(is_delete == 1) {
							is_delete = 0;
						}else if(is_delete == 0) {
							Delete_Item_LopTC(plist, check+1);
							Message("SUCCESS:", "Da Xoa Lop Tin Chi!", 1, 1000);
						}
						temp = "";
						type = 0;
						y = 8;
						DrawTitleYesNo(35, -1, state);
						ClearInput(x, 4, 7);
						ClearButtonYesNo(34);
						index = 0;
						temp = "";
					}
					
					break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
}

void DrawTableLopTinChi(int is_draw_title, int number, int tab){
	int pointX = 45, pointY = 5, width = 106, height = 37;
	int col1 = 10, col2 = 20, col3 = 33, col4 = 47, col5 = 57, col6 = 65, col7 = 75, col8 = 85;
	
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
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5 || j == col6 || j == col7 || j == col8)
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
				else if(j == col1 || j == col2 || j == col3 || j == col4 || j == col5|| j == col6 || j == col7 || j == col8)
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
				
				GoToXY(pointX+col8, pointY+i);
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
	DrawTitleTable(number == 4 ? 78 : 87, 1, tab, LopTinChiText, number);
}

void PrintDataLopTC(int tab, string state){
	int c, a, b;
	
	if(state != "NEW" && dsloptc.N == 0) {
		Message("ERROR:", "Danh Sach Lop Tin Chi Rong. Khong The Sua Hoac Xoa!", 0, 1000);
		return;
	}
					
	if(tab > 1){
		DrawTitleTable(78, 1, tab, LopTinChiText, 4);
		do{
			a = ThemLopTinChi(dsloptc, state);
			HideTyping();
			switch(a){
				case 3:
					c = DrawTableMonHocEx();
					if(c == 1) {
						tab = 1;
						break;
					}else if(c == -1) return;
					DrawTitleTable(78, 1, tab, LopTinChiText, 4);
				case EX_F3:
					if(dsloptc.N == 0) {
						Message("ERROR:", "Danh Sach Lop Tin Chi Rong. Khong The Sua Hoac Xoa!", 0, 1000);
						break;
					}
					state = "EDIT";
					break;
				case EX_INSERT:
					state = "NEW";
					break;
				case EX_DEL:
					if(dsloptc.N == 0) {
						Message("ERROR:", "Danh Sach Lop Tin Chi Rong. Khong The Sua Hoac Xoa!", 0, 1000);
						break;
					}
					state = "DELETE";
					break;
				case ESC:
					ClearTable(1);
		        	return;
			}
		    if (tab == 1) break;
		} while (1);
		
		ClearTable(0);
	}
	
	if(dsloptc.N == 0){
		Message("ERROR:", "Danh Sach Lop Tin Chi Rong!", 0, 1000);
		ClearTable(1);
		return;
	}
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = dsloptc.N;

	int n = (int)ceil((double)total/15);
	int currentPage = 0;
	string keyword = "";

	
	Message("SUCCESS:", "Load Du Lieu Lop Tin Chi Thanh Cong!", 1, 500);
	PrintPageTable(currentPage+1, n);
	DrawTableLopTinChi(1, 4, tab);
	Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
	PrintSearchInput(keyword);
	do {
	    c = InputSearch(keyword, x, y);
	    switch (c) {
		    case EX_UP:
		    case EX_DOWN:
		    	if(tab > 1) break;
		    	
		    	if (c == EX_UP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_DOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
		        Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
		        n = (int)ceil((double)total/15);
				PrintPageTable(currentPage+1, n);
				
				if(currentPage == n-1)
						ClearRemainLopTinChi(stt, pointX, pointY);
						
				PrintSearchInput(keyword);
				
		        break;
		    case TAB: 
		    	tab = tab == 1 ? 2 : (tab == 2 ? 3 : 1);
		    	DrawTitleTable(78, 1, tab, LopTinChiText, 4);
		    	
		    	if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTable(0);
		    		PrintPageTable(currentPage+1, n);
					DrawTableLopTinChi(1, 4, tab);
					Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
					PrintSearchInput(keyword);
				}else if(tab == 2){
					ClearTable(0);
					a = ThemLopTinChi(dsloptc, "NEW");
					do{
						if(a == 3){
							tab = 3;
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else {
							HideTyping();
							a = ThemLopTinChi(dsloptc, a == EX_F3 ? "EDIT" : (a == EX_INSERT ? "NEW" : "DELETE"));
						} 
					}while(1);
				
				}
				
				if(tab == 3){
					ClearTable(0);
					b = DrawTableMonHocEx();
					if(b == 1) {
						x = 57, y = 6;
						tab = 1;
						ClearTable(0);
				    	PrintPageTable(currentPage+1, n);
						DrawTableLopTinChi(1, 4, tab);
						Traverse_LTC(dsloptc, pointX, pointY = 8, currentPage, stt, keyword, total);
						PrintSearchInput(keyword);
						break;
					}else if(b == -1) {
						return;
					}
				
				}
		    	break;
		    case EX_F3: 
		    case EX_DEL: 
		    case EX_INSERT: 
		    	if(tab == 2) break;
		    	tab = 2;
				ClearTable(0);
				DrawTitleTable(78, 1, tab, LopTinChiText, 4);
				a = ThemLopTinChi(dsloptc, a == EX_F3 ? "EDIT" : (a == EX_INSERT ? "NEW" : "DELETE"));
				do{
					if(a == 0){
						x = 57, y = 6;
						tab = 1;
						ClearTable(0);
				    	PrintPageTable(currentPage+1, n);
						DrawTableLopTinChi(1, 4, tab);
						Traverse_LTC(dsloptc, pointX, pointY = 8, currentPage, stt, keyword, total);
						PrintSearchInput(keyword);
						break;
					}else if(a == ESC) {
						ClearTable(1);
						return;
					}else {
						HideTyping();
						a = ThemLopTinChi(dsloptc, a == EX_F3 ? "EDIT" : (a == EX_INSERT ? "NEW" : "DELETE"));
					}
				}while(1);
		    	break;
		    case ENTER:
		    	if(tab ==  2) break;
				Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
				ClearRemainLopTinChi(stt, pointX, pointY = 8);
				n = (int)ceil((double)total/15);
				PrintPageTable(currentPage+1, n);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
		    case ESC:
		    	ClearTable(1);
		        return;
	    }
	} while (1);
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
		ltc = new LopTinChi;

		getline(file, temp, ',');
		sscanf(temp.c_str(), "%d", &ltc->MALOPTC);
		
		getline(file, temp, ',');
		strcpy(ltc->MAMH, temp.c_str());
		
		getline(file, temp, ',');
		sscanf(temp.c_str(), "%d", &ltc->NIENKHOA);
		
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

void ClearBoderHuyLopTinChi(){
	int pointX = 65, pointY = 15, width = 70, height = 10;
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		printf("%-80s", " ");
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
	
	
	DrawBoderHuyLopTinChi();
	int c, x = 10, y = 20, is_delete = 0, type = 4;
	string temp;
	
	DrawButtonYesNo(y, "HUYLOPTC");
	DrawTitleYesNo(y+1, is_delete, "HUYLOPTC");
	do{
		c = InputValue(50, "%-50s", temp, x, y, type);
		switch (c) {
			case EX_LEFT:
			case EX_RIGHT:
			    is_delete = is_delete == 1 ? 0 : 1;
			    DrawTitleYesNo(y+1, is_delete, "HUYLOPTC");
			    break;
			   case ENTER:
			    	
			   	if(is_delete == 1) is_delete = 0;
			   	else{
			   		Huy_LopTinChi(dsloptc);
					Message("SUCCESS:", "Da Huy Lop Tin Chi Thanh Cong!", 1, 1500);
				}
			case ESC:
			   	ClearBoderHuyLopTinChi();
			       return;
		}
	}while(1);
}

void DrawBoderChonLTC(){
	int pointX = 55, pointY = 10, width = 90, height = 8;
	
	
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
	
	int index = 0;
	GoToXY(pointX+5, pointY+3+index*4);
	printf("%-30s", ThemLopTinChiText[index]);
	DrawInput(85, pointY+2+index*4);
	
	GoToXY(87, 8);
	HideTyping();

}


int DrawTableLopTCEx(){
	int c, a;
	if(dsloptc.N == 0){
		Message("ERROR:", "Danh Sach Lop Tin Chi Rong!", 0, 1000);
		return -1;
	}
	
	ClearTable(0);
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = dsloptc.N;

	int n = (int)ceil((double)total/15);
	int currentPage = 0;
	string keyword = "";

	
	Message("SUCCESS:", "Load Du Lieu Lop Tin Chi Thanh Cong!", 1, 500);
	PrintPageTable(currentPage+1, n);
	DrawTableLopTinChi(0, 3, 0);
	DrawTitleFunction(pointX+10, pointY+17 ,0, 4);
	Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
	PrintSearchInput(keyword);
	do {
	    c = InputSearch(keyword, x, y);
	    switch (c) {
		    case EX_UP:
		    case EX_DOWN:
		    	if (c == EX_UP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_DOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
		        Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
		        n = (int)ceil((double)total/15);
				PrintPageTable(currentPage+1, n);
				
				if(currentPage == n-1)
						ClearRemainLopTinChi(stt, pointX, pointY);
						
				PrintSearchInput(keyword);
				
		    	break;
		    case ENTER:
				Traverse_LTC(dsloptc, pointX, pointY, currentPage, stt, keyword, total);
				ClearRemainLopTinChi(stt, pointX, pointY = 8);
				n = (int)ceil((double)total/15);
				PrintPageTable(currentPage+1, n);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
			case TAB:
				ClearTable(0);
		        return 1;
		    case ESC:
		    	ClearTable(1);
		        return 2;
	    }
	} while (1);
}

int DrawTableMonHocEx(){
	TREE DSMH = NULL;
	int c, a;
	
	if(tree == NULL){
		Message("ERROR:", "Danh Sach Mon Hoc Rong!", 0, 1000);
		return -1;
	}
	ClearTable(0);
	DrawTitleTable(78, 1, 3, LopTinChiText, 4);
	
	if(tree != NULL) Inorder(tree, DSMH); 
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = ReccountTree(tree);
	int n = (int)ceil((double)total/15);
	int currentPage = 0;
	string keyword = "";
	
	Selection_Sort_DSMH(DSMH);
	
	Message("SUCCESS:", "Load Du Lieu Mon Hoc Thanh Cong!", 1, 500);
	PrintPageTable(currentPage+1, n);
	DrawTableMonHoc(0);
	DrawHuongDanTable(48, 40, LopTinChiFunctionText, NUMBER_ITEM_LOPTINCHI_FUNCTION_TEXT);
	Traverse_DSMH(DSMH, stt, pointX, pointY, currentPage, keyword);
	PrintSearchInput(keyword);
	
	do {
	    c = InputSearch(keyword, x, y);
	    switch (c) {
		    case EX_UP:
		    case EX_DOWN:
		    	if (c == EX_UP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_DOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
		        Selection_Sort_DSMH(DSMH);
				Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword);
				n = (int)ceil((double)stt/15);
				PrintPageTable(currentPage+1, n);
				
				if(currentPage == n-1)
						ClearRemainMonHoc(stt, pointX, pointY, currentPage);
						
				PrintSearchInput(keyword);
				
		        break;
		    case EX_F3:
		    case EX_INSERT:
		    case EX_DEL:
		    	delete DSMH;
		    	ClearTable(0);
		    	return c;
		    case TAB: 
		    	delete DSMH;
		    	ClearTable(0);
		    	return 1;
		    case ENTER:
		    	Selection_Sort_DSMH(DSMH);
				Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword);
				ClearRemainMonHoc(stt, pointX, pointY = 8, 0);
				n = (int)ceil((double)stt/15);
				PrintPageTable(currentPage+1, n);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
		    case ESC:
		    	delete DSMH;
		    	ClearTable(1);
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
	char malophoc[1] = "";
	LISTSV *pages = new LISTSV[n];
	
	
	Message("SUCCESS:", "Load Du Lieu Sinh Vien Thanh Cong!", 1, 500);
	PrintPageTable(currentPage+1, n);
	DrawTableSinhVien(malophoc, 0);
	Selection_Sort_SV(DSSV, malophoc);
	Traverse_SV(DSSV, malophoc, stt, pointX, pointY, currentPage, keyword, pages);
	DrawTitleFunction(pointX+10, pointY+17, 4, 4);
	PrintSearchInput(keyword);
	
	do {
	    c = InputSearch(keyword, x, y);
	    switch (c) {
		    case EX_UP:
		    case EX_DOWN:
		    	
		    	if (c == EX_UP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_DOWN && currentPage + 1 < n) currentPage++;

		        HideTyping();
				Traverse_SV(DSSV, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
				PrintPageTable(currentPage+1, n);
				
				if(currentPage == n-1)
					ClearRemainSinhVien(stt, pointX, pointY);
						
				PrintSearchInput(keyword);
				
		        break;
		    case ENTER:
		    	Selection_Sort_SV(DSSV, malophoc);
				Traverse_SV(DSSV, malophoc, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
				ClearRemainSinhVien(stt, pointX, pointY = 8);
				total = Reccount_SV_With_Keyword(DSSV, malophoc, keyword);
				n = (int)ceil((double)total/15);
				PrintPageTable(currentPage+1, n);
				PrintKeyWord("%-50s", keyword, x, y);

				break; 
		    case ESC:
		    	delete pages;
		    	ClearListSV(DSSV);
		    	ClearTable(1);
		        return;
	    }
	} while (1);
	
} 

void DrawTitleFunction(int x, int y, int start, int step){
	for(int i = start; i < NUMBER_ITEM_LOPTINCHI_FUNCTION_TEXT; i+=step){
		GoToXY(x-7+5*i, y+15);
		SetBGColor(14);
		SetColor(RED);
		cout << LopTinChiFunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << LopTinChiFunctionText[1][i];
	}	
}

void DrawChonLopTinChi(){
	DrawBoderChonLTC();
	int c, x = 87, y = 13, type = 0, tab = 1, maloptc;
	string temp = "";
	int length = 10;
	
	DrawTitle(DanhSachDangKyText[0], 88);
	DrawTitleTable(x, 1, tab, DanhSachDangKyText, 3);
	DrawTitleFunction(x, y-11, 0, 4);
	
	do{
		c = InputValue(length, "%-50s", temp, x, y, type);
			switch (c) {
				case TAB:
					tab = 2;
					DrawTitleTable(x, 1, tab, DanhSachDangKyText, 3);
					if(tab == 2) {
						int b = DrawTableLopTCEx();
						if(b == 1){
							DrawBoderChonLTC();
							DrawTitleFunction(x, y-11, 0, 4);
						}else if(b == 2){
							return;
						}
					}
					tab = 1, temp = "";
					DrawTitleTable(x, 1, tab, DanhSachDangKyText, 3);
					break;
			    case ENTER:
			    	{
			    		if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
				    	if(temp.length() == 0 ) {
							Message("ERROR:", "Vui long khong de trong!", 0, 1000);
							GoToXY(x+temp.length(), y);
							break;
						}
				    	sscanf(temp.c_str(), "%d", &maloptc);
							
						int check = Search_Info_LTC(dsloptc, maloptc);
						if(check == -1){
							Message("ERROR:", "Khong Tim Thay Lop Tin Chi Phu Hop!", 0, 1000);
							break;
						}
							
						if(dsloptc.LOP[check]->DSDK == NULL){
							Message("ERROR:", "Danh Sach Sinh Vien Rong!", 0, 1000);
							break;
						}
						DrawTableSinhVienEx(dsloptc.LOP[check]->DSDK);
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

int Reccount_LH(DSLOPPTR &ListLop) {
	if(ListLop == NULL) return 0;
	
	int count = 0;
	DSLOPPTR p = ListLop;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

void Selection_Sort_LH(DSLOPPTR& ListLop){
    DSLOPPTR p, q, pmin;
    char min[50];

    for (p = ListLop; p->next != NULL; p = p->next)
    {
        strcpy(min, p->MALOP);
        pmin = p;
        for (q = p->next; q != NULL; q = q->next){
	        if ( strcmp(min, q->MALOP ) < 0)
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

void Traverse_LH(DSLOPPTR ListLop, int &stt, string keyword, int x, int y, string state){
	HideTyping();
   	DSLOPPTR p = ListLop;
   	ClearAutoComplete(x-17, y+2, 15);
   	int check = state == "NEW" ? 6 : 7;
   	while(p != NULL)
   	{
   		if(stt == check) break;
   		GoToXY(x, y+stt*2 + 3);
   		string malophoc = convertToString(p->MALOP, strlen(p->MALOP));
   		if(malophoc.find(keyword) != string::npos){
        	printf("%-11s\n", p->MALOP);
        	GoToXY(x, y+stt*2 + 4);
        	stt++;
        	if(stt < 7) cout << "------------------------------";
		}
		p = p->next;
   	}
   	if(state != "NEW" ) {
   		if(stt == 0){
	   		ClearAutoComplete(x-17, y+2, 3);
	   		return;
		}
   		stt--;
   		DrawAutoComplete(x-17, y+2, stt*2+3);
		return;
	}
	
   	GoToXY(x, y+stt*2 + 3);
   	cout << "Them Lop Moi";
   	DrawAutoComplete(x-17, y+2, stt*2+3);
}

DSLOPPTR Search_LH(DSLOPPTR ListLop, char *malh){
	if(ListLop == NULL) return NULL;
	DSLOPPTR p;
	for (p = ListLop;  p != NULL ; p=p->next ) 
        if ( strcmp(p->MALOP, malh) == 0  ) return p;
	return NULL;
}

DSLOPPTR Search_LH_By_STT(DSLOPPTR ListLop, string keyword, int select){
	if(ListLop == NULL) return NULL;
	DSLOPPTR p;
	int stt = 0;
	for (p = ListLop;  p != NULL ; p=p->next  ) {
		string malophoc = convertToString(p->MALOP, strlen(p->MALOP));
   		if(malophoc.find(keyword) != string::npos){ 
   		   stt++;
   		   if(select == stt-1) return p;
   		}
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

void Load_SinhVien(){ 
	
	ClearListSV(First);
	Initialize_SV(First);
	
	char filename[50] = "data\\DSSV.TXT";
	SinhVien x;
  	ifstream file(filename);
	
	if (!file.is_open())
	{
		Message("ERROR:", "File DSSV.TXT Khong Ton Tai", 0, 1000);
		return;
	}
	
	string temp;
	while (!file.eof())
	{
		getline(file, temp, ',');
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

void ClearAutoComplete(int pointX, int pointY, int height){
	HideTyping();
	for(int i = 0; i < height; i++){
		GoToXY(pointX, pointY+i);
		printf("%-50s","");
	}
}

void DrawBorderChonLopHoc(int &pointX, int &pointY, int &col1, int &height, int &width){
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
				else if(j == col1)
					if(i == 0)
						cout << char(TOP_CENTER_SIMPLE);
					else if(i == height-1)
						cout << char(BOTTOM_CENTER_SIMPLE);
					else cout << char(HORIZONTAL_LINE);
				else cout << char(HORIZONTAL_LINE);
			}
		}else {
			cout << char(VERTICAL_LINE);
			//printf("%-69s"," ");
			if(i > 0 && i < height - 1){
				GoToXY(pointX+15, pointY+i);
				cout << char(VERTICAL_LINE);
			}
			GoToXY(pointX+width-1, pointY+i);
			cout << char(VERTICAL_LINE);
		}
	}
}

void DrawAutoComplete(int x, int y, int height){
	int width = 50;
	int col1 = 15;
	DrawBorderChonLopHoc(x, y, col1, height, width);
}

void DrawBorderSearch(int &pointX, int &pointY){
	int width = 50, height = 3;
	int col1 = 15;
	DrawBorderChonLopHoc(pointX, pointY, col1, height, width);
	
	GoToXY(pointX+2, pointY+1);
	cout << " MA LOP HOC: ";
	GoToXY(pointX+col1+2, pointY+1);
}


void DrawCharArrow(int select, int total){
	HideTyping();
	int x = 78, y = 14;
	for(int i = 0; i < total; i++){
		GoToXY(x, y+2*i );
		if(select == i){
			SetColor(LIGHT_PURPLE);
			cout << char(219) << char(219)<< "====>>>>";
			SetColor(BLACK);
		}else printf("%-10s"," ");
	}
}

void DrawChonLopHoc(string state){
	int x = 75, y = 10;
	DrawBorderSearch(x, y);
	string keyword = "";
	x = x+17, y = y+1;
	int c, stt, select = 0;
	Selection_Sort_LH(ListLop);
	do {
	    c = InputValue(20, "%-30s", keyword, x, y, 5);
	    switch (c) {
		    case 201:
		    	if(keyword == ""){
		    		ClearAutoComplete(x-17, y+2, 15);
		    		break;
				}
		    	Traverse_LH(ListLop, stt = 0, keyword, x, y, state);
		    	if(state == "NEW")
		    		DrawCharArrow(select = 0, stt+1);
		    	else 
		    		DrawCharArrow(select = stt > 0 ? 0 : -1, stt+1);
		    	break;
		    case EX_UP:
		    	if(keyword == "" || stt == 0) break;
		    	if(select + 1 > 1) select--;
		    	DrawCharArrow(select, stt+1);
		    	break;
		     case EX_DOWN:
		     	if(keyword == "" || stt == 0) break;
		     	if(select + 1 < stt+1) select++;
		     	DrawCharArrow(select, stt+1);
		    	break;
		    case ESC:
		    	HideTyping();
		    	ClearAutoComplete(x-17, y-1, 20);
		    	return;
		    case ENTER:
		    	if(keyword == "") break;
		    	char temp[10];
		    	strcpy(temp, keyword.c_str());
		    	DSLOPPTR p;
		    	
		    	if(state == "DSSV"){
		    		p = Search_LH_By_STT(ListLop, keyword, select);
		    		if(p == NULL){
		    			Message("ERROR:", "Ma Lop Khong Ton Tai!", 0, 1000);
			    		break;
					}
		    		ClearAutoComplete(x-17, y-1, 20);
		    		PrintDataSinhVien(First, 1, state, p->MALOP, 0);
				}else{
					if(state == "NEW" && select == stt){
						p = Search_LH(ListLop, temp);
			    		if(p != NULL){
			    			Message("ERROR:", "Ma Lop Hoc Da Ton Tai!", 0, 1000);
			    			break;
						}
			    		ClearAutoComplete(x-17, y-1, 20);
				    	CreateSinhVien(First, temp, 1, state);
				    	
				    	LISTSV q = Check_Is_New_Class(First, temp);
				    	if(q != NULL){
				    		Insert_Last_LH(ListLop, temp);
						}
				    		

					} else {
						p = Search_LH_By_STT(ListLop, keyword, select);
				    	ClearAutoComplete(x-17, y-1, 20);
				    	CreateSinhVien(First, p->MALOP, 0, state);
					}
				}
		    	return;
		}	
	}while(1);
}
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
			"F3",
			"DEL",
			"INSERT",
			"ENTER"
		},
		{
			": Chuyen Tab",
			": Chinh Sua",
			": Xoa",
			": Them",
			": Xac Nhan"
		}
};
/*
* === END ===
*/

/*
* — Ham xu ly Cau truc sinh vien . Danh sach lien ket don —
*/

void Initialize_SV(LISTSV& First){
    First = NULL;
}

int Reccount_SV_With_Keyword(LISTSV &First, char *malophoc, string keyword){
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

int Reccount_SV(LISTSV &First, char *malophoc) {
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
	else 
		p = pages[currentPage];
	
    while (p != NULL)
    {
        
    	if( stt < 16 && (strlen(malophoc) == 0 || strcmp(p->SV.MALOP, malophoc) == 0 ) ){
    		string ten = convertToString(p->SV.TEN, strlen(p->SV.TEN));
	        string ho = convertToString(p->SV.HO, strlen(p->SV.HO));
	        string masv = convertToString(p->SV.MASV, strlen(p->SV.MASV));
        	if( (ten.find(keyword) != string::npos || ho.find(keyword) !=  string::npos || masv.find(keyword) !=  string::npos) ){
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
/*
* === END ===
*/

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
	
	
	for(int i = 0; i < NUMBER_ITEM_SINHVIEN_FUNCTION_TEXT; i++){
		GoToXY(pointX+17*i+ 5, pointY+30);
		SetBGColor(14);
		SetColor(RED);
		cout << SinhVienFunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << SinhVienFunctionText[1][i];
	}
	
	
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

int ThemSinhVien(LISTSV &First, string state, char *malophoc, int is_new_class){
	char title[50];
	strcpy(title, SinhVienText[0]);
	strcat(title, " LOP: ");
	strcat(title, malophoc);
	DrawTitle(title, 78);
	
	SinhVien sv;
	LISTSV p;
	int x = 87, y = 8, c, type = 0, index = 0, is_delete = 0, gender = 1, length = 15;
	string temp = "";
	
	if(state == "NEW"){
		DrawBoderThemSinhVien("NHAP THONG TIN DE THEM SINH VIEN!", malophoc);
		DrawInputGender(87, 24, -1);
			do{
			c = InputValue(length, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
			    case EX_DEL:
			    	if(is_new_class){
			    		ClearButtonYesNo(31);
			    		Message("ERROR:", "Danh Sach Sinh Vien Rong Khong The Xoa Hoac Sua!", 0, 1500);
			    		break;
					}
			    case EX_INSERT:
			    	ClearButtonYesNo(31);
			    	return c;
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
				    	is_new_class = 0;
					}
					GoToXY(x, y+=4);
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "EDIT"){
		DrawBoderThemSinhVien("NHAP MA SINH VIEN DE CHINH SUA!", malophoc);
		DrawInputGender(87, 24, -1);
			do{
			c = InputValue(50, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
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
					
			    	if(index == 0){
			    		strcpy(sv.MASV, temp.c_str());
			    		p = Search_Info_SV(First, sv);
			    		if(p == NULL) {
			    			Message("ERROR:", "Ma Sinh Vien Khong Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
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
					}else if(index == 1){
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
						
						if(is_delete == 1) {
							is_delete = 0;
						}else if(is_delete == 0) {
							p->SV = sv;
							Message("SUCCESS:", "Luu Sinh Vien Thanh Cong!", 1, 1000);
						}
				    	type = 0, y = 8;
						index = 0;
						temp = "";
				    	ClearInput(x, y-4, 3);
				    	ClearButtonYesNo(31);
				    	
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "DELETE"){
		DrawBoderThemSinhVien("NHAP MA SINH VIEN DE XOA!", malophoc);
		DrawInputGender(87, 24, -1);
		do{
			c = InputValue(50, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
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
					
					if(index == 0){
						strcpy(sv.MASV, temp.c_str());
				    	p = Search_Info_SV(First, sv);
				    	if(p == NULL) {
				    		Message("ERROR:", "Ma Sinh Vien Khong Ton Tai!", 0, 1000);
				    		GoToXY(x+temp.length(), y);
				    		break;
						}
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
					}else if(index == 6){
						if(is_delete == 1) {
							is_delete = 0;
						}else if(is_delete == 0) {
							Delete_Info_SV(First, sv);
							Message("SUCCESS:", "Xoa Sinh Vien Thanh Cong!", 1, 800);
						}
						temp = "";
						GoToXY(x, y);
						printf("%-50s"," ");
						gender = 0;
						DrawInputGender(x, 24, gender-1);
						type = 0, y = 8, index = 0;
						DrawTitleYesNo(32, -1, state);
						ClearInput(x, 4, 4);
						ClearButtonYesNo(31);
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
	DrawTitleTable(87, 1, 1, SinhVienText, 3);
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
	
	if(tab == 2){
		DrawTitleTable(87, 1, tab, SinhVienText, 3);
		do{
			a = ThemSinhVien(First, state, malophoc, is_new_class);
			HideTyping();
			switch(a){
				case 0:
					break;
				case EX_F3:
					state = "EDIT";
					break;
				case EX_INSERT:
					state = "NEW";
					break;
				case EX_DEL:
					state = "DELETE";
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
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = Reccount_SV(First, malophoc);
	
	if(total == 0){
		Message("ERROR:", "Danh Sach Sinh Vien Rong!", 0, 1000);
		ClearTable(1);
		return;
	}
	

	int n = (int)ceil((double)total/15);
	int currentPage = 0;
	string keyword = "";
	
	LISTSV *pages = new LISTSV[n];
	
	Message("SUCCESS:", "Load Du Lieu Sinh Vien Thanh Cong!", 1, 500);
	PrintPageTable(currentPage+1, n);
	DrawTableSinhVien(malophoc, 1);
	Selection_Sort_SV(First, malophoc);
	Traverse_SV(First, malophoc, stt, pointX, pointY, currentPage, keyword, pages);
	PrintSearchInput(keyword);
	do {
	    c = InputSearch(keyword, x, y);
	    switch (c) {
		    case EX_UP:
		    case EX_DOWN:
		    	if(tab ==  2) break;
		    	
		    	if (c == EX_UP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_DOWN && currentPage + 1 < n) currentPage++;

		        HideTyping();
		        Selection_Sort_SV(First, malophoc);
				Traverse_SV(First, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
				PrintPageTable(currentPage+1, n);
				
				if(currentPage == n-1)
					ClearRemainSinhVien(stt, pointX, pointY);
						
				PrintSearchInput(keyword);
				
		        break;
		    case TAB: 
		    	tab = (tab == 1) ? 2 : 1;
		    	DrawTitleTable(87, 1, tab, SinhVienText, 3);
		    	if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTable(0);
		    		PrintPageTable(currentPage+1, n);
					DrawTableSinhVien(malophoc, 1);
					Selection_Sort_SV(First, malophoc);
					Traverse_SV(First, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
					PrintSearchInput(keyword);
					
				}else{
					ClearTable(0);
					a = ThemSinhVien(First, "NEW", malophoc, is_new_class);
					do{
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
				    		PrintPageTable(currentPage+1, n);
							DrawTableSinhVien(malophoc, 1);
							Selection_Sort_SV(First, malophoc);
							Traverse_SV(First, malophoc, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
							PrintSearchInput(keyword);
							break;
						}else if(a == EX_F3){
							HideTyping();
							a = ThemSinhVien(First, "EDIT", malophoc, is_new_class);
						}else if(a == EX_INSERT){
							HideTyping();
							a = ThemSinhVien(First, "NEW", malophoc, is_new_class);
						}else if(a == EX_DEL){
							HideTyping();
							a = ThemSinhVien(First, "DELETE", malophoc, is_new_class);
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}
					}while(1);
				}
		    	break;
		    case EX_F3: 
		    case EX_DEL: 
		    case EX_INSERT: 
		    	if(tab == 2) break;
		    	tab = 2;
				ClearTable(0);
				DrawTitleTable(87, 1, tab, SinhVienText, 3);
				if(c == EX_F3)
		    		a = ThemSinhVien(First, "EDIT", malophoc, is_new_class);
		    	else if(c == EX_DEL)
					a = ThemSinhVien(First, "DELETE", malophoc, is_new_class);
				else if(c == EX_INSERT)
					a = ThemSinhVien(First, "NEW", malophoc, is_new_class);
				do{
					if(a == 0){
						x = 57, y = 6;
						tab = 1;
						ClearTable(0);
				    	PrintPageTable(currentPage+1, n);
						DrawTableSinhVien(malophoc, 1);
						Selection_Sort_SV(First, malophoc);
						Traverse_SV(First, malophoc, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
						PrintSearchInput(keyword);
						break;
					}else if(a == EX_F3){
						HideTyping();
						a = ThemSinhVien(First, "EDIT", malophoc, is_new_class);
					}else if(a == EX_INSERT){
						HideTyping();
						a = ThemSinhVien(First, "NEW", malophoc, is_new_class);
					}else if(a == EX_DEL){
						HideTyping();
						a = ThemSinhVien(First, "DELETE", malophoc, is_new_class);
					}else if(a == ESC) {
						ClearTable(1);
						return;
					}
				}while(1);
		    	break;
		    case ENTER:
		    	if(tab ==  2) break;
		    	Selection_Sort_SV(First, malophoc);
				Traverse_SV(First, malophoc, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
				ClearRemainSinhVien(stt, pointX, pointY = 8);
				total = Reccount_SV_With_Keyword(First, malophoc, keyword);
				n = (int)ceil((double)total/15);
				PrintPageTable(currentPage+1, n);
				PrintKeyWord("%-50s", keyword, x, y);

				break;
		    case ESC:
		    	delete pages;
		    	ClearTable(1);
		        return;
	    }
	} while (1);
}

void CreateSinhVien(LISTSV &First, char *malophoc, int is_new_class, string state){
	PrintDataSinhVien(First, 2, state, malophoc, is_new_class);
}





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

const int NUMBER_ITEM_MONHOC_FUNCTION_TEXT = 5;
char MonHocFunctionText[2][NUMBER_ITEM_MONHOC_FUNCTION_TEXT][30] = {
		{
			"TAB",
			"F3",
			"DEL",
			"INSERT",
			"ENTER"
		},
		{
			": Chuyen Tab",
			": Chinh Sua",
			": Xoa",
			": Them",
			": Xac Nhan"
		}
};
/*
* === END ===
*/



/*
* — Ham In Ra Man Hinh —
*/
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

void Traverse_DSMH(TREE DSMH, int &stt, int &pointX, int pointY, int currentPage, string &keyword){
   	TREE p = DSMH;
   	while(p != NULL)
   	{
   		string ten = convertToString(p->MH.TENMH, strlen(p->MH.TENMH));
        string ma = convertToString(p->MH.MAMH, strlen(p->MH.MAMH));
        if(ten.find(keyword) != string::npos || ma.find(keyword) !=  string::npos){
        	stt++;
	        if(currentPage*15 < stt && stt < (currentPage+1)*15 +1) {
	        	GoToXY(pointX, pointY+=2);
				CoutNodeMH(p->MH, stt, pointX, pointY);
			}
		}
      	p = p->right;
   	}
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
/*
* === END ===
*/

void ClearRemainMonHoc(int total, int pointX, int pointY, int currentPage){

	int row = (currentPage+1)*15 - total;
	int row2 = 15-row;
	pointY = row2*2+pointY;
	for(int i = 0; i < row;i++){
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
	
	DrawTitleTable(87, 1, 1, MonHocText, 3);
}

void Load_MonHoc(){
	InitializeTree(tree);
	char filename[50] = "data\\DSMH.TXT";
	MonHoc x;
  	ifstream file(filename);
	
	if (!file.is_open())
	{
		cout << "File Khong Ton Tai";
		return;
	}
	
	string temp;
	while (!file.eof())
	{
		file >> temp >> x.STCLT >> x.STCTH;
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
	
	
	for(int i = 0; i < NUMBER_ITEM_MONHOC_FUNCTION_TEXT; i++){
		GoToXY(pointX+17*i+ 5, pointY+20);
		SetBGColor(14);
		SetColor(RED);
		cout << MonHocFunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << MonHocFunctionText[1][i];
	}
	
	
	for(int i = 0; i < NUMBER_ITEM_MONHOCTEXT; i++){
		GoToXY(pointX+5, pointY+3+i*4);
		cout << ThemMonHocText[i];
		DrawInput(85, pointY+2+i*4);
	}
	GoToXY(87, 8);
	Typing();

}


int ThemMonHoc(TREE &DSMH, string state){
	DrawTitle(MonHocText[0], 87);
	MonHoc mh;
	TREE p;
	int x = 87, y = 8, c, type = 0, is_delete = 0, length = 10;
	string temp = "";
	if(state == "NEW"){
		DrawBoderThemMonHoc("NHAP THONG TIN DE THEM MON HOC!");
		do{
			c = InputValue(length, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
			    case EX_INSERT:
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
		DrawBoderThemMonHoc("NHAP MA MON HOC DE CHINH SUA!");
		do{
			c = InputValue(50, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
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
			    	if(type == 0){
			    		strcpy(mh.MAMH, temp.c_str());
			    		p = SearchNodeMH(tree, mh.MAMH);
			    		if(p == NULL) {
			    			Message("ERROR:", "Ma Mon Hoc Khong Ton Tai!", 0, 1000);
			    			GoToXY(x+temp.length(), y);
			    			break;
						}
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
						GoToXY(x + temp.length(), y);
						
					}else if(type == 1){
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
						if(is_delete == 1) {
							is_delete = 0;
						}else if(is_delete == 0) {
							p->MH = mh;
							TREE q;
							for(q = DSMH; q != NULL && strcmp(mh.MAMH, p->MH.MAMH) != 0; q = q->right);
							q->MH = mh;
							Message("SUCCESS:", "Luu Mon Hoc Thanh Cong!", 1, 800);
						}
						temp = "";
						type = 0;
						y = 8;
						DrawTitleYesNo(23, -1, state);
						ClearInput(x, 4, 4);
						ClearButtonYesNo(22);
					}
					
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
	else if(state == "DELETE"){
		DrawBoderThemMonHoc("NHAP MA MON HOC DE XOA!");
		do{
			c = InputValue(50, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
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
					if(type == 0){
						strcpy(mh.MAMH, temp.c_str());
				    	p = SearchNodeMH(tree, mh.MAMH);
				    	if(p == NULL) {
				    		Message("ERROR:", "Ma Mon Hoc Khong Ton Tai!", 0, 1000);
				    		GoToXY(x+temp.length(), y);
				    		break;
						}
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
					}else if(type == 4){
						if(is_delete == 1) {
							is_delete = 0;
						}else if(is_delete == 0) {
							tree = DeleteMH(tree, mh.MAMH);
							DeleteMH_DSMH(DSMH, mh.MAMH);
							Message("SUCCESS:", "Xoa Mon Hoc Thanh Cong!", 1, 800);
						}
						temp = "";
						type = 0;
						y = 8;
						DrawTitleYesNo(23, -1, state);
						ClearInput(x, 4, 4);
						ClearButtonYesNo(22);
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
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
	
	TREE DSMH = NULL;
	int c, a;
	
	if(state !="NEW" && tree == NULL){
		Message("ERROR:", "Danh Sach Mon Hoc Rong!", 0, 1000);
		return;
	}
	
	if(tree != NULL) Inorder(tree, DSMH); 
	
	if(tab == 2){
		DrawTitleTable(87, 1, tab, MonHocText, 3);
		do{
			a = ThemMonHoc(DSMH, state);
			HideTyping();
			switch(a){
				case 0:
					break;
				case EX_F3:
				case EX_INSERT:
				case EX_DEL:
					state = a == EX_F3 ? "EDIT" : (a == EX_INSERT ? "NEW" : "DELETE");
					if(state != "NEW" && tree == NULL){
						Message("ERROR:", "Danh Sach Mon Hoc Rong!", 0, 1000);
						state = "NEW";
					}
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
	int currentPage = 0;
	string keyword = "";
	
	Selection_Sort_DSMH(DSMH);
	
	Message("SUCCESS:", "Load Du Lieu Mon Hoc Thanh Cong!", 1, 500);
	PrintPageTable(currentPage+1, n);
	DrawTableMonHoc(1);
	Traverse_DSMH(DSMH, stt, pointX, pointY, currentPage, keyword);
	PrintSearchInput(keyword);
	
	do {
	    c = InputSearch(keyword, x, y);
	    switch (c) {
		    case EX_UP:
		    case EX_DOWN:
		    	if(tab ==  2) break;
		    	
		    	if (c == EX_UP &&currentPage + 1 > 1) currentPage--; 
		        else if (c == EX_DOWN && currentPage + 1 < n) currentPage++;
		        
		        HideTyping();
		        Selection_Sort_DSMH(DSMH);
				Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword);
				n = (int)ceil((double)stt/15);
				PrintPageTable(currentPage+1, n);
				
				if(currentPage == n-1)
						ClearRemainMonHoc(stt, pointX, pointY, currentPage);
						
				PrintSearchInput(keyword);
				
		        break;
		    case TAB: 
		    	tab = (tab == 1) ? 2 : 1;
		    	DrawTitleTable(87, 1, tab, MonHocText, 3);
		    	if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTable(0);
		    		PrintPageTable(currentPage+1, n);
					DrawTableMonHoc(1);
					Selection_Sort_DSMH(DSMH);
					Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword);
					PrintSearchInput(keyword);
				}else{
					ClearTable(0);
					a = ThemMonHoc(DSMH, "NEW");
					do{
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTable(0);
				    		PrintPageTable(currentPage+1, n);
							DrawTableMonHoc(1);
							Selection_Sort_DSMH(DSMH);
							Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword);
							PrintSearchInput(keyword);
							break;
						}else if(a == ESC) {
							ClearTable(1);
							return;
						}else {
							HideTyping();
							a = ThemMonHoc(DSMH, a == EX_F3 ? "EDIT" : (a == EX_INSERT ? "NEW" : "DELETE"));
						} 
					}while(1);
				}
		    	break;
		    case EX_F3: 
		    case EX_DEL: 
		    case EX_INSERT: 
		    	if(tab == 2) break;
		    	tab = 2;
				ClearTable(0);
				DrawTitleTable(87, 1, tab, MonHocText, 3);
				a = ThemMonHoc(DSMH, a == EX_F3 ? "EDIT" : (a == EX_INSERT ? "NEW" : "DELETE"));
				do{
					if(a == 0){
						x = 57, y = 6;
						tab = 1;
						ClearTable(0);
				    	PrintPageTable(currentPage+1, n);
						DrawTableMonHoc(1);
						Selection_Sort_DSMH(DSMH);
						Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword);
						PrintSearchInput(keyword);
						break;
					}else if(a == ESC) {
						ClearTable(1);
						return;
					}else {
						HideTyping();
						a = ThemMonHoc(DSMH, a == EX_F3 ? "EDIT" : (a == EX_INSERT ? "NEW" : "DELETE"));
					} 
				}while(1);
		    	break;
		    case ENTER:
		    	if(tab ==  2) break;
		    	Selection_Sort_DSMH(DSMH);
				Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword);
				ClearRemainMonHoc(stt, pointX, pointY = 8, 0);
				n = (int)ceil((double)stt/15);
				PrintPageTable(currentPage+1, n);
				PrintKeyWord("%-50s", keyword, x, y);
				break;
		    case ESC:
		    	delete DSMH;
		    	ClearTable(1);
		        return;
	    }
	} while (1);
	
}


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
