#include <iostream>
#include "console.h"
#include "helpers.h"
#include "struct/structs.h"
#include "menu.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	system("cls");
	ResizeConsole(1353, 800);
	RemoveScrollbar();
	SetTitleAndBgColor("QUAN LY DIEM SINH VIEN", "color F0");
	DrawBorder();
	ShowHuongDan();
	LoadAllDataFromFile();
	ShowMenu();
	system("pause");
	return 0;
}


