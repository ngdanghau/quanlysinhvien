#include "helpers.h"
#include "../constant.h"
std::string convertToString(char* a, int size) 
{ 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

std::string ConvertIntToString(int a){
	std::string s = "", temp = ""; 
    int n = 0, du;

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

void Message(std::string s, std::string s2, int type, int ms)
{
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

int InputValue(int maxlength, string pattern, string &keyword, int &x, int &y, int type){
	int c;
	int len = keyword.length();
	
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
			}else if (  (c > 48 && c < 51 ) ){
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

void DrawTitleTable(int pointX, int pointY, int select, char ListText[10][MENU_TEXT_LENGTH], int number){
	GoToXY(pointX-6, pointY+2);
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
		
		cout << ListText[i];
		if(i == number-1) {
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

void DrawHuongDanTable(int pointX, int pointY, char FunctionText[10][5][30], int n){
	for(int i = 0; i < n; i++){
		GoToXY(pointX+16*i + 5, pointY);
		SetBGColor(14);
		SetColor(RED);
		cout << FunctionText[0][i];
		SetColor(BLACK);
		SetBGColor(WHITE);
		cout << FunctionText[1][i];
	}
}

void PrintSearchInput(string keyword){
	GoToXY(47, 6);
	cout << "Tim kiem: " + keyword;
	Typing();
}

int InputSearch(string &keyword, int &x, int &y){
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
				PrintKeyWord("%-50s", keyword, x, y);
			}
		}else if(c == BACKSPACE){
			--len;
			keyword = keyword.substr(0, len--);
			PrintKeyWord("%-50s", keyword, x, y);
		}else return c;
	}
}

void PrintPageTable(int currentPage, int totalPage){
	GoToXY(140, 40);
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

