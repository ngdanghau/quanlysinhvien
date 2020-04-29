#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>
#include <iostream>
using namespace std;

void ResizeConsole(int width, int height);
void RemoveScrollbar();
void SetTitleAndBgColor(string title, string color);
void GoToXY(int x, int y);
int GetX();
int GetY();
void HideTyping();
void Typing();
void SetColor(WORD color);
void SetBGColor(WORD color);

#endif

