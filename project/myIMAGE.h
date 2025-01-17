#ifndef MY_IMAGE_H
#define MY_IMAGE_H 0

#include"myvarible.h"
#include"easyx.h"
#define BACKCOLOR RGB(200,180,100)
#define BK RGB(160, 160, 160)
#define BUTTONWIDTH 150
#define BUTTONHEIGHT 60
#define BOXSIZE 80
#define BOARDSIZE 800// = BOXSIZE * 10
#define TOTALWIDTH 1400// = BOARDSIZE + BUTTONWIDTH * 4
using namespace std;

const char numofbutton = 6;//按钮数量
const char buttontext[numofbutton][100] = { "菜单","提示","AI信息","悔棋","用AI代替","退出" };
extern char buttonstate[numofbutton];
extern char opbutton;

string int_to_string(int);
int string_to_int(string);
void drawboard(void);
void drawchess(char, char, char);
void drawnext(char, char, char);
void drawnumber(char, char, char, char);
short buttonx(char);
short buttony(char);
void drawbutton(short, short, const char[], bool);
void drawbutton(char, bool);
void drawclick(char, char, char);
void drawlast(char, char);
void input(void);
void outputAIinformation(void);
void outputsideinformation(void);

#endif