#include"myIMAGE.h"

char buttonstate[numofbutton] = {};
char opbutton = -1;

string int_to_string(int n) {

	if (n == 0)return"0";
	if (n < 0)return"-" + int_to_string(-n);
	string s = "";
	while (n > 0) {
		s = char(n % 10 + '0') + s;
		n /= 10;
	}
	return s;

}
int string_to_int(string s) {

	if (s[0] == '-') {
		string s0 = "";
		for (int i = 1; i < s.length(); ++i) {
			s0 = s0 + s[i];
		}
		return -string_to_int(s0);
	}
	int n = 0;
	for (int i = 0; i < s.length(); ++i) {
		n = n * 10;
		n = n + int(s[i] - '0');
	}
	return n;

}
void drawboard(void) {//绘制棋盘

	//棋盘背景
	setlinecolor(BK);
	setfillcolor(BK);
	fillrectangle(0, 0, TOTALWIDTH - 1, BOARDSIZE - 1);
	setfillcolor(BACKCOLOR);
	setlinecolor(BACKCOLOR);
	fillrectangle(0, 0, BOARDSIZE - 1, BOARDSIZE - 1);

	//棋盘网格
	setlinecolor(BLACK);
	char i;
	for (i = 1; i <= 9; ++i) {
		line(BOXSIZE - 1, BOXSIZE * i - 1, BOXSIZE * 9 - 1, BOXSIZE * i - 1);
		line(BOXSIZE * i - 1, BOXSIZE - 1, BOXSIZE * i - 1, BOXSIZE * 9 - 1);
	}

	//坐标
	settextstyle(BOXSIZE / 2, 0, "黑体");
	settextcolor(RGB(50, 50, 50));
	for (char i = 1; i <= 8; ++i) {
		char texttemp[100] = {};
		string s = int_to_string(i - 1);

		for (int c = 0; c < s.length(); ++c) {
			texttemp[c] = s[c];
		}
		int t = i * BOXSIZE + BOXSIZE / 2 - textwidth(texttemp) / 2 - 1;
		int l = BOXSIZE / 2;
		outtextxy(t, l, texttemp);
		outtextxy(l, t, texttemp);
	}

	//按钮
	for (int i = 0; i < numofbutton; ++i) {
		drawbutton(i, 0);
	}
}
void drawchess(char x, char y, char color) {//在第x行第y列绘制颜色为color的棋子
	if (x < 0 || x>7 || y < 0 || y>7)return;
	//设置颜色
	COLORREF LINE, OUTER, MIDDLE1, MIDDLE2, MIDDLE3, INNER;
	if (color == -1) {//-1为白棋
		LINE = RGB(50, 50, 50);//轮廓为黑色
		//颜色渐变
		OUTER = RGB(230, 230, 230);
		MIDDLE1 = RGB(225, 225, 225);
		MIDDLE2 = RGB(220, 220, 220);
		MIDDLE3 = RGB(215, 215, 215);
		INNER = RGB(210, 210, 210);
	}
	else if (color == 1) {//1为黑棋
		LINE = RGB(230, 230, 230);//轮廓为白色
		//颜色渐变
		OUTER = RGB(50, 50, 50);
		MIDDLE1 = RGB(55, 55, 55);
		MIDDLE2 = RGB(60, 60, 60);
		MIDDLE3 = RGB(65, 65, 65);
		INNER = RGB(70, 70, 70);
	}
	else {
		LINE = OUTER = MIDDLE1 = MIDDLE2 = MIDDLE3 = INNER = BACKCOLOR;
	}
	//绘制棋子
	int posx = BOXSIZE * (x + 1) + BOXSIZE / 2, posy = BOXSIZE * (y + 1) + BOXSIZE / 2;
	setfillcolor(OUTER);
	setlinecolor(LINE);
	fillcircle(posx, posy, BOXSIZE * 0.45);
	circle(posx, posy, BOXSIZE * 0.45);
	setfillcolor(MIDDLE1);
	setlinecolor(MIDDLE1);
	fillcircle(posx, posy, BOXSIZE * 0.4);
	circle(posx, posy, BOXSIZE * 0.4);
	setfillcolor(MIDDLE2);
	setlinecolor(MIDDLE2);
	fillcircle(posx, posy, BOXSIZE * 0.35);
	circle(posx, posy, BOXSIZE * 0.35);
	setfillcolor(MIDDLE3);
	setlinecolor(MIDDLE3);
	fillcircle(posx, posy, BOXSIZE * 0.3);
	circle(posx, posy, BOXSIZE * 0.3);
	setfillcolor(INNER);
	setlinecolor(INNER);
	fillcircle(posx, posy, BOXSIZE * 0.25);
	circle(posx, posy, BOXSIZE * 0.25);
}
void drawnext(char x, char y, char color) {
	if (0 <= x && x <= 7 && 0 <= y && y <= 7) {
		COLORREF FILL;
		if (color == -1) FILL = RGB(230, 230, 230);//-1为白棋
		else if (color == 1) FILL = RGB(50, 50, 50);//1为黑棋
		else if (color == 2) FILL = GREEN;//AI推荐
		else FILL = BACKCOLOR;
		//绘制棋子
		int posx = BOXSIZE * (x + 1) + BOXSIZE / 2, posy = BOXSIZE * (y + 1) + BOXSIZE / 2;
		setfillcolor(FILL);
		setlinecolor(FILL);
		fillcircle(posx, posy, BOXSIZE / 10);
	}
}
void drawnumber(char x, char y, char num, char color) {//在第x行第y列绘制颜色为color的棋子的序号
	if (num == 0 || color == 0)return;
	COLORREF TEXTCOLOR;
	if (color == -1) {//-1为白棋，写黑字
		TEXTCOLOR = RGB(50, 50, 50);
	}
	else if (color == 1) {//1为黑棋，写白字
		TEXTCOLOR = RGB(230, 230, 230);
	}
	else {
		TEXTCOLOR = BACKCOLOR;
	}

	char texttemp[100] = {};
	string s = int_to_string(num);

	for (int c = 0; c < s.length(); ++c) {
		texttemp[c] = s[c];
	}
	settextstyle(BOXSIZE / 2, 0, "黑体");
	settextcolor(TEXTCOLOR);
	int ti = x * BOXSIZE - textwidth(texttemp) / 2 - 1;
	int tj = y * BOXSIZE - textheight(texttemp) / 2 - 1;
	outtextxy(ti, tj, texttemp);
}
short buttonx(char num) {
	return BOARDSIZE + BUTTONWIDTH / 4 + BUTTONWIDTH * 6 / 5 * (num % 3);
}
short buttony(char num) {
	return BUTTONHEIGHT / 4 + BUTTONHEIGHT * 6 / 5 * (num / 3);
}
void drawbutton(short x, short y, const char c[], bool isclick) {
	setfillcolor(RGB(230, 230, 230));
	if (isclick) {
		setlinecolor(GREEN);
	}
	else {
		setlinecolor(BLACK);
	}
	fillrectangle(x, y, x + BUTTONWIDTH, y + BUTTONHEIGHT);
	settextcolor(BLACK);
	settextstyle(BUTTONHEIGHT / 2, 0, "黑体");
	int t = x + BUTTONWIDTH / 2 - textwidth(c) / 2;
	int l = y + BUTTONHEIGHT / 2 - textheight(c) / 2;
	outtextxy(t, l, c);
}
void drawbutton(char num, bool isclick) {
	drawbutton(buttonx(num), buttony(num), buttontext[num], isclick);
}
void drawclick(char x, char y, char color) {
	int posx = (x + 1) * BOXSIZE, posy = (y + 1) * BOXSIZE;
	COLORREF lcolor;
	if (color == 1) {//黑棋
		lcolor = RGB(50, 50, 50);
	}
	else if (color == -1) {//白棋
		lcolor = RGB(230, 230, 230);
	}
	else {//恢复
		lcolor = BACKCOLOR;
	}
	setlinecolor(lcolor);
	rectangle(posx + 3, posy + 3, posx + BOXSIZE - 5, posy + BOXSIZE - 5);
}
void drawlast(char x, char y) {
	if (x < 0 || x>7 || y < 0 || y>7)return;
	int posx = BOXSIZE * (x + 1) + BOXSIZE / 2, posy = BOXSIZE * (y + 1) + BOXSIZE / 2;
	setfillcolor(RED);
	fillcircle(posx, posy, BOXSIZE / 10);
}
void input(void) {
	ExMessage msg;
	char clickx = 0, clicky = 0;
	char px = 0, py = 0, pb = -1;
	inputx = inputy = -1;
	while (!clickx && !clicky) {
		bool flag = 0;
		if (peekmessage(&msg)) {
			if (msg.x >= 0 && msg.x < BOARDSIZE && msg.y >= 0 && msg.y < BOARDSIZE) {
				if (pb != -1) {
					drawbutton(pb, 0);
					pb = -1;
				}
				for (char i = 0; i < 8; ++i) {
					for (char j = 0; j < 8; ++j) {
						if (msg.x >= BOXSIZE * (i + 1) + 2 && msg.x < BOXSIZE * (i + 2) - 3) {
							if (msg.y >= BOXSIZE * (j + 1) + 2 && msg.y < BOXSIZE * (j + 2) - 3) {
								if (px != i || py != j) {
									if (mainboard.board[px][py] == 0) {
										drawclick(px, py, 0);
									}
									px = i; py = j;
								}
								if (mainboard.board[i][j] == 0) {
									drawclick(i, j, mainboard.nextmove);
								}
								if (msg.message == WM_LBUTTONDOWN) {
									inputx = px; inputy = py;
									px = py = 0;
									if (mainboard.board[i][j] == 0) {
										drawclick(i, j, 0);
									}
									return;
								}
								else if (msg.message == WM_RBUTTONDOWN && gamemode == 6) {
									useRB = 1;
									inputx = px; inputy = py;
									px = py = 0;
									if (mainboard.board[i][j] == 0) {
										drawclick(i, j, 0);
									}
									return;
								}
								flag = 1;
								break;
							}
						}
					}
					if (flag)break;
				}
			}
			else if (msg.x >= BOARDSIZE && msg.x < TOTALWIDTH && msg.y >= 0 && msg.y < BOARDSIZE) {
				if (mainboard.board[px][py] == 0) {
					drawclick(px, py, 0);
				}
				px = 0; py = 0;
				for (int i = 0; i < numofbutton; ++i) {
					if (msg.x >= buttonx(i) && msg.x < buttonx(i) + BUTTONWIDTH && msg.y >= buttony(i) && msg.y < buttony(i) + BUTTONHEIGHT) {
						if (pb != i) {
							if (i != 4) {
								if (!buttonstate[i]) {
									drawbutton(i, 0);
								}
							}
							else {
								if (mainboard.nextmove == 1 && (buttonstate[4] != 1 && buttonstate[4] != 3)) {
									drawbutton(i, 0);
								}
								else if (mainboard.nextmove == -1 && (buttonstate[4] != 2 && buttonstate[4] != 3)) {
									drawbutton(i, 0);
								}
							}
							pb = i;
						}
						if (msg.message == WM_LBUTTONDOWN) {
							//左键：若按钮未按下，则闪一次，按钮被标记点击一次；若已按下，则取消按下状态，不点击
							if (buttonstate[i]) {
								if (i == 4) {
									if (mainboard.nextmove == 1) {
										useBlackAI = 0;
									}
									else if (mainboard.nextmove == -1) {
										useWhiteAI = 0;
									}
									AIhelpx = -1;
									AIhelpy = -1;
								}
								drawbutton(i, 0);
								buttonstate[i] = 0;
								Sleep(100);
								pb = 1;
								return;
							}
							opbutton = i;
							drawbutton(i, 1);
							Sleep(100);
							pb = -1;
							return;
						}
						else if (msg.message == WM_RBUTTONDOWN) {
							//右键：将按钮标记为按下状态
							opbutton = i;
							if (i != 4) {//使用AI
								buttonstate[i] = 1;
							}
							else {
								if (!mainboard.isFinished) {
									if (mainboard.nextmove == 1) {
										useBlackAI = 1;
										if (buttonstate[4] == 0) {
											buttonstate[4] = 1;
										}
										else if (buttonstate[4] == 2) {
											buttonstate[4] = 3;
										}
									}
									else if (mainboard.nextmove == -1) {
										useWhiteAI = 1;
										if (buttonstate[4] == 0) {
											buttonstate[4] = 2;
										}
										else if (buttonstate[4] == 1) {
											buttonstate[4] = 3;
										}
									}
								}
							}
							drawbutton(i, 1);
							Sleep(100);
							return;
						}
						break;
					}
				}
			}
		}
	}
}
void outputAIinformation(void) {
	black_chess = getchess();
	black_score = getvalue();
	black_tag = gettag();
	next_variety = getrestrict(1);
	next_oddeven = getoddeven(1);
	int information[5] = { black_chess,black_score,black_tag,next_variety,next_oddeven };
	char ifm[5][100] = {};
	setlinecolor(BK);
	setfillcolor(BK);
	fillrectangle(900, 400, 1300, 600);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(20, 0, "黑体");
	for (int i = 0; i < 6; ++i) {
		line(900, 400 + i * 30, 1300, 400 + i * 30);
	}
	line(900, 400, 900, 550);
	line(1100, 400, 1100, 550);
	line(1300, 400, 1300, 550);
	const char content[5][100] = { "数量（黑-白）","评分（黑）","标签（黑）","落子位置数量","奇偶控制" };
	for (int i = 0; i < 5; ++i) {
		outtextxy(920, 405 + i * 30, content[i]);
		string temp = int_to_string(information[i]);
		int len = temp.length();
		for (int j = 0; j < len; ++j) {
			ifm[i][j] = temp[j];
		}
		outtextxy(1120, 405 + i * 30, ifm[i]);
	}
	char AItree[100] = {};
	for (int i = 0; i < 4; ++i) {
		if (i < AIdepth && chess_tree[i][0] != -1) {
			AItree[i * 6 + 0] = '(';
			AItree[i * 6 + 1] = chess_tree[i][0] + '0';
			AItree[i * 6 + 2] = ',';
			AItree[i * 6 + 3] = chess_tree[i][1] + '0';
			AItree[i * 6 + 4] = ')';
			AItree[i * 6 + 5] = ' ';
		}
		else {
			AItree[i * 6 + 0] = '(';
			AItree[i * 6 + 1] = 'x';
			AItree[i * 6 + 2] = ',';
			AItree[i * 6 + 3] = 'x';
			AItree[i * 6 + 4] = ')';
			AItree[i * 6 + 5] = ' ';
		}
	}
	outtextxy(900, 560, AItree);
	for (int i = 0; i < 4; ++i) {
		chess_tree[i][0] = chess_tree[i][1] = -1;
	}
}
void outputsideinformation(void) {
	setlinecolor(BK);
	setfillcolor(BK);
	fillrectangle(900, 300, 1300, 390);
	const char renlei[100] = "（人类）", jiqi[100] = "（机器）";
	char bp[100] = {}, wp[100] = {};
	if (gamemode == 2) {
		strcat_s(bp, renlei);
		strcat_s(wp, jiqi);
	}
	else if (gamemode == 3) {
		strcat_s(bp, jiqi);
		strcat_s(wp, renlei);
	}
	else if (gamemode == 5) {
		strcat_s(bp, jiqi);
		strcat_s(wp, jiqi);
	}
	else if (gamemode == 6) {
		strcat_s(bp, renlei);
		strcat_s(wp, renlei);
	}
	settextstyle(30, 0, "宋体");
	settextcolor(BLACK);
	outtextxy(900, 300, "黑棋");
	outtextxy(960, 300, bp);
	{
		string s = int_to_string(mainboard.count(1));
		char c[100] = {};
		for (int i = 0; i < s.length(); ++i) {
			c[i] = s[i];
		}
		outtextxy(1110, 300, c);
	}
	settextcolor(WHITE);
	outtextxy(900, 330, "白棋");
	outtextxy(960, 330, wp);
	{
		string s = int_to_string(mainboard.count(-1));
		char c[100] = {};
		for (int i = 0; i < s.length(); ++i) {
			c[i] = s[i];
		}
		outtextxy(1110, 330, c);
	}
	if (mainboard.isFinished) {
		settextcolor(BLACK);
		char win = 0;
		if (mainboard.count(0) > 0) win = 1;
		else if (mainboard.count(0) < 0)win = -1;
		if (win) {
			outtextxy(900, 360, "获胜方：");
			outtextxy(1020, 360, (win == 1 ? "黑棋" : "白棋"));
			if (gamemode == 2) outtextxy(1080, 360, (win == 1 ? renlei : jiqi));
			if (gamemode == 3) outtextxy(1080, 360, (win == 1 ? jiqi : renlei));
		}
		else {
			outtextxy(900, 360, "平局");
		}
	}
}