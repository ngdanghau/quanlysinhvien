#ifndef MENU_H
#define MENU_H

#include <windows.h>
#include <string.h>
#include <conio.h>
#include "constant.h"
#include "text.h"

using namespace std;

void PrintFrameText(int color, const char* text){
	SetColor(color);
	cout << text;
	SetColor(DARK_BLUE);
}

void ColorText(int color, const char* text){
	SetBGColor(color);
	SetColor(WHITE);
	printf("%-25s", text);
	SetColor(BLACK);
	SetBGColor(WHITE);
}

void DrawBorder(){
	int index = 0;
	HideTyping();
	GoToXY(0, 0);
	SetColor(DARK_BLUE);
	for(int i = 0; i < HEIGHT_BORDER; i++){
		if (i == 0){
			cout << " " << char(TOP_LEFT_CORNER);
			index = (WIDTH_FRAME_MENU - strlen(FrameTitle[0]) )/2;
			
			for(int j = 0; j < index; j++){
				cout << char(DOUBLE_HORIZONTAL_LINE);
			}
			
			PrintFrameText(GREEN, FrameTitle[0]);
			
			for(int j = WIDTH_FRAME_MENU-index; j < WIDTH_BORDER-1; j++){
				if(j == WIDTH_FRAME_MENU) cout << char(TOP_CENTER);
				else cout << char(DOUBLE_HORIZONTAL_LINE);
			}
			cout << char(TOP_RIGHT_CORNER) << endl;
		} else if(i == HEIGHT_BORDER - 1) {
			cout << " "<< char(BOTTOM_LEFT_CORNER);
			for(int j = 1; j < WIDTH_BORDER-1; j++) {
				if(j == WIDTH_FRAME_MENU) cout << char(BOTTOM_CENTER);
				else cout << char(DOUBLE_HORIZONTAL_LINE);
			}
			cout << char(BOTTOM_RIGHT_CORNER) << endl;
		} else if(i == HEIGHT_FRAME_MENU){
			cout << " " << char(LEFT_CENTER);
			
			index = (WIDTH_FRAME_MENU - strlen(FrameTitle[1]) )/2;
			for(int j = 0; j < index; j++){
				cout << char(DOUBLE_HORIZONTAL_LINE);
			}
			
			PrintFrameText(GREEN, FrameTitle[1]);
			
			for(int j = WIDTH_FRAME_MENU-index; j < WIDTH_FRAME_MENU; j++) {
				cout << char(DOUBLE_HORIZONTAL_LINE);
			}
			cout << char(RIGHT_CENTER);
			GoToXY(WIDTH_BORDER, i);
			cout << char(DOUBLE_VERTICAL_LINE) << endl;
			
		} else if(i == HEIGHT_FRAME_MAIN ){
			cout << " " << char(DOUBLE_VERTICAL_LINE);
			GoToXY(WIDTH_FRAME_MENU+1, i);
			cout << char(LEFT_CENTER);
			
			index = (WIDTH_BORDER - WIDTH_FRAME_MENU - strlen(FrameTitle[2]) )/2;
			for(int j = 0; j < index; j++){
				cout << char(DOUBLE_HORIZONTAL_LINE);
			}
			
			PrintFrameText(RED, FrameTitle[2]);
			
			for(int j = WIDTH_BORDER - WIDTH_FRAME_MENU-index; j < WIDTH_BORDER-WIDTH_FRAME_MENU-1; j++) {
				cout << char(DOUBLE_HORIZONTAL_LINE);
			}
			GoToXY(WIDTH_BORDER, i);
			cout << char(RIGHT_CENTER) << endl;
		}else {
			cout << " " << char(DOUBLE_VERTICAL_LINE);
			GoToXY(WIDTH_FRAME_MENU+1, i);
			cout << char(DOUBLE_VERTICAL_LINE);
			GoToXY(WIDTH_BORDER, i);
			cout << char(DOUBLE_VERTICAL_LINE) << endl;
		}
	}
	
}

void ShowHuongDan(){
	for (int i = 0; i < NUMBER_LINE_ITEM; i++){
		GoToXY(3, HEIGHT_FRAME_MENU+3+i);
		cout << MenuPhimTat[i];
	}
}

void ClearBorderSubMenu(){
	for (int i = 0; i < 30; i++){
		GoToXY(BUTTON_PADDING_LEFT+WIDTH_FRAME_MENU, i+4);
		printf("%-27s"," ");	
	}
}

int DrawSubMenu(int i, int select){
	int j = 0, 
		pointX = BUTTON_PADDING_LEFT+WIDTH_FRAME_MENU+1, 
		pointY = i*BUTTON_PADDING_LEFT+5;

	for(int k = 0; k < NUMBER_SUB_MENU_ITEM*2-1; k++){
		if(k%2 == 0){
			GoToXY(pointX, pointY+k);
			if(select-1 == j){
				ColorText(LIGHT_BLUE, SubMenuText[i][j++]);
			}else {
				SetColor(BLACK);
				printf("%-25s", SubMenuText[i][j++]);
			}
			GoToXY(pointX, pointY+1+k);
			if(k < 6) cout << "-------------------------";
		}
	}
	
	return 0;
}

void DrawBorderSubMenu(int i, int selectSubMenu = 0){
	ClearBorderSubMenu();
	int k = 0;
	
	int pointX = BUTTON_PADDING_LEFT+WIDTH_FRAME_MENU;
	int pointY = i*BUTTON_PADDING_LEFT+5;
	
	SetColor(BLACK);
	GoToXY(pointX, pointY-1);
	cout << char(TOP_LEFT_CORNER_SIMPLE);
    for (k=1; k < MENU_TEXT_LENGTH-5; k++)
        cout << char(HORIZONTAL_LINE);

    cout << char(TOP_RIGHT_CORNER_SIMPLE);
    
    int j = 0;
    for(k = 0; k < 7; k++){
	    GoToXY(pointX, pointY+k);
	    cout << char(VERTICAL_LINE);
	    GoToXY(WIDTH_FRAME_MENU+MENU_TEXT_LENGTH-2, pointY+k);
	    cout << char(VERTICAL_LINE);
	}
	
	GoToXY(pointX, pointY+k);
	cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
    for (k=1; k< MENU_TEXT_LENGTH-5; k++)
        cout << char(HORIZONTAL_LINE);
        
    cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
    DrawSubMenu(i, selectSubMenu);
}

void DrawButton(int i){
	int pointX = BUTTON_PADDING_LEFT;
	int pointY = i*BUTTON_PADDING_LEFT+4;
	
	SetColor(BLACK);
	GoToXY(pointX, pointY);
    cout << char(TOP_LEFT_CORNER_SIMPLE);
    for (int k=1; k < MENU_TEXT_LENGTH-5; k++)
        cout << char(HORIZONTAL_LINE);	
        
    cout << char(TOP_RIGHT_CORNER_SIMPLE);
    GoToXY(BUTTON_PADDING_LEFT, pointY+1);
    cout << char(VERTICAL_LINE);
    
    
    for(int k = 0; k < MENU_TEXT_LENGTH-6; k++)
        cout << char(SPACE);
    
    cout << char(VERTICAL_LINE);
    GoToXY(pointX, pointY+2);
    cout << char(BOTTOM_LEFT_CORNER_SIMPLE);
    
    for (int k=1; k< MENU_TEXT_LENGTH-5; k++)
        cout << char(HORIZONTAL_LINE);
        
    cout << char(BOTTOM_RIGHT_CORNER_SIMPLE);
    	
}

void PrintMenuText(int &select){
	int pointX = BUTTON_PADDING_LEFT+1, pointY = 0;
	for(int i = 0; i < NUMBER_MENU_ITEM; i++){
		pointY = i*BUTTON_PADDING_LEFT+5;
		GoToXY(pointX, pointY);
		if(i == select)
        	ColorText(LIGHT_BLUE, MenuText[i]);
	    else cout << MenuText[i];
	}
}

void DrawMenu(int &select){
	int pointX = BUTTON_PADDING_LEFT+1, pointY = 0;
	for(int i = 0; i < NUMBER_MENU_ITEM; i++){
		DrawButton(i);
		pointY = i*BUTTON_PADDING_LEFT+5;
		GoToXY(pointX, pointY);
	}
	PrintMenuText(select);
}

int SubMenu(int index){
	char action;
	int selectSubMenu = 0;
	DrawBorderSubMenu(index, selectSubMenu+1);
	do {
		SetColor(BLACK);
		DrawSubMenu(index, selectSubMenu+1);
	    action = getch();
	    if (action == 0) action = getch();
	    switch (action) {
		    case UP:
		        if (selectSubMenu + 1 > 1) {
		            selectSubMenu--; 
		        }
		        break;
		    case DOWN:
		        if (selectSubMenu + 1 < NUMBER_SUB_MENU_ITEM) {
		            selectSubMenu++;
		        }
		        break;
		    case ENTER:
		    	return selectSubMenu;
		    case ESC:
		    	selectSubMenu = -1;
		    	return selectSubMenu;
		    case LEFT:
		    	selectSubMenu = -1;
		    	return selectSubMenu;
	    }
	} while (1);
}

void ShowSubMenu(int &select){
	int selectSubMenu = 0;
	do {
	    selectSubMenu = SubMenu(select);
	    ClearBorderSubMenu();
	    switch (selectSubMenu) {
	    	case -1:
		    	return;
		    case 0:
		    	if(select == 2)
		    		PrintDataMonHoc(2, "NEW");
		        break;
		    case 1:
		    	if(select == 2)
		    		PrintDataMonHoc(2, "EDIT");
		        break;
		    case 2:
		        break;
		    case 3:
		    	if(select == 1){
		    		PrintDataLopHoc();
				}	
		    	else if(select == 2)
		    		PrintDataMonHoc(1, "DATA_TABLE");
		        break;
	    }
	} while (1);
}

int ShowMenu(){
	HideTyping();
	char action;
	int select = 0;
	DrawMenu(select);
	do {
		PrintMenuText(select);
	    action = getch();
	    if (action == 0) action = getch();
	    switch (action) {
		    case UP:
		        if (select + 1 > 1) {
		            select--; 
		        }
		        break;
		    case DOWN:
		        if (select + 1 < NUMBER_MENU_ITEM) {
		            select++;
		        }	
		        break;
		    case RIGHT:
		    	if(select < NUMBER_MENU_ITEM-1)
		    		ShowSubMenu(select);
		        break;
		    case ENTER:
		    	if(select < NUMBER_MENU_ITEM-1)
		    		ShowSubMenu(select);	
				else {
					system("cls");
					exit(0);
				}	
		        break;
	    }
	} while (1);
}
#endif
