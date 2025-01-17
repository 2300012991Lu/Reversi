#include"myIMAGE.h"
#include"myGAME.h"
#include"myAI.h"
using namespace std;

int main() {

	initgraph(TOTALWIDTH, BOARDSIZE, EX_SHOWCONSOLE);
	setbkcolor(BK);
	setbkmode(TRANSPARENT);
	cleardevice();
	srand((unsigned)time(NULL));
	drawboard();
	gamemode = 6;
	AIstrength = 9;
	mainboard.prepare(0);
	mainboard.draw();
	for (char i = 0; i < 4; ++i) {
		chess_tree[i][0] = chess_tree[i][1] = -1;
	}

	while (1) {
		AIboard = mainboard;
		mainboard.draw();
		outputsideinformation();
		AIhelpx = AIhelpy = -1;
		if (mainboard.round > 4) {
			drawlast(mainboard.game[mainboard.round - 1][0], mainboard.game[mainboard.round - 1][1]);
		}
		if ((help || useBlackAI || useWhiteAI || buttonstate[1] || buttonstate[2]) && !mainboard.isFinished) {
			if (mainboard.nextmove == 1 && useBlackAI) {
				bot(1);
				if (buttonstate[4] != 1 && buttonstate[4] != 3) {
					useBlackAI = 0;
				}
				else drawbutton(4, 1);
			}
			else if (mainboard.nextmove == -1 && useWhiteAI) {
				bot(-1);
				if (buttonstate[4] != 2 && buttonstate[4] != 3) {
					useWhiteAI = 0;
				}
				else drawbutton(4, 1);
			}
			mainboard.drawtips();
			help = 0;
		}
		if (!useBlackAI && mainboard.nextmove == 1) drawbutton(4, 0);
		else if (!useWhiteAI && mainboard.nextmove == -1)drawbutton(4, 0);
		if (help == 2 || buttonstate[2]) {
			outputAIinformation();
		}
		else {
			setlinecolor(BK);
			setfillcolor(BK);
			fillrectangle(900, 400, 1300, 600);
		}
		opbutton = -1;
		if (((gamemode == 2 && mainboard.nextmove == 1) || (gamemode == 3 && mainboard.nextmove == -1) || gamemode == 6) || mainboard.isFinished) {//轮到玩家落子
			input();
			if (opbutton == 0) {//菜单
				while (1) {
					char t1 = gamemode;
					char t2 = AIstrength;
					char t3 = AIdepth;
					chessboard t4 = mainboard;
					mainmenu();
					menuinput();
					if (inputbutton == 22) {//取消
						gamemode = t1;
						AIstrength = t2;
						AIdepth = t3;
						mainboard = t4;
						break;
					}
					else if (inputbutton == 23) {//确认
						if (gamemode == 1 || gamemode == 4) {//随机
							bool p = rand() % 2;
							gamemode = 2 + p;
						}
						if (AIstrength == 7)
							for (char q = 0; q < 5; ++q) blackweight[q] = whiteweight[q] = weight_1[q];
						else if (AIstrength == 8)
							for (char q = 0; q < 5; ++q) blackweight[q] = whiteweight[q] = weight_2[q];
						else if (AIstrength == 9)
							for (char q = 0; q < 5; ++q) blackweight[q] = whiteweight[q] = weight_3[q];
						mainboard.prepare(0);
						drawboard();
						mainboard.draw();
						break;
					}
					else if (inputbutton == 24) {//退出
						return 0;
					}
					else if (inputbutton >= 11 && inputbutton <= 21) {
						if (inputbutton >= 13 && inputbutton <= 17)break;
						gamemode = t1;
						AIstrength = t2;
						AIdepth = t3;
						mainboard = t4;
						break;
					}
				}
				drawboard();
				mainboard.draw();
				outputsideinformation();
				if (gamemode == 14) {
					setlinecolor(BK);
					setfillcolor(BK);
					fillrectangle(BOARDSIZE - 1, 0, TOTALWIDTH - 1, BOARDSIZE - 1);
					settextcolor(BLACK);
					settextstyle(30, 0, "黑体");
					outtextxy(900, 100, "复盘模式：");
					outtextxy(900, 140, "按方向键播放棋局");
					outtextxy(900, 180, "按空格键使用/关闭AI");
					outtextxy(900, 220, "按回车键退出复盘模式");
					chessboard tempboard = mainboard;
					char r = 0;
					bool useAI = 0;
					while (1) {
						Sleep(100);
						if (KEY_DOWN(0x0D)) {//回车键退出复盘模式
							break;
						}
						if (KEY_DOWN(0x20)) {//空格键开启AI
							useAI = !useAI;
							AIhelpx = AIhelpy = -1;
							mainboard.drawtips();
						}
						if (KEY_DOWN(0x25)) {//左箭头：向前一步
							mainboard.prepare(1);
							if (r > 0)--r;
							for (char c = 0; c < r; ++c) {
								mainboard.move(tempboard.game[c][0], tempboard.game[c][1], tempboard.game[c][2]);
							}
							mainboard.draw();
							if (useAI)
								bot(mainboard.nextmove);
							if (mainboard.round > 4) {
								drawlast(mainboard.game[mainboard.round - 1][0], mainboard.game[mainboard.round - 1][1]);
								mainboard.drawtips();
							}
						}
						if (KEY_DOWN(0x27)) {//右箭头：向后一步
							mainboard.prepare(1);
							if (r < tempboard.round)++r;
							for (char c = 0; c < r; ++c) {
								mainboard.move(tempboard.game[c][0], tempboard.game[c][1], tempboard.game[c][2]);
							}
							mainboard.draw();
							if (useAI)
								bot(mainboard.nextmove);
							if (mainboard.round > 4) {
								drawlast(mainboard.game[mainboard.round - 1][0], mainboard.game[mainboard.round - 1][1]);
								mainboard.drawtips();
							}
						}
						if (KEY_DOWN(0x26)) {//上箭头：向前五步
							mainboard.prepare(1);
							if (r > 4)r -= 5;
							else r = 0;
							for (char c = 0; c < r; ++c) {
								mainboard.move(tempboard.game[c][0], tempboard.game[c][1], tempboard.game[c][2]);
							}
							mainboard.draw();
							if (useAI)
								bot(mainboard.nextmove);
							if (mainboard.round > 4) {
								drawlast(mainboard.game[mainboard.round - 1][0], mainboard.game[mainboard.round - 1][1]);
								mainboard.drawtips();
							}
						}
						if (KEY_DOWN(0x28)) {//下箭头：向后五步
							mainboard.prepare(1);
							if (r < tempboard.round - 4)r += 5;
							else r = tempboard.round;
							for (char c = 0; c < r; ++c) {
								mainboard.move(tempboard.game[c][0], tempboard.game[c][1], tempboard.game[c][2]);
							}
							mainboard.draw();
							if (useAI)
								bot(mainboard.nextmove);
							if (mainboard.round > 4) {
								drawlast(mainboard.game[mainboard.round - 1][0], mainboard.game[mainboard.round - 1][1]);
								mainboard.drawtips();
							}
						}
					}
					drawboard();
					gamemode = 6;
					mainboard = tempboard;
				}
				continue;
			}
			else if (opbutton == 1) {//提示
				help = 1;
				continue;
			}
			else if (opbutton == 2) {//AI参数信息
				help = 2;
				continue;
			}
			else if (opbutton == 3) {//悔棋
				mainboard.rerun();
				continue;
			}
			else if (opbutton == 4) {//AI开始
				if (!mainboard.isFinished) {
					if (mainboard.nextmove == 1) {
						useBlackAI = 1;
					}
					else if (mainboard.nextmove == -1) {
						useWhiteAI = 1;
					}
				}
				//点击后若下一手使用黑棋，则载入黑棋AI；若使用白棋，则载入白棋AI
				continue;
			}
			else if (opbutton == 5) {//退出
				return 0;
			}
			if (inputx >= 0 && inputx <= 7 && inputy >= 0 && inputy <= 7) {
				if (useRB) {
					if (gamemode == 6) {
						mainboard.strongmove(inputx, inputy, mainboard.nextmove);
						mainboard.draw();
						while (1) {
							if (KEY_DOWN(0x20)) {
								mainboard.nextmove = -mainboard.nextmove;
								break;
							}
							else if (KEY_DOWN(0x0D))break;
							Sleep(50);
						}
					}
					useRB = 0;
				}
				else {
					mainboard.move(inputx, inputy);
				}
				inputx = inputy = -1;
			}
			mainboard.draw();

		}
		if (((gamemode == 2 && mainboard.nextmove == -1) || (gamemode == 3 && mainboard.nextmove == 1) || gamemode == 5) && !mainboard.isFinished) {//轮到机器落子
			bot(mainboard.nextmove);
			mainboard.move(AIhelpx, AIhelpy);
			mainboard.draw();
		}
	}

	return 0;
}
