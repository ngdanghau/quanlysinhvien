#include "monhoc.h"
#include "../constant.h"
#include "../console.h"
#include "../helpers.h"
using namespace std;
/*
* — Khai bao bien toan cuc —
*/
TREE tree = NULL;
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

void PrintPageMonHoc(int currentPage, int totalPage){
	GoToXY(140, 40);
	SetBGColor(GREEN);
	SetColor(WHITE);
	printf("Trang %d/%d", currentPage, totalPage);
	SetBGColor(WHITE);
	SetColor(BLACK);
}

void PrintSearchInput(string keyword){
	GoToXY(47, 6);
	cout << "Tim kiem: " + keyword;
	Typing();
}

void PrintKeyWord(string keyword, int &x, int &y){
	HideTyping();
	GoToXY(x, y);
	printf("%-50s", " ");
	GoToXY(x, y);
	cout << keyword;
	Typing();
}

int InputMonHoc(string &keyword, int &x, int &y, int type){
	int c;
	int len = keyword.length();
	
	if(type == 4) HideTyping();
	else Typing();
	
	if(type == 0){
		while(1){
			len = keyword.length();
			c = getch();
			if( c == 224 || c == 0){
				c = 256 + getch();
				return c;
			}else if (  (c > 47 && c < 58 ) || ( c > 64 && c < 91)   ){
				if(len < 50){
					keyword.push_back(char(c));
					PrintKeyWord(keyword, x, y);
				}
			}else if ( c > 96 && c < 123 ){
				if(len < 50){
					keyword.push_back(char(c-32));
					PrintKeyWord(keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(keyword, x, y);
			}else return c;
		}
	}else if(type == 1){
		while(1){
			len = keyword.length();
			c = getch();
			if( c == 224 || c == 0){
				c = 256 + getch();
				return c;
			}else if (  (c > 47 && c < 58 ) || ( c > 64 && c < 91) ||  ( c > 96 && c < 123 ) || c == SPACE ){
				if(len < 50){
					if(c == 32 ){
						if(len == 0 || keyword[len-1] == SPACE) break;
					}
					keyword.push_back(char(c));
					PrintKeyWord(keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(keyword, x, y);
			}else return c;
		}
	}else if(type == 2 || type == 3){
		while(1){
			len = keyword.length();
			c = getch();
			if( c == 224 || c == 0){
				c = 256 + getch();
				return c;
			}else if (  (c > 47 && c < 58 ) ){
				if(len < 10){
					keyword.push_back(char(c));
					PrintKeyWord(keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(keyword, x, y);
			}else return c;
		}
	}else if(type == 4){
		while(1){
			c = getch();
			if( c == 224 || c == 0){
				c = 256 + getch();
				return c;
			}else return c;
		}
	}
}

int InputSearchMonHoc(string &keyword, int &x, int &y){
	int c;
	int len = keyword.length();
	while(1){
		len = keyword.length();
		c = getch();
		if( c == 224 || c == 0){
			c = 256 + getch();
			return c;
		}else if ( (c > 96 && c < 123) || ( c > 31 && c < 90 )  ){
			if(len < 50){
				if(c == 32 ){
					if(len == 0 || keyword[len-1] == SPACE) break;
				}
				keyword.push_back(char(c));
				PrintKeyWord(keyword, x, y);
			}
		}else if(c == BACKSPACE){
			--len;
			keyword = keyword.substr(0, len--);
			PrintKeyWord(keyword, x, y);
		}else return c;
	}
}

void ClearInputThemMonHoc(int x, int y){
	HideTyping();
	for(int i = 0; i < 4; i++){
		GoToXY(x, y+=4);
		printf("%-50s"," ");
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

void DrawHuongDanTableMonHoc(int pointX, int pointY){
	for(int i = 0; i < NUMBER_ITEM_MONHOC_FUNCTION_TEXT; i++){
		GoToXY(pointX+16*i + 5, pointY);
		SetBGColor(14);
		SetColor(RED);
		cout << MonHocFunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << MonHocFunctionText[1][i];
	}
}

void DrawTitleTableMonHoc(int pointX, int pointY, int select){
	GoToXY(pointX-6, pointY+2);
	int number = 3;
	for(int i = 1; i < number; i++){
		SetBGColor(WHITE);
		SetColor(BLACK);
		cout << "|";
		
		if(i == select){
			SetColor(WHITE);
			SetBGColor(BLUE);
		}else {
			SetColor(BLACK);
			SetBGColor(WHITE);
		}
		
		cout << MonHocText[i];
		if(i == number-1) {
			SetColor(BLACK);
			SetBGColor(WHITE);
			cout << "|";
		}
	}
	
}

void DrawTitleMonHoc(char *title, int x){
	GoToXY(x, 1);
	cout << title;
	GoToXY(79, 2);
	cout << "-------------------------------------------";
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
	DrawHuongDanTableMonHoc(48, 40);
	
	DrawTitleMonHoc(MonHocText[0], 87);
	
	DrawTitleTableMonHoc(87, 1, 1);
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

void DrawInputThemMonHoc(int pointX, int pointY){
	GoToXY(pointX, pointY);
    cout << char(TOP_LEFT_CORNER_SIMPLE);
    for (int k=1; k < INPUT_TEXT_LENGTH-5; k++)
        cout << char(HORIZONTAL_LINE);	
        
    cout << char(TOP_RIGHT_CORNER_SIMPLE);
    GoToXY(pointX, pointY+1);
    cout << char(VERTICAL_LINE);
    
    for(int k = 0; k < INPUT_TEXT_LENGTH-6; k++)
        cout << " ";

    cout << char(VERTICAL_LINE);
    GoToXY(pointX, pointY+2);
    cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
    
    for (int k=1; k< INPUT_TEXT_LENGTH-5; k++)
        cout << char(HORIZONTAL_LINE);
        
    cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
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
		DrawInputThemMonHoc(85, pointY+2+i*4);
	}
	GoToXY(87, 8);
	Typing();
}

void DrawTitleYesNoMH(int select, string state){
	HideTyping();
	GoToXY(76, 23);
	
	SetColor(GREEN);
	
	if(select == 0){
		SetColor(WHITE);
		SetBGColor(GREEN);
	}
	if(state == "EDIT")
		cout << " LUU THAY DOI ";
	else if(state == "DELETE")
		cout << " XAC NHAN XOA ";
	GoToXY(110, 23);
	
	
	SetColor(RED);
	SetBGColor(WHITE);
	
	if(select == 1){
		SetColor(WHITE);
		SetBGColor(RED);
	}
	if(state == "EDIT")
		cout << " HUY THAY DOI ";
	else if(state == "DELETE")
		cout << "    HUY XOA   ";
	
	SetBGColor(WHITE);
	SetColor(BLACK);
}

void DrawButtonYesNoMH(string state){
	int pointX = 75, pointY = 22;
	int width = 15;
	for(int i = 0; i < 2; i++){
		GoToXY(pointX + i*34, pointY);
	    cout << char(TOP_LEFT_CORNER_SIMPLE);
	    for (int k=1; k < width; k++)
	        cout << char(HORIZONTAL_LINE);	
	        
	    cout << char(TOP_RIGHT_CORNER_SIMPLE);
	    GoToXY(pointX + i*34, pointY+1);
	    cout << char(VERTICAL_LINE);
	    
	    for(int k = 0; k < width-1; k++)
	        cout << " ";
	
	    cout << char(VERTICAL_LINE);
	    GoToXY(pointX + i*34, pointY+2);
	    cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
	    
	    for (int k=1; k< width; k++)
	        cout << char(HORIZONTAL_LINE);
	        
	    cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
	}
	DrawTitleYesNoMH(-1, state);
}

void ClearButtonYesNoMH(){
	int pointX = 75, pointY = 22;
	for(int i = 0; i < 4; i++){
		GoToXY(pointX, pointY+i);
		printf("%-70s"," ");
	}
}

int ThemMonHoc(TREE &DSMH, string state){
	DrawTitleMonHoc(MonHocText[0], 87);
	MonHoc mh;
	TREE p;
	int x = 87, y = 8;
	string temp = "";
	int c, type = 0;
	int is_delete = 0;
	if(state == "NEW"){
		DrawBoderThemMonHoc("NHAP THONG TIN DE THEM MON HOC!");
		do{
			c = InputMonHoc(temp, x, y, type);
			switch (c) {
				case EX_F3:
			        return c;
			    case EX_INSERT:
			        return c;
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
						
				    	ClearInputThemMonHoc(x, y);
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
			c = InputMonHoc(temp, x, y, type);
			switch (c) {
				case EX_F3:
			        return c;
			    case EX_INSERT:
			        return c;
			    case EX_DEL:
			        return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    	if(type < 3) break;
			    	if(is_delete == 1) is_delete = 0;
			    	DrawTitleYesNoMH(is_delete, state);
			        break;
			    case EX_RIGHT:
			    	if(type < 3) break;
			    	if(is_delete == 0) is_delete = 1;
			    	DrawTitleYesNoMH(is_delete, state);
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
						DrawButtonYesNoMH(state);
						
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
						DrawTitleYesNoMH(is_delete, state);
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
						DrawTitleYesNoMH(-1, state);
						ClearInputThemMonHoc(x, 4);
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
			c = InputMonHoc(temp, x, y, type);
			switch (c) {
				case EX_F3:
			        return c;
			    case EX_INSERT:
			        return c;
			    case EX_DEL:
			        return c;
				case TAB:
			        return 0;
			    case EX_LEFT:
			    	if(type < 3) break;
			    	if(is_delete == 1) is_delete = 0;
			    	DrawTitleYesNoMH(is_delete, state);
			        break;
			    case EX_RIGHT:
			    	if(type < 3) break;
			    	if(is_delete == 0) is_delete = 1;
			    	DrawTitleYesNoMH(is_delete, state);
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
						DrawButtonYesNoMH(state);
						DrawTitleYesNoMH(is_delete, state);
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
						DrawTitleYesNoMH(-1, state);
						ClearInputThemMonHoc(x, 4);
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
		c = InputMonHoc(temp, x, y, 0);
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
		DrawTitleTableMonHoc(87, 1, tab);
		a = ThemMonHoc(DSMH, state);
		if(a == ESC) {
			ClearTableMonHoc(1);
			return;
		}
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
	PrintPageMonHoc(currentPage+1, n);
	DrawTableMonHoc();
	Traverse_DSMH(DSMH, stt, pointX, pointY, currentPage, keyword);
	PrintSearchInput(keyword);
	
	do {
	    c = InputSearchMonHoc(keyword, x, y);
	    switch (c) {
		    case EX_UP:
		    	if(tab ==  2) break;
		        if (currentPage + 1 > 1) {
		            currentPage--; 
		            HideTyping();
		            Selection_Sort_DSMH(DSMH);
					Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword);
					n = (int)ceil((double)stt/15);
					PrintPageMonHoc(currentPage+1, n);
					PrintSearchInput(keyword);
		        }
		        break;
		    case EX_DOWN:
		    	if(tab ==  2) break;
		        if (currentPage + 1 < n) {
		            currentPage++;
		            HideTyping();
		            Selection_Sort_DSMH(DSMH);
					Traverse_DSMH(DSMH, stt = 0, pointX, pointY, currentPage, keyword);
					n = (int)ceil((double)stt/15);
					PrintPageMonHoc(currentPage+1, n);
					
					if(currentPage == n-1)
						ClearRemainMonHoc(stt, pointX, pointY, currentPage);
					
					PrintSearchInput(keyword);
		        }
		        break;
		    case EX_F3: 
		    	tab = 2;
		    	DrawTitleTableMonHoc(87, 1, tab);
		    	ClearTableMonHoc(0);
				a = ThemMonHoc(DSMH, "EDIT");
				do{
					if(a == 0){
						x = 57, y = 6;
						tab = 1;
						ClearTableMonHoc(0);
				    	PrintPageMonHoc(currentPage+1, n);
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
						ClearButtonYesNoMH();
						a = ThemMonHoc(DSMH, "NEW");
					}else if(a == EX_DEL){
						HideTyping();
						ClearButtonYesNoMH();
						a = ThemMonHoc(DSMH, "DELETE");
					}else if(a == ESC) {
						ClearTableMonHoc(1);
						return;
					}
				}while(1);
		    	break;
		    case EX_DEL: 
		    	tab = 2;
		    	DrawTitleTableMonHoc(87, 1, tab);
		    	ClearTableMonHoc(0);
				a = ThemMonHoc(DSMH, "DELETE");
				do{
					if(a == 0){
						x = 57, y = 6;
						tab = 1;
						ClearTableMonHoc(0);
				    	PrintPageMonHoc(currentPage+1, n);
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
						ClearButtonYesNoMH();
						a = ThemMonHoc(DSMH, "NEW");
					}else if(a == EX_DEL){
						HideTyping();
						ClearButtonYesNoMH();
						a = ThemMonHoc(DSMH, "DELETE");
					}else if(a == ESC) {
						ClearTableMonHoc(1);
						return;
					}
				}while(1);
		    	break;
		    case TAB: 
		    	tab = (tab == 1) ? 2 : 1;
		    	DrawTitleTableMonHoc(87, 1, tab);
		    	if(tab == 1){
		    		x = 57, y = 6;
		    		ClearTableMonHoc(0);
		    		PrintPageMonHoc(currentPage+1, n);
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
				    		PrintPageMonHoc(currentPage+1, n);
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
							ClearButtonYesNoMH();
							a = ThemMonHoc(DSMH, "NEW");
						}else if(a == EX_DEL){
							HideTyping();
							ClearButtonYesNoMH();
							a = ThemMonHoc(DSMH, "DELETE");
						}else if(a == ESC) {
							ClearTableMonHoc(1);
							return;
						}
					}while(1);
				}
		    	break;
		    case EX_INSERT: 
		    	if(tab == 2) break;
		    	tab = 2;
				ClearTableMonHoc(0);
				DrawTitleTableMonHoc(87, 1, tab);
				a = ThemMonHoc(DSMH, "NEW");
				do{
					if(a == 0){
						x = 57, y = 6;
						tab = 1;
						ClearTableMonHoc(0);
				    	PrintPageMonHoc(currentPage+1, n);
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
						ClearButtonYesNoMH();
						a = ThemMonHoc(DSMH, "NEW");
					}else if(a == EX_DEL){
						HideTyping();
						ClearButtonYesNoMH();
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
				PrintPageMonHoc(currentPage+1, n);
				PrintKeyWord(keyword, x, y);
				break;
		    case ESC:
		    	delete DSMH;
		    	ClearTableMonHoc(1);
		        return;
	    }
	} while (1);
	
}
