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
								if (pc[i] != j) {//ɾ����һ��ѡ�е�״̬
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
								//ѡ�е�ǰ��ť
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
				else if (i == 3) {//���ΰ�ť����Ҫ���»�������������
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
							settextstyle(20, 0, "����");
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
								//ѡ�е�ǰ��ť����˸һ�Σ����Ҳ�������Ϣ��
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
	case 10:return { 230,200,270 };//270���������룬10��
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
	settextstyle(20, 0, "����");
	outtextxy(temp.x + temp.len + 20, temp.y + 5, "5");
	settextstyle(30, 0, "����");
	outtextxy(80, 70, "�Ծ�ģʽ��");
	outtextxy(80, 100, "�˻������ִ�ڰ����  �����Ծ�  ˫�˶Ծ�");//1-6
	outtextxy(80, 150, "AI���ã�����  �м�  �߼�");//7-9
	outtextxy(80, 200, "������ȣ�");//10
	outtextxy(80, 300, "���棺�ݴ�  ����Ϊ����");//11-12
	outtextxy(80, 350, "�򿪣��ɶԾ�  ����  ������  ��ʼ����  ʹ���ݴ�");//13-17
	outtextxy(80, 450, "����������  ʹ�ý̳�  AI˵��  ����");//18-21
	outtextxy(280, 700, "ȡ��  ȷ��  �˳�");//22-24
	return;
}
void sidemenu(char num) {
	setlinecolor(BK);
	setfillcolor(BK);
	fillrectangle(BOARDSIZE - 1, 0, TOTALWIDTH - 1, BOARDSIZE - 1);
	if (num == 11) {//�浵
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
	else if (num == 12) {//�����ļ������浵��ֻ����س���ʹ����ֵʱ������
		settextstyle(20, 0, "����");
		settextcolor(BLACK);
		outtextxy(850, 50, "�����ļ�����");
		setlinecolor(BLACK);
		fillrectangle(850, 80, 1150, 110);
		fstream f;
		char counter = 0;
		char c = 0;
		char name[100] = {};
		bool useC = 0;
		while (1) {
			if (KEY_DOWN(0x14)) {//��д����
				useC = !useC;
			}
			for (c = 'A'; c <= 'Z'; ++c) {//��ĸ
				if (KEY_DOWN(c)) {
					if (useC) name[counter] = c;//��д��ĸ
					else name[counter] = c - 'A' + 'a';//Сд��ĸ
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			for (c = '0'; c <= '9'; ++c) {//����
				if (KEY_DOWN(c)) {
					name[counter] = c;
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			if (KEY_DOWN(0x0D)) {//�س���
				break;
			}
			if (KEY_DOWN(0x08)) {//�˸��
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
	else if (num == 13) {//�ɶԾ֣������ļ���
		settextstyle(20, 0, "����");
		settextcolor(BLACK);
		outtextxy(850, 50, "�����ļ�����");
		setlinecolor(BLACK);
		fillrectangle(850, 80, 1150, 110);
		char counter = 0;
		char c = 0;
		char name[100] = {};
		bool useC = 0;
		while (1) {
			if (KEY_DOWN(0x14)) {//��д����
				useC = !useC;
			}
			for (c = 'A'; c <= 'Z'; ++c) {//��ĸ
				if (KEY_DOWN(c)) {
					if (useC) name[counter] = c;//��д��ĸ
					else name[counter] = c - 'A' + 'a';//Сд��ĸ
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			for (c = '0'; c <= '9'; ++c) {//����
				if (KEY_DOWN(c)) {
					name[counter] = c;
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			if (KEY_DOWN(0x0D)) {//�س���
				break;
			}
			if (KEY_DOWN(0x08)) {//�˸��
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
	else if (num == 14) {//���̣�����Ծ���
		settextstyle(20, 0, "����");
		settextcolor(BLACK);
		outtextxy(850, 50, "�����ļ�����");
		setlinecolor(BLACK);
		fillrectangle(850, 80, 1150, 110);
		char counter = 0;
		char c = 0;
		char name[100] = {};
		bool useC = 0;
		while (1) {
			if (KEY_DOWN(0x14)) {//��д����
				useC = !useC;
			}
			for (c = 'A'; c <= 'Z'; ++c) {//��ĸ
				if (KEY_DOWN(c)) {
					if (useC) name[counter] = c;//��д��ĸ
					else name[counter] = c - 'A' + 'a';//Сд��ĸ
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			for (c = '0'; c <= '9'; ++c) {//����
				if (KEY_DOWN(c)) {
					name[counter] = c;
					++counter;
					fillrectangle(850, 80, 1150, 110);
					outtextxy(855, 85, name);
				}
			}
			if (KEY_DOWN(0x0D)) {//�س���
				break;
			}
			if (KEY_DOWN(0x08)) {//�˸��
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
	else if (num == 15) {//������
		gamemode = 6;
		mainboard.prepare(1);
	}
	else if (num == 16) {//��ʼ����
		gamemode = 6;
		mainboard.prepare(0);
	}
	else if (num == 17) {//����
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
	else if (num == 18) {//����
		settextcolor(BLACK);
		settextstyle(30, 0, "����");
		outtextxy(850, 100, "�ڰ������");
		outtextxy(850, 140, "�������У�˫�����������ڷ����ڡ�");
		outtextxy(850, 180, "һ�κϷ���������ָ��һ����������");
		outtextxy(850, 220, "���ںᡢ����б�������������Լ�");
		outtextxy(850, 260, "�����ӣ����Լ������������м�ĸ�");
		outtextxy(850, 300, "������ȫ���ǶԷ������ӡ�");
		outtextxy(850, 340, "���Ӻ����ѶԷ����б���ס������");
		outtextxy(850, 380, "��ɱ��������ӡ�");
		outtextxy(850, 420, "��˫���������ڿ������ӵ�λ��ʱ��");
		outtextxy(850, 460, "��ֽ�����");
		outtextxy(850, 500, "����ʱ���Ӷ��һ����ʤ��");
		outtextxy(850, 600, "����ո��������");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	else if (num == 19) {//ʹ��˵��
		settextcolor(BLACK);
		settextstyle(30, 0, "����");
		outtextxy(850, 100, "����ʹ��˵����");
		outtextxy(850, 150, "�������̺Ͱ�ť��");
		outtextxy(850, 360, "���ڲ˵���");
		outtextxy(850, 500, "����ո��������");
		settextstyle(20, 0, "����");
		outtextxy(850, 180, "ʹ���������������ϵ���������ӣ�");
		outtextxy(850, 200, "��˫��ģʽ��ʹ���Ҽ������������ϰ�һö���ӣ�����");
		outtextxy(850, 220, "���ո������һ�����ӣ������س���Ȼ�������ӣ�");
		outtextxy(850, 240, "ʹ�������������ťѡ�а�ťһ�Σ����̸��º�ȡ��ѡ");
		outtextxy(850, 260, "��״̬���Ҽ��������ѡ�а�ť��ֱ��ʹ�����ȡ����");
		outtextxy(850, 280, "�˵����˳�������ť�޷�������ѡ�У�");
		outtextxy(850, 300, "���尴ť������ѡ�к󲻻����������");
		outtextxy(850, 320, "ʹ��AI��ť�����������Ͱ���ֱ�ʹ�á�");
		outtextxy(850, 390, "�˵�����ѡ��Ծ�ģʽ��AI���ԣ�");
		outtextxy(850, 410, "���ȷ�Ϻ������ÿ�ʼ�Ծ֣���δѡ�������ϴ����ã�");
		outtextxy(850, 430, "���ȡ����ָ��ϴ�״̬��������");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	else if (num == 20) {//AI˵��
		settextcolor(BLACK);
		settextstyle(30, 0, "����");
		outtextxy(850, 100, "����AI��");
		outtextxy(850, 150, "AI����minmax�㷨�����ֶ�ѡ��Ȩ��");
		outtextxy(850, 180, "�Լ�������ȣ�");
		outtextxy(850, 210, "��������ȴ���5��ʱ���ڵ�5������");
		outtextxy(850, 240, "��֦��������ʱ����Ȼ���������Ƽ�");
		outtextxy(850, 270, "ʹ��̫���������ȣ�");
		outtextxy(850, 300, "AI��������������ֵ���ԽǵĿ�������");
		outtextxy(850, 330, "�ԶԷ��������Լ�����ż�Ŀ������");
		outtextxy(850, 360, "������Ȩ��");
		outtextxy(850, 390, "Ȩ�������ı仯���仯��");
		outtextxy(850, 490, "����ո��������");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	else if (num == 21) {//����
		settextcolor(BLACK);
		settextstyle(30, 0, "����");
		outtextxy(850, 100, "���ߣ�½�ư�");
		outtextxy(850, 130, "ѧ�ţ�2300012991");
		outtextxy(850, 200, "����ո��������");
		while (1) {
			if (KEY_DOWN(0x20))return;
		}
	}
	return;
}