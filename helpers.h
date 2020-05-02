#include <iostream>
#include <conio.h>
#include "console.h"
std::string convertToString(char* a, int size);
void ClearMessage(std::string s);
void Message(std::string s, std::string s2, int type, int ms);
int InputValue(int maxlength, std::string pattern, std::string &keyword, int &x, int &y, int type);
void PrintKeyWord(std::string pattern, std::string keyword, int &x, int &y);

void DrawTitle(char *title, int x);
void DrawTitleTable(int pointX, int pointY, int select, char ListText[10][31], int number);

void DrawTitleYesNoMH(int pointY, int select, std::string state);
void DrawButtonYesNoMH(int pointY, std::string state);
void ClearButtonYesNoMH(int pointY);
void DrawInput(int pointX, int pointY);
void ClearInput(int x, int y, int n);

void DrawHuongDanTable(int pointX, int pointY, char FunctionText[10][5][30], int n);
void PrintPageTable(int currentPage, int totalPage);
void PrintSearchInput(std::string keyword);
int InputSearch(std::string &keyword, int &x, int &y);
