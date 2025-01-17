#include"myGAME.h"

void menuinput(void) {
	ExMessage msg;
	char pc[8] = {};
	inputbutton = 0;
	while (!inputbutton) {
		bool flag = 0;
		if (peekmessage(&msg)) {
			for (int i = 1; i <= 7; ++i) {
				if (i < 3) {
					if (msg.message == WM_LBUTTONDOWN) {
						for (int j = menulist(i - 1) + 1; j <= menulist(i); ++j) {
							menuposition temp = menubutton(j);
							if (msg.x > temp.x && msg.x < temp.x + temp.len && msg.y > temp.y && msg.y < temp.y + 30) {
								menuposition t;
								if (pc[i] != j) {//删除上一个选中的状态
									setlinecolor(BLACK);
									t = menubutton(pc[i]);
									rectangle(t.x, t.y, t.x + t.len, t.y + 30);
									if (i == 1) {
										t = menubutton(1);
										rectangle(t.x, t.y, t.x + t.len, t.y + 30);
										t = menubutton(4);
										rectangle(t.x, t.y, t.x + t.len, t.y + 30);
									}
								}
								//选中当前按钮
								pc[i] = j;
								setlinecolor(SELECTCOLOR);
								rectangle(temp.x, temp.y, temp.x + temp.len, temp.y + 30);
								if (i == 1) {
									if (j <= 4) {
										t = menubutton((j == 1 ? 4 : 1));
										rectangle(t.x, t.y, t.x + t.len, t.y + 30);
									}
								}
								if (i == 1)gamemode = j;
								else if (i == 2)AIstrength = j;
							}
						}
					}
				}
				else if (i == 3) {//条形按钮，需要重新绘制整个滑动条
					if (msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) {
						menuposition temp = menubutton(menulist(i));
						if (msg.x > temp.x - 10 && msg.x < temp.x + 10 + temp.len && msg.y > temp.y + 8 && msg.y < temp.y + 22) {
							setlinecolor(MENUCOLOR);
							setfillcolor(MENUCOLOR);
							rectangle(temp.x - 15, temp.y, temp.x + temp.len + 40, temp.y + 15);
							fillrectangle(temp.x - 15, temp.y, temp.x + temp.len + 40, temp.y + 30);
							setfillcolor(RGB(230, 230, 230));
							setlinecolor(BLACK);
							fillrectangle(temp.x, temp.y + 12, temp.x + temp.len, temp.y + 18);
							rectangle(temp.x, temp.y + 12, temp.x + temp.len, temp.y + 18);
							int dist_L = msg.x - temp.x + 15;
							AIdepth = dist_L / 30 + 1;
							dist_L = (AIdepth - 1) * 30;
							int posx = temp.x + dist_L, posy = temp.y + 15;
							setfillcolor(RED);
							circle(posx, posy, 5);
							fillcircle(posx, posy, 5);
							settextcolor(BLACK);
							settextstyle(20, 0, "宋体");
							char c[100] = {};
							string s = int_to_string(AIdepth);
							int len = s.length();
							for (int j = 0; j < len; ++j) {
								c[j] = s[j];
							}
							outtextxy(temp.x + temp.len + 20, temp.y + 5, c);
						}
					}
				}
				else if (i < 7) {
					for (int j = menulist(i - 1) + 1; j <= menulist(i); ++j) {
						menuposition temp = menubutton(j);
						if (msg.x > temp.x && msg.x < temp.x + temp.len && msg.y > temp.y && msg.y < temp.y + 30) {
							if (msg.message == WM_LBUTTONDOWN) {
								//选中当前按钮，闪烁一次，在右侧跳出信息栏
								inputbutton = j;
								setlinecolor(SELECTCOLOR);
								rectangle(temp.x, temp.y, temp.x + temp.len, temp.y + 30);
								Sleep(200);
								setlinecolor(BLACK);
								rectangle(temp.x, temp.y, temp.x + temp.len, temp.y + 30);
								sidemenu(j);
								return;
							}
						}
					}
				}
				else if (i == 7) {
					for (int j = menulist(i - 1) + 1; j <= menulist(i); ++j) {
						menuposition temp = menubutton(j);
						if (msg.x > temp.x && msg.x < temp.x + temp.len && msg.y > temp.y && msg.y < temp.y + 30) {
							if (msg.message == WM_LBUTTONDOWN) {
								inputbutton = j;
							}
						}
					}
				}
			}
		}
	}
}
menuposition menubutton(char num) {
	switch (num) {
	case 1:return { 80, 100, 60 };//60
	case 2:return { 260, 100, 30 };//30
	case 3:return { 290,100,30 };//30
	case 4:return { 320,100,60 };//60
	case 5:return { 410, 100,120 };//120
	case 6:return { 560,100,120 };//120
	case 7:return { 200,150,60 };//60
	case 8:return { 290,150,60 };//60
	case 9:return { 380,150,60 };//60
	case 10:return { 230,200,270 };//270，条形输入，10挡
	case 11:return { 170,300,60 };//60
	case 12:return { 260,300,150 };//150
	case 13:return { 170,350,90 };//90
	case 14:return { 290,350,60 };//60
	case 15:return { 380,350,90 };//90
	case 16:return { 500,350,120 };//120
	case 17:return { 650,350,120 };//120
	case 18:return { 170,450,60 };//60
	case 19:return { 260,450,120 };//120
	case 20:return { 410,450,90 };//90
	case 21:return { 530,450,60 };//60
	case 22:return { 280,700,60 };//60
	case 23:return { 370,700,60 };//60
	case 24:return { 460,700,60 };//60
	}
	return { 0,0,0 };
}
char menulist(char num) {
	switch (num) {
	case 0:return 0;
	case 1:return 6;
	case 2:return 9;
	case 3:return 10;
	case 4:return 12;
	case 5:return 17;
	case 6:return 21;
	case 7:return 24;
	}
	return 0;
}
void mainmenu(void) {
	setfillcolor(MENUCOLOR);
	setlinecolor(MENUCOLOR);
	fillrectangle(0, 0, 799, 799);
	setfillcolor(RGB(230, 230, 230));
	setlinecolor(BLACK);
	for (char i = 1; i <= 24; ++i) {
		menuposition temp = menubutton(i);
		rectangle(temp.x, temp.y + (i == 10 ? 12 : 0), temp.x + temp.len, temp.y + (i == 10 ? 18 : 30));
		fillrectangle(temp.x, temp.y + (i == 10 ? 12 : 0), temp.x + temp.len, temp.y + (i == 10 ? 18 : 30));
	}
	menuposition temp = menubutton(10);
	setfillcolor(RED);
	circle(temp.x + 120, temp.y + 15, 5);
	fillcircle(temp.x + 120, temp.y + 15, 5);
	settextcolor(BLACK);
	settextstyle(20, 0, "宋体");
	outtextxy(temp.x + temp.len + 20, temp.y + 5, "5");
	settextstyle(30, 0, "宋体");
	outtextxy(80, 70, "对局模式：");
	outtextxy(80, 100, "人机：玩家执黑白随机  机器对决  双人对决");//1-6
	outtextxy(80, 150, "AI设置：初级  中级  高级");//7-9
	outtextxy(80, 200, "搜索深度：");//10
	outtextxy(80, 300, "保存：暂存  保存为棋谱");//11-12
	outtextxy(80, 350, "打开：旧对局  复盘  空棋盘  初始棋盘  使用暂存");//13-17
	outtextxy(80, 450, "帮助：规则  使用教程  AI说明  其他");//18-21
	outtextxy(280, 700, "取消  确认  退出");//22-24
	return;
}
void sidemenu(char num) {
	setlinecolor(BK);
	setfillcolor(BK);
	fillrectangle(BOARDSIZE - 1, 0, TOTALWIDTH - 1, BOARDSIZE - 1);
	if (num == 11) {//存档
		remove("quickstart");
		fstream f;
		f.open("quickstart", ios::out | ios::app);
		f << (int)mainboard.isFinished << ' ' << (int)mainboard.nextmove << ' ' << (int)mainboard.round;
		f << ' ' << (int)gamemode << ' ' << (int)AIstrength << ' ' << (int)AIdepth << '\n';
		for (int i = 0; i < mainboard.round; ++i) {
			for (int j = 0; j < 3; ++j) {
				f << (int)mainboard.game[i][j] << ' ';
			}
			f << '\n';
		}
		f << '\n';
		f.close();
	}
	else if (num == 12) {//输入文件名并存档，只输入回车会使用整值时间命名
		settextstyle(20, 0, "宋体");
		settextcolor(BLACK);
		outtextxy(850, 50, "输入文件名：");
		setlinecolor(BLACK);
		fillrectangle(850, 80, 1150, 110);
		fstream f;
		char counter = 0;
		char c = 0;
		char name[100] = {};
		bool useC = 0;
		while (1) {
			if (KEY_DOWN(0x14)) {//大写锁定
				useC = !useC;
			}
			for (c = 'A'; c <= 'Z'; ++c) {//字母
				if (KEY_DOWN(c)) {
					if (useC) name[counter] = c;//大写字母
					else name[counter] = c - 'A' + 'a';//小写字母
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			for (c = '0'; c <= '9'; ++c) {//数字
				if (KEY_DOWN(c)) {
					name[counter] = c;
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			if (KEY_DOWN(0x0D)) {//回车键
				break;
			}
			if (KEY_DOWN(0x08)) {//退格键
				if (counter > 0) {
					--counter;
					name[counter] = 0;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			Sleep(60);
		}
		if (name[0]) {
			remove(name);
			f.open(name, ios::out | ios::app);
		}
		else f.open(int_to_string((unsigned)time(0)), ios::out | ios::app);
		f << (int)mainboard.isFinished << ' ' << (int)mainboard.nextmove << ' ' << (int)mainboard.round;
		f << ' ' << (int)gamemode << ' ' << (int)AIstrength << ' ' << (int)AIdepth << '\n';
		for (int i = 0; i < mainboard.round; ++i) {
			for (int j = 0; j < 3; ++j) {
				f << (int)mainboard.game[i][j] << ' ';
			}
			f << '\n';
		}
		f << '\n';
		f.close();
	}
	else if (num == 13) {//旧对局，输入文件名
		settextstyle(20, 0, "宋体");
		settextcolor(BLACK);
		outtextxy(850, 50, "输入文件名：");
		setlinecolor(BLACK);
		fillrectangle(850, 80, 1150, 110);
		char counter = 0;
		char c = 0;
		char name[100] = {};
		bool useC = 0;
		while (1) {
			if (KEY_DOWN(0x14)) {//大写锁定
				useC = !useC;
			}
			for (c = 'A'; c <= 'Z'; ++c) {//字母
				if (KEY_DOWN(c)) {
					if (useC) name[counter] = c;//大写字母
					else name[counter] = c - 'A' + 'a';//小写字母
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			for (c = '0'; c <= '9'; ++c) {//数字
				if (KEY_DOWN(c)) {
					name[counter] = c;
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			if (KEY_DOWN(0x0D)) {//回车键
				break;
			}
			if (KEY_DOWN(0x08)) {//退格键
				if (counter > 0) {
					--counter;
					name[counter] = 0;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			Sleep(60);
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				mainboard.board[i][j] = 0;
			}
		}
		mainboard.isFinished = 0;
		mainboard.round = 0;
		mainboard.nextmove = 1;
		int g, n, k;
		int q1, q2, q3;
		fstream f;
		f.open(name, ios::in);
		f >> g >> n >> k;
		f >> q1 >> q2 >> q3;
		gamemode = q1;
		AIstrength = q2;
		AIdepth = q3;
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < 3; ++j) {
				f >> g;
				mainboard.game[i][j] = g;
			}
			mainboard.move(mainboard.game[i][0], mainboard.game[i][1], mainboard.game[i][2]);
		}
		f.close();
	}
	else if (num == 14) {//复盘，输入对局名
		settextstyle(20, 0, "宋体");
		settextcolor(BLACK);
		outtextxy(850, 50, "输入文件名：");
		setlinecolor(BLACK);
		fillrectangle(850, 80, 1150, 110);
		char counter = 0;
		char c = 0;
		char name[100] = {};
		bool useC = 0;
		while (1) {
			if (KEY_DOWN(0x14)) {//大写锁定
				useC = !useC;
			}
			for (c = 'A'; c <= 'Z'; ++c) {//字母
				if (KEY_DOWN(c)) {
					if (useC) name[counter] = c;//大写字母
					else name[counter] = c - 'A' + 'a';//小写字母
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			for (c = '0'; c <= '9'; ++c) {//数字
				if (KEY_DOWN(c)) {
					name[counter] = c;
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			if (KEY_DOWN(0x0D)) {//回车键
				break;
			}
			if (KEY_DOWN(0x08)) {//退格键
				if (counter > 0) {
					--counter;
					name[counter] = 0;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			Sleep(60);
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				mainboard.board[i][j] = 0;
			}
		}
		mainboard.isFinished = 0;
		mainboard.round = 0;
		mainboard.nextmove = 1;
		int g, n, k;
		int q1, q2, q3;
		fstream f;
		f.open(name, ios::in);
		f >> g >> n >> k;
		f >> q1 >> q2 >> q3;
		gamemode = q1;
		AIstrength = q2;
		AIdepth = q3;
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < 3; ++j) {
				f >> g;
				mainboard.game[i][j] = g;
			}
			mainboard.move(mainboard.game[i][0], mainboard.game[i][1], mainboard.game[i][2]);
		}
		f.close();
		gamemode = 14;
	}
	else if (num == 15) {//空棋盘
		gamemode = 6;
		mainboard.prepare(1);
	}
	else if (num == 16) {//初始棋盘
		gamemode = 6;
		mainboard.prepare(0);
	}
	else if (num == 17) {//读档
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				mainboard.board[i][j] = 0;
			}
		}
		mainboard.isFinished = 0;
		mainboard.round = 0;
		mainboard.nextmove = 1;
		int c, n, k;
		int q1, q2, q3;
		fstream f;
		f.open("quickstart", ios::in);
		f >> c >> n >> k;
		f >> q1 >> q2 >> q3;
		gamemode = q1;
		AIstrength = q2;
		AIdepth = q3;
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < 3; ++j) {
				f >> c;
				mainboard.game[i][j] = c;
			}
			mainboard.move(mainboard.game[i][0], mainboard.game[i][1], mainboard.game[i][2]);
		}
		f.close();
	}
	else if (num == 18) {//规则
		settextcolor(BLACK);
		settextstyle(30, 0, "宋体");
		outtextxy(850, 100, "黑白棋规则：");
		outtextxy(850, 140, "黑棋先行，双方把棋子落在方格内。");
		outtextxy(850, 180, "一次合法的落子是指：一方落下棋子");
		outtextxy(850, 220, "后，在横、竖、斜三个方向上有自己");
		outtextxy(850, 260, "的棋子，且自己的两个棋子中间的格");
		outtextxy(850, 300, "子里面全部是对方的棋子。");
		outtextxy(850, 340, "落子后必须把对方所有被夹住的棋子");
		outtextxy(850, 380, "变成本方的棋子。");
		outtextxy(850, 420, "当双方都不存在可以落子的位置时，");
		outtextxy(850, 460, "棋局结束。");
		outtextxy(850, 500, "结束时棋子多的一方获胜。");
		outtextxy(850, 600, "点击空格继续……");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	else if (num == 19) {//使用说明
		settextcolor(BLACK);
		settextstyle(30, 0, "宋体");
		outtextxy(850, 100, "程序使用说明：");
		outtextxy(850, 150, "关于棋盘和按钮：");
		outtextxy(850, 360, "关于菜单：");
		outtextxy(850, 500, "点击空格继续……");
		settextstyle(20, 0, "宋体");
		outtextxy(850, 180, "使用鼠标左键在棋盘上点击即可落子；");
		outtextxy(850, 200, "在双人模式下使用右键可以在棋盘上摆一枚棋子，随后点");
		outtextxy(850, 220, "击空格更换下一方落子，或点击回车仍然本方落子；");
		outtextxy(850, 240, "使用鼠标左键点击按钮选中按钮一次，棋盘更新后取消选");
		outtextxy(850, 260, "中状态；右键点击持续选中按钮，直至使用左键取消；");
		outtextxy(850, 280, "菜单、退出两个按钮无法被持续选中；");
		outtextxy(850, 300, "悔棋按钮被持续选中后不会持续触发；");
		outtextxy(850, 320, "使用AI按钮可以区别黑棋和白棋分别使用。");
		outtextxy(850, 390, "菜单可以选择对局模式和AI属性；");
		outtextxy(850, 410, "点击确认后按照设置开始对局，若未选择则保留上次配置；");
		outtextxy(850, 430, "点击取消后恢复上次状态并继续。");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	else if (num == 20) {//AI说明
		settextcolor(BLACK);
		settextstyle(30, 0, "宋体");
		outtextxy(850, 100, "关于AI：");
		outtextxy(850, 150, "AI采用minmax算法，可手动选择权重");
		outtextxy(850, 180, "以及搜索深度；");
		outtextxy(850, 210, "当搜索深度大于5步时，在第5步进行");
		outtextxy(850, 240, "剪枝，但计算时间仍然过长，不推荐");
		outtextxy(850, 270, "使用太大的搜索深度；");
		outtextxy(850, 300, "AI对棋子数量、价值、对角的控制力、");
		outtextxy(850, 330, "对对方的限制以及对奇偶的控制五个");
		outtextxy(850, 360, "参数加权；");
		outtextxy(850, 390, "权重随局面的变化而变化。");
		outtextxy(850, 490, "点击空格继续……");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	else if (num == 21) {//其他
		settextcolor(BLACK);
		settextstyle(30, 0, "宋体");
		outtextxy(850, 100, "作者：陆昶安");
		outtextxy(850, 130, "学号：2300012991");
		outtextxy(850, 200, "点击空格继续……");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	return;
}