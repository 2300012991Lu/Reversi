#include"myvarible.h"
using namespace std;

char help = 0;//帮助模式：0表示不帮助，1表示显示显示可以落子的全部位置，2表示显示机器推荐的位置
char AIhelpx = -1, AIhelpy = -1;
char inputx = -1, inputy = -1;//点击的棋盘位置
char lastx = 0, lasty = 0;
char inputbutton = 0;//点击的菜单按钮
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
void chessboard::draw(void) {//绘制棋盘
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
void chessboard::strongmove(char x, char y, char color) {//强制落子
	board[x][y] = color;
	game[round][0] = x;
	game[round][1] = y;
	game[round][2] = color + color;//双倍给下一个人()
	++round;
}
bool chessboard::isPossible(char x, char y, char color) {//是否可以落在(x,y)的位置
	if (x < 0 || x > 7 || y < 0 || y > 7) return 0;//落在棋盘外
	if (board[x][y]) return 0;//已有棋子
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
				if (flag) {//这个方向没有夹住
					flag = 0;
					continue;
				}
			}
		}
	}
	return 0;//这里不行
}
bool chessboard::canBePlaced(char color) {//能否落子
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
	if (isPossible(x, y, color)) {//可以落子
		board[x][y] = color;//在棋盘上落子
		game[round][0] = x;
		game[round][1] = y;
		game[round][2] = color;//记录棋谱
		++round;//棋盘上多了一颗子
		for (char d = 0; d < 8; d++) {
			char posx = x + dx[d], posy = y + dy[d];
			if (0 <= posx && posx < 8 && 0 <= posy && posy < 8) {
				if (board[posx][posy] == -color) {
					for (char k = 2; k < 8; ++k) {
						posx += dx[d], posy += dy[d];
						if (0 <= posx && posx < 8 && 0 <= posy && posy < 8) {
							if (board[posx][posy] == 0) break;
							else if (board[posx][posy] == color) {//把这个方向夹住的棋子翻转
								for (char l = 1; l < k; ++l) board[x + l * dx[d]][y + l * dy[d]] = color;
								break;
							}
						}
					}
				}
			}
		}
		if (canBePlaced(-color)) nextmove = -color;//正常情况下下一手更换另一方来下
		else if (!canBePlaced(color)) isFinished = 1;//若双方都不能下则结束
		//否则连续落子
		return;
	}
	//else cout << (int)x << " " << (int)y << " 那里不行\n";
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
			if (game[i][2] == nextmove || game[i][2] == nextmove + nextmove) {//追溯到上一步本方落子
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