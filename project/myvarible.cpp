#include"myvarible.h"
using namespace std;

char help = 0;//����ģʽ��0��ʾ��������1��ʾ��ʾ��ʾ�������ӵ�ȫ��λ�ã�2��ʾ��ʾ�����Ƽ���λ��
char AIhelpx = -1, AIhelpy = -1;
char inputx = -1, inputy = -1;//���������λ��
char lastx = 0, lasty = 0;
char inputbutton = 0;//����Ĳ˵���ť
char gamemode = 0;
char AIstrength = 0;
char AIdepth = 5;
bool useBlackAI = 0;
bool useWhiteAI = 0;
bool useRB = 0;
char black_chess = 0, black_score = 0, black_tag = 0;
char next_variety = 0, next_oddeven = 0;
char chess_tree[4][2] = {};

double weight[5][3] = {};
double blackweight[5] = { 0.1,0.1,0.5,0.2,0.1 };
double whiteweight[5] = { 0.1,0.1,0.5,0.2,0.1 };

chessboard mainboard = {};
chessboard AIboard = {};

void chessboard::prepare(bool getempty) {
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			board[i][j] = 0;
		}
	}
	round = 0;
	if (!getempty) {
		board[3][4] = board[4][3] = 1;
		board[3][3] = board[4][4] = -1;
		round = 4;
	}
	nextmove = 1;
	isFinished = 0;
}
char chessboard::count(char color) {
	char counter = 0;
	if (color) {
		for (char i = 0; i < 8; ++i) {
			for (char j = 0; j < 8; ++j) {
				if (board[i][j] == color)++counter;
			}
		}
		return counter;
	}
	return count(1) - count(-1);
}
void chessboard::draw(void) {//��������
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			drawchess(i, j, board[i][j]);
		}
	}
}
void chessboard::drawtips(void) {
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			if (isPossible(i, j, nextmove)) {
				drawnext(i, j, nextmove);
				if (i == AIhelpx && j == AIhelpy) drawnext(i, j, 2);
			}
		}
	}
}
void chessboard::strongmove(char x, char y, char color) {//ǿ������
	board[x][y] = color;
	game[round][0] = x;
	game[round][1] = y;
	game[round][2] = color + color;//˫������һ����()
	++round;
}
bool chessboard::isPossible(char x, char y, char color) {//�Ƿ��������(x,y)��λ��
	if (x < 0 || x > 7 || y < 0 || y > 7) return 0;//����������
	if (board[x][y]) return 0;//��������
	bool flag = 0;
	for (char d = 0; d < 8; d++) {
		char posx = x + dx[d], posy = y + dy[d];
		if (0 <= posx && posx < 8 && 0 <= posy && posy < 8) {
			if (board[posx][posy] == -color) {
				for (char k = 2; k < 8; ++k) {
					posx += dx[d], posy += dy[d];
					if (0 <= posx && posx < 8 && 0 <= posy && posy < 8) {
						if (board[posx][posy] == 0) {
							flag = 1;
							break;
						}
						else if (board[posx][posy] == color) {
							return 1;
						}
					}
				}
				if (flag) {//�������û�м�ס
					flag = 0;
					continue;
				}
			}
		}
	}
	return 0;//���ﲻ��
}
bool chessboard::canBePlaced(char color) {//�ܷ�����
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			if (isPossible(i, j, color)) {
				return 1;
			}
		}
	}
	return 0;
}
void chessboard::move(char x, char y) {
	move(x, y, nextmove);
}
void chessboard::move(char x, char y, char color) {
	if (color == 2 || color == -2) {
		strongmove(x, y, color / 2);
		return;
	}
	if (isPossible(x, y, color)) {//��������
		board[x][y] = color;//������������
		game[round][0] = x;
		game[round][1] = y;
		game[round][2] = color;//��¼����
		++round;//�����϶���һ����
		for (char d = 0; d < 8; d++) {
			char posx = x + dx[d], posy = y + dy[d];
			if (0 <= posx && posx < 8 && 0 <= posy && posy < 8) {
				if (board[posx][posy] == -color) {
					for (char k = 2; k < 8; ++k) {
						posx += dx[d], posy += dy[d];
						if (0 <= posx && posx < 8 && 0 <= posy && posy < 8) {
							if (board[posx][posy] == 0) break;
							else if (board[posx][posy] == color) {//����������ס�����ӷ�ת
								for (char l = 1; l < k; ++l) board[x + l * dx[d]][y + l * dy[d]] = color;
								break;
							}
						}
					}
				}
			}
		}
		if (canBePlaced(-color)) nextmove = -color;//�����������һ�ָ�����һ������
		else if (!canBePlaced(color)) isFinished = 1;//��˫���������������
		//������������
		return;
	}
	//else cout << (int)x << " " << (int)y << " ���ﲻ��\n";
}
void chessboard::rerun(void) {
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			board[i][j] = 0;
		}
	}
	if (isFinished) {
		nextmove = -nextmove;
	}
	if (round >= 6) {
		for (char i = round - 1; i > 4; --i) {
			if (game[i][2] == nextmove || game[i][2] == nextmove + nextmove) {//׷�ݵ���һ����������
				round = 0;
				isFinished = 0;
				for (char j = 0; j < i; ++j) {
					move(game[j][0], game[j][1], game[j][2]);
				}
				return;
			}
		}
	}
	prepare(0);
}