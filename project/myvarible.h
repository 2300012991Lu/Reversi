#ifndef MY_VARIBLE_H
#define MY_VARIBLE_H 1234567

#include<iostream>
using namespace std;

const char dx[8] = { -1,-1, 0, 1, 1, 1, 0,-1 }, dy[8] = { 0 , 1, 1, 1, 0,-1,-1,-1 };//八个方向char help = 0;//帮助模式：0表示不帮助，1表示显示显示可以落子的全部位置，2表示显示机器推荐的位置
extern char help;
extern char AIhelpx, AIhelpy;
extern char inputx, inputy;
extern char lastx, lasty;
extern char inputbutton;
extern char gamemode;
extern char AIstrength;
extern char AIdepth;
extern bool useBlackAI;
extern bool useWhiteAI;
extern bool useRB;
extern char black_chess, black_score, black_tag;
extern char next_variety, next_oddeven;
extern char chess_tree[4][2];

//权重
extern double weight[5][3];
extern double blackweight[5];
extern double whiteweight[5];
const double weight_1[5] = { 0.5,0,0.5,0,0 };
const double weight_2[5] = { 0.2,0.5,0.3,0,0 };
const double weight_3[5] = { 0.1,0.1,0.5,0.2,0.1 };

//IMAGE
string int_to_string(int);//将整数转化为字符串
int string_to_int(string);//将字符串转化为整数
void drawboard(void);//绘制棋盘
void drawchess(char, char, char);//绘制棋子
void drawnext(char, char, char);//绘制下一步
void drawnumber(char, char, char, char);//绘制棋子序号
void drawclick(char, char, char);//绘制鼠标放置位置
short buttonx(char);//按钮位置
short buttony(char);//按钮位置
void drawbutton(short, short, const char[], bool);//绘制按钮
void drawbutton(char, bool);//绘制按钮
void drawlast(char, char);//绘制上一步落子位置
void input(void);//输入
void outputsideinformation(void);//对局信息

//GAME
void menuinput(void);//主菜单输入
void mainmenu(void);//主菜单
char menulist(char);//菜单每一行有几个选项
void sidemenu(char);//由菜单跳出右侧信息栏

//AI
char getchess(void);//子差
int getvalue(void);//估值
char gettag(void);//标签
char getrestrict(char);//限制落子
bool getoddeven(char);//奇偶分析
void outputAIinformation(void);//输出AI数据

double getAI(char);//获取加权评分
void bot(char);//自动落子函数
void deep_bot(char, char);//深度搜索

//类
struct menuposition {
	int x;//x坐标
	int y;//y坐标
	int len;//宽度
};
class chessboard {
public:
	char board[8][8] = {};//棋盘
	bool isFinished = 0;//是否已经结束
	char nextmove = 1;//下一步落子
	char round = 4;//记录棋子数量
	char game[160][3] = { {3,4,2},{3,3,-2},{4,3,2},{4,4,-2} };//记录落子

	void prepare(bool);
	char count(char);
	void draw(void);
	void drawtips(void);
	void strongmove(char, char, char);
	bool isPossible(char, char, char);
	bool canBePlaced(char);
	void move(char, char);
	void move(char, char, char);
	void rerun(void);
};
extern chessboard mainboard, AIboard;

menuposition menubutton(char);//菜单按钮坐标


#endif