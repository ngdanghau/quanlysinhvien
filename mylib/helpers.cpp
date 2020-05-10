#include "helpers.h"
#include "../constant.h" 
std::string convertToString(char* a, int size) { 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

std::string ConvertIntToString(int a){
	std::string s = "", temp = ""; 
    int du;

	while (a != 0)
	{
		du = a % 10;
		temp.push_back((char)( du + '0'));
		a = a / 10;
		
	}

	int length = temp.length();
    for (int i = length-1; i > -1; i--) {
        s.push_back(temp[i]);
    }
    return s; 
}

/* Function cho thong bao */
void ClearMessage(std::string s){
	GoToXY(34, 43);
	printf("%-60s"," ");
	GoToXY(34, 44);
	printf("%-60s"," ");
}

void Message(std::string s, std::string s2, int type, int ms){
	HideTyping();
	SetColor(RED);
	if(type == 1)
		SetColor(GREEN);
    GoToXY(34, 43);
    std::cout << s;
    GoToXY(34, 44);
    std::cout << s2;
    Sleep(ms);
    ClearMessage(s);
    SetColor(BLACK);
}

void PrintKeyWord(string pattern, string keyword, int &x, int &y){
	HideTyping();
	GoToXY(x, y);
	printf(pattern.c_str(), " ");
	GoToXY(x, y);
	cout << keyword;
	Typing();
}

int InputValue(int maxlength, string &keyword, int &x, int &y, int type){
	int c;
	int len = keyword.length();
	string pattern = "%-" + ConvertIntToString(maxlength) + "s";
	GoToXY(x+len, y);
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
				if(len < maxlength){
					keyword.push_back(char(c));
					PrintKeyWord(pattern, keyword, x, y);
				}
			}else if ( c > 96 && c < 123 ){
				if(len < maxlength){
					keyword.push_back(char(c-32));
					PrintKeyWord(pattern, keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(pattern, keyword, x, y);
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
				if(len < maxlength){
					if(c == 32 ){
						if(len == 0 || keyword[len-1] == SPACE) break;
					}
					keyword.push_back(char(c));
					PrintKeyWord(pattern, keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(pattern, keyword, x, y);
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
				if(len < maxlength){
					keyword.push_back(char(c));
					PrintKeyWord(pattern, keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(pattern, keyword, x, y);
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
	}else if(type == 5){
		while(1){
			len = keyword.length();
			c = getch();
			if( c == 224 || c == 0){
				c = 256 + getch();
				return c;
			}else if (  (c > 47 && c < 58 ) || ( c > 64 && c < 91)  || c == 45){
				if(len < maxlength){
					keyword.push_back(char(c));
					PrintKeyWord(pattern, keyword, x, y);
				}
				return 201;
			}else if ( c > 96 && c < 123 ){
				if(len < maxlength){
					keyword.push_back(char(c-32));
					PrintKeyWord(pattern, keyword, x, y);
				}
				return 201;
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(pattern, keyword, x, y);
				return 201;
			}else return c;
		}
	}else if(type == 6){
		while(1){
			len = keyword.length();
			c = getch();
			if( c == 224 || c == 0){
				c = 256 + getch();
				return c;
			}else if (  (c > 48 && c < 52 ) ){
				if(len < maxlength){
					keyword.push_back(char(c));
					PrintKeyWord(pattern, keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(pattern, keyword, x, y);
			}else return c;
		}
	}else if(type == 7){
		while(1){
			len = keyword.length();
			c = getch();
			if( c == 224 || c == 0){
				c = 256 + getch();
				return c;
			}else if (  (c > 47 && c < 58 ) || c == 45 ){
				if(len < maxlength){
					keyword.push_back(char(c));
					PrintKeyWord(pattern, keyword, x, y);
				}
			}else if(c == BACKSPACE){
				--len;
				keyword = keyword.substr(0, len--);
				PrintKeyWord(pattern, keyword, x, y);
			}else return c;
		}
	}
}

void DrawTitle(char *title, int x){
	GoToXY(x, 1);
	cout << title;
	GoToXY(79, 2);
	cout << "-------------------------------------------";
}

void DrawTitleTable(int pointX, int pointY, int select, char ListText[10][MENU_TEXT_LENGTH]){
	GoToXY(pointX-6, pointY+2);
	for(int i = 1; i < 3; i++){
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
		
		cout << ListText[i];
		if(i == 2) {
			SetColor(BLACK);
			SetBGColor(WHITE);
			cout << "|";
		}
	}	
}


void DrawTitleYesNo(int pointY, int select, string state){
	HideTyping();
	GoToXY(76, pointY);
	
	SetColor(GREEN);
	
	if(select == 0){
		SetColor(WHITE);
		SetBGColor(GREEN);
	}
	if(state == "EDIT")
		cout << " LUU THAY DOI ";
	else if(state == "DELETE")
		cout << " XAC NHAN XOA ";
	else if(state == "HUYLOPTC")
		cout << "    DONG Y    ";
	GoToXY(110, pointY);
	
	
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
	else if(state == "HUYLOPTC")
		cout << "    TU CHOI   ";
	
	SetBGColor(WHITE);
	SetColor(BLACK);
}

void DrawButtonYesNo(int pointY, string state){
	int pointX = 75;
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
	DrawTitleYesNo(pointY+1, -1, state);
}

void ClearButtonYesNo(int pointY){
	int pointX = 75;
	for(int i = 0; i < 3; i++){
		GoToXY(pointX, pointY+i);
		printf("%-60s"," ");
	}
}

void DrawInput(int pointX, int pointY){
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

void ClearInput(int x, int y, int n){
	HideTyping();
	for(int i = 0; i < n; i++){
		GoToXY(x, y+=4);
		printf("%-50s"," ");
	}
}

void ClearTable(int is_clear_title){
	HideTyping();
	int height = 37;
	int pointY = 5;
	if(is_clear_title){
		height = 41;
		pointY = 1;
	}
	for (int i = 0; i < height; i++){
		GoToXY(33, i+pointY);
		printf("%-120s"," ");
	}
}

void DrawTitleFunction(int pointX, int pointY, char FunctionText[10][5][30], int n, int is_skip){
	GoToXY(pointX, pointY);
	for(int i = 0; i < n; i++){
		if(is_skip && i == 1) continue;
		SetBGColor(14);
		SetColor(RED);
		cout << FunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << FunctionText[1][i];
		if(i < n -1)
			cout << char(HORIZONTAL_LINE) << char(HORIZONTAL_LINE) << char(HORIZONTAL_LINE);
	}
}


void DrawHuongDanTable(int pointX, int pointY, char FunctionText[10][5][30], int n){
	GoToXY(pointX, pointY);
	for(int i = 0; i < n; i++){
		SetBGColor(14);
		SetColor(RED);
		cout << FunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << FunctionText[1][i];
		cout << "   ";
	}
}

void PrintSearchInput(int x, string keyword){
	GoToXY(x, 6);
	cout << "Tim kiem: " + keyword;
	Typing();
}

int InputSearch(string &keyword, int &x, int &y, int length){
	Typing();
	int c;
	int len = keyword.length();
	string pattern = "%-" + ConvertIntToString(length) + "s";
	while(1){
		len = keyword.length();
		c = getch();
		if( c == 224 || c == 0){
			c = 256 + getch();
			return c;
		}else if ( (c > 96 && c < 123) || ( c > 31 && c < 90 )  ){
			if(len < length){
				if(c == 32 ){
					if(len == 0 || keyword[len-1] == SPACE) break;
				}
				keyword.push_back(char(c));
				PrintKeyWord(pattern, keyword, x, y);
			}
		}else if(c == BACKSPACE){
			--len;
			keyword = keyword.substr(0, len--);
			PrintKeyWord(pattern, keyword, x, y);
		}else return c;
	}
}

void PrintPageTable(int currentPage, int totalPage, int x){
	GoToXY(x, 40);
	SetBGColor(GREEN);
	SetColor(WHITE);
	printf("Trang %d/%d", currentPage, totalPage);
	SetBGColor(WHITE);
	SetColor(BLACK);
}


int GetHocKyByTime(){
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	int month = 1 + ltm->tm_mon;
	if( 0 < month < 7){
		return 1;
	}else return 2;
}

int GetYear(){
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	return 1900 + ltm->tm_year;
}


void DrawArrowTable(int pointX, int pointY, int select, int currentPage, int stt){
	HideTyping();
	for(int i = 0; i < stt;i++){
		GoToXY(pointX, pointY+=2);
		if(i == select){
			SetColor(LIGHT_PURPLE);
			cout << ">>>>>";
			SetColor(BLACK);
		}else printf("%-6d", (i+1) + 15*currentPage);
	}
}


int InArray(int a, int *array, int n){
	for(int i = 0; i < n; i++){
		if(a == array[i]) return i;
	}
	return -1;
}


void Remove_Element(int *array, int index, int &n){
   int i;
   for(i = index; i < n-1; i++) array[i] = array[i + 1];
   n--;
}

int AddLopTC(int *array, int value, int &n){
	int check = -1;
	check = InArray(value, array, n);
	if(check != -1){
		Remove_Element(array, check , n);
		return 0;
	}
	array[n] = value;
	n++;
	return 1;
}









