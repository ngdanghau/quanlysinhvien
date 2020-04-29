#include "helpers.h"
#include "constant.h"
std::string convertToString(char* a, int size) 
{ 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
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
