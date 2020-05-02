#include "structs.h"
#include "../constant.h"
#include "../console.h"
#include "../helpers.h"
/*
* — Khai bao bien toan cuc —
*/
TREE tree = NULL;
DSLOPPTR ListLop;
LISTSV First = NULL;
/*
* === END ===
*/

using namespace std;
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
		cout << "File Khong Ton Tai";
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
	do {
	    c = InputValue(30, "%-30s", keyword, x, y, 5);
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
		    		DrawCharArrow(select = stt > -1 ? 0 : -1, stt+1);
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
		if( strcmp(p->SV.MALOP, malophoc) == 0 && (ten.find(keyword) != string::npos || ho.find(keyword) !=  string::npos || masv.find(keyword) !=  string::npos) ) count++;
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
        
    	if( stt < 16 && strcmp(p->SV.MALOP, malophoc) == 0  ){
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
        	if( strcmp(q->SV.MALOP, malophoc) == 0 ){
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


void ClearTableSinhVien(int is_clear_title){
	HideTyping();
	int height = 38;
	int pointY = 4;
	if(is_clear_title){
		height = 41;
		pointY = 1;
	}
	for (int i = 0; i < height; i++){
		GoToXY(33, i+pointY);
		printf("%-120s"," ");
	}
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
	int x = 87, y = 8;
	string temp = "";
	int c, type = 0, index = 0;
	int is_delete = 0, gender = 1;
	
	if(state == "NEW"){
		DrawBoderThemSinhVien("NHAP THONG TIN DE THEM SINH VIEN!", malophoc);
		DrawInputGender(87, 24, -1);
			do{
			c = InputValue(50, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
			    case EX_DEL:
			    	if(is_new_class){
			    		Message("ERROR:", "Danh Sach Sinh Vien Rong Khong The Xoa Hoac Sua!", 0, 1500);
			    		break;
					}
			    case EX_INSERT:
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
						type = 1;
						strcpy(sv.MALOP, malophoc);
					}else if(index == 1){
						strcpy(sv.HO, temp.c_str());
					}else if(index == 2){
						strcpy(sv.TEN, temp.c_str());
						type = 4, index = 3, y+=4;
						DrawInputGender(x, y+4, gender);
					}else if(index == 4){
						temp = gender == 1 ? "Nam" : "Nu";
						sv.PHAI = gender;
						type = 3;
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
			    		DrawTitleYesNoMH(32, is_delete, state);
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
						DrawButtonYesNoMH(31, state);
						
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
						DrawTitleYesNoMH(32, is_delete, state);
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
				    	ClearButtonYesNoMH(31);
				    	
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
			    	return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(index < 6) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNoMH(32, is_delete, state);
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
						DrawButtonYesNoMH(31, state);
						DrawTitleYesNoMH(32, is_delete, state);
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
						DrawTitleYesNoMH(32, -1, state);
						ClearInput(x, 4, 4);
						ClearButtonYesNoMH(31);
						GoToXY(x, y);
					}
			    	break;
			    case ESC:
			        return c;
			}
		}while(1);
	}
}

void DrawTableSinhVien(char *malophoc){
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
	DrawHuongDanTable(48, 40, SinhVienFunctionText, NUMBER_ITEM_SINHVIEN_FUNCTION_TEXT);
	
	
	char title[50];
	strcpy(title, SinhVienText[0]);
	strcat(title, " LOP: ");
	strcat(title, malophoc);
	
	DrawTitle(title, 78);
	DrawTitleTable(87, 1, 1, SinhVienText, 3);
}

void ClearRemainSinhVien(int total, int pointX, int pointY, int currentPage){
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
					ClearTableSinhVien(1);
		        	return;
			}
		    if (a == 0) break;
		} while (1);
		
		ClearTableSinhVien(0);
		tab = 1;
	}
	
	if(First == NULL){
		Message("ERROR:", "Danh Sach Sinh Vien Rong!", 0, 1000);
		ClearTableSinhVien(1);
		return;
	}
	
	int stt = 0, pointX = 47, pointY = 8, x = 57, y = 6;
	int total = Reccount_SV(First, malophoc);
	
	if(total == 0){
		Message("ERROR:", "Danh Sach Sinh Vien Rong!", 0, 1000);
		ClearTableSinhVien(1);
		return;
	}
	

	int n = (int)ceil((double)total/15);
	int currentPage = 0;
	string keyword = "";
	
	LISTSV *pages = new LISTSV[n];
	
	Message("SUCCESS:", "Load Du Lieu Sinh Vien Thanh Cong!", 1, 500);
	PrintPageTable(currentPage+1, n);
	DrawTableSinhVien(malophoc);
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
					ClearRemainSinhVien(stt, pointX, pointY, currentPage);
						
				PrintSearchInput(keyword);
				
		        break;
		    case TAB: 
		    	tab = (tab == 1) ? 2 : 1;
		    	DrawTitleTable(87, 1, tab, SinhVienText, 3);
		    	if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTableSinhVien(0);
		    		PrintPageTable(currentPage+1, n);
					DrawTableSinhVien(malophoc);
					Selection_Sort_SV(First, malophoc);
					Traverse_SV(First, malophoc, stt = 0, pointX, pointY, currentPage, keyword, pages);
					PrintSearchInput(keyword);
					
				}else{
					ClearTableSinhVien(0);
					a = ThemSinhVien(First, "NEW", malophoc, is_new_class);
					do{
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTableSinhVien(0);
				    		PrintPageTable(currentPage+1, n);
							DrawTableSinhVien(malophoc);
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
							ClearTableSinhVien(1);
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
				ClearTableSinhVien(0);
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
						ClearTableSinhVien(0);
				    	PrintPageTable(currentPage+1, n);
						DrawTableSinhVien(malophoc);
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
						ClearTableSinhVien(1);
						return;
					}
				}while(1);
		    	break;
		    case ENTER:
		    	if(tab ==  2) break;
		    	Selection_Sort_SV(First, malophoc);
				Traverse_SV(First, malophoc, stt = 0, pointX, pointY = 8, currentPage, keyword, pages);
				ClearRemainSinhVien(stt, pointX, pointY = 8, 0);
				total = Reccount_SV_With_Keyword(First, malophoc, keyword);
				n = (int)ceil((double)total/15);
				PrintPageTable(currentPage+1, n);
				PrintKeyWord("%-50s", keyword, x, y);

				break;
		    case ESC:
		    	delete pages;
		    	ClearTableSinhVien(1);
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

void ClearTableMonHoc(int is_clear_title){
	HideTyping();
	int height = 38;
	int pointY = 4;
	if(is_clear_title){
		height = 41;
		pointY = 1;
	}
	for (int i = 0; i < height; i++){
		GoToXY(33, i+pointY);
		printf("%-120s"," ");
	}
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

void DrawTableMonHoc(){
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
	int x = 87, y = 8;
	string temp = "";
	int c, type = 0;
	int is_delete = 0;
	if(state == "NEW"){
		DrawBoderThemMonHoc("NHAP THONG TIN DE THEM MON HOC!");
		do{
			c = InputValue(50, "%-50s", temp, x, y, type);
			switch (c) {
				case EX_F3:
			    case EX_INSERT:
			    case EX_DEL:
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
					}else if(type == 1){
						if(temp[temp.length()-1] == SPACE) temp = temp.substr(0, temp.length()-1);
						strcpy(mh.TENMH, temp.c_str());
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
				    	type = 0, y = 4;
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
			        return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(type < 3) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNoMH(23, is_delete, state);
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
						DrawButtonYesNoMH(22, state);
						
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
						temp = "";
						temp.push_back((char)( p->MH.STCLT + '0'));
						GoToXY(x + temp.length(), y+=4);
						type++;
					}else if(type == 2){
						sscanf(temp.c_str(), "%d", &mh.STCLT);
						temp = "";
						temp.push_back((char)( p->MH.STCTH + '0'));
						GoToXY(x + temp.length(), y+=4);
						type++;
					}else if(type == 3){
						sscanf(temp.c_str(), "%d", &mh.STCTH);
						temp = "";
						GoToXY(x + temp.length(), y+=4);
						type++;
						DrawTitleYesNoMH(23, is_delete, state);
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
						DrawTitleYesNoMH(23, -1, state);
						ClearInput(x, 4, 4);
						ClearButtonYesNoMH(22);
						GoToXY(x, y);
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
			    	return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    case EX_RIGHT:
			    	if(type < 3) break;
			    	is_delete = is_delete == 1 ? 0 : 1;
			    	DrawTitleYesNoMH(23, is_delete, state);
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
						DrawButtonYesNoMH(22, state);
						DrawTitleYesNoMH(23, is_delete, state);
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
						DrawTitleYesNoMH(23, -1, state);
						ClearInput(x, 4, 4);
						ClearButtonYesNoMH(22);
						GoToXY(x, y);
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


int ChinhSuaMonHoc(){
	DrawBorderEditMonHoc();
	int c, x = 57, y = 6;
	string temp;
	do{
		c = InputValue(50, "%-50s", temp, x, y, 0);
		switch (c) {
			case TAB:
		        return 0;
		    case ENTER:
		    	break;
		    case ESC:
		        return c;
		}
	}while(1);
}

void PrintDataMonHoc(int tab, string state){
	
	TREE DSMH = NULL;
	int c, a;
	
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
					state = "EDIT";
					break;
				case EX_INSERT:
					state = "NEW";
					break;
				case EX_DEL:
					state = "DELETE";
					break;
				case ESC:
					ClearTableMonHoc(1);
		        	return;
			}
		    if (a == 0) break;
		} while (1);
		
		ClearTableMonHoc(0);
		tab = 1;
	}
	
	if(tree == NULL){
		Message("ERROR:", "Danh Sach Mon Hoc Rong!", 0, 1000);
		ClearTableMonHoc(1);
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
	DrawTableMonHoc();
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
		    		ClearTableMonHoc(0);
		    		PrintPageTable(currentPage+1, n);
					DrawTableMonHoc();
					Selection_Sort_DSMH(DSMH);
					Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword);
					PrintSearchInput(keyword);
				}else{
					ClearTableMonHoc(0);
					a = ThemMonHoc(DSMH, "NEW");
					do{
						if(a == 0){
							x = 57, y = 6;
							tab = 1;
							ClearTableMonHoc(0);
				    		PrintPageTable(currentPage+1, n);
							DrawTableMonHoc();
							Selection_Sort_DSMH(DSMH);
							Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword);
							PrintSearchInput(keyword);
							break;
						}else if(a == EX_F3){
							HideTyping();
							a = ThemMonHoc(DSMH, "EDIT");
						}else if(a == EX_INSERT){
							HideTyping();
							a = ThemMonHoc(DSMH, "NEW");
						}else if(a == EX_DEL){
							HideTyping();
							a = ThemMonHoc(DSMH, "DELETE");
						}else if(a == ESC) {
							ClearTableMonHoc(1);
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
				ClearTableMonHoc(0);
				DrawTitleTable(87, 1, tab, MonHocText, 3);
				if(c == EX_F3)
		    		a = ThemMonHoc(DSMH, "EDIT");
		    	else if(c == EX_DEL)
					a = ThemMonHoc(DSMH, "DELETE");
				else if(c == EX_INSERT)
					a = ThemMonHoc(DSMH, "NEW");
				do{
					if(a == 0){
						x = 57, y = 6;
						tab = 1;
						ClearTableMonHoc(0);
				    	PrintPageTable(currentPage+1, n);
						DrawTableMonHoc();
						Selection_Sort_DSMH(DSMH);
						Traverse_DSMH(DSMH, stt = 0, pointX, pointY = 8, currentPage, keyword);
						PrintSearchInput(keyword);
						break;
					}else if(a == EX_F3){
						HideTyping();
						a = ThemMonHoc(DSMH, "EDIT");
					}else if(a == EX_INSERT){
						HideTyping();
						a = ThemMonHoc(DSMH, "NEW");
					}else if(a == EX_DEL){
						HideTyping();
						a = ThemMonHoc(DSMH, "DELETE");
					}else if(a == ESC) {
						ClearTableMonHoc(1);
						return;
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
		    	ClearTableMonHoc(1);
		        return;
	    }
	} while (1);
	
}


void LoadAllDataFromFile(){
	Load_MonHoc();
	Load_SinhVien();
}
