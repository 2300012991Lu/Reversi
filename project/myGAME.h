#ifndef MY_GAME_H
#define MY_GAME_H 0

#include<fstream>
#include<conio.h>
#include"myvarible.h"
#include"easyx.h"
#define BOARDSIZE 800// = BOXSIZE * 10
#define TOTALWIDTH 1400// = BOARDSIZE + BUTTONWIDTH * 4
#define BACKCOLOR RGB(200,180,100)
#define BK RGB(160, 160, 160)
#define MENUCOLOR RGB(220,220,240)
#define SELECTCOLOR RGB(40,200,40)
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

void menuinput(void);
menuposition menubutton(char);
char menulist(char);
void mainmenu(void);
void sidemenu(char);

#endif