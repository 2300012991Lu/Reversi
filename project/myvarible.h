#ifndef MY_VARIBLE_H
#define MY_VARIBLE_H 1234567

#include<iostream>
using namespace std;

const char dx[8] = { -1,-1, 0, 1, 1, 1, 0,-1 }, dy[8] = { 0 , 1, 1, 1, 0,-1,-1,-1 };//�˸�����char help = 0;//����ģʽ��0��ʾ��������1��ʾ��ʾ��ʾ�������ӵ�ȫ��λ�ã�2��ʾ��ʾ�����Ƽ���λ��
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

//Ȩ��
extern double weight[5][3];
extern double blackweight[5];
extern double whiteweight[5];
const double weight_1[5] = { 0.5,0,0.5,0,0 };
const double weight_2[5] = { 0.2,0.5,0.3,0,0 };
const double weight_3[5] = { 0.1,0.1,0.5,0.2,0.1 };

//IMAGE
string int_to_string(int);//������ת��Ϊ�ַ���
int string_to_int(string);//���ַ���ת��Ϊ����
void drawboard(void);//��������
void drawchess(char, char, char);//��������
void drawnext(char, char, char);//������һ��
void drawnumber(char, char, char, char);//�����������
void drawclick(char, char, char);//����������λ��
short buttonx(char);//��ťλ��
short buttony(char);//��ťλ��
void drawbutton(short, short, const char[], bool);//���ư�ť
void drawbutton(char, bool);//���ư�ť
void drawlast(char, char);//������һ������λ��
void input(void);//����
void outputsideinformation(void);//�Ծ���Ϣ

//GAME
void menuinput(void);//���˵�����
void mainmenu(void);//���˵�
char menulist(char);//�˵�ÿһ���м���ѡ��
void sidemenu(char);//�ɲ˵������Ҳ���Ϣ��

//AI
char getchess(void);//�Ӳ�
int getvalue(void);//��ֵ
char gettag(void);//��ǩ
char getrestrict(char);//��������
bool getoddeven(char);//��ż����
void outputAIinformation(void);//���AI����

double getAI(char);//��ȡ��Ȩ����
void bot(char);//�Զ����Ӻ���
void deep_bot(char, char);//�������

//��
struct menuposition {
	int x;//x����
	int y;//y����
	int len;//���
};
class chessboard {
public:
	char board[8][8] = {};//����
	bool isFinished = 0;//�Ƿ��Ѿ�����
	char nextmove = 1;//��һ������
	char round = 4;//��¼��������
	char game[160][3] = { {3,4,2},{3,3,-2},{4,3,2},{4,4,-2} };//��¼����

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

menuposition menubutton(char);//�˵���ť����


#endif