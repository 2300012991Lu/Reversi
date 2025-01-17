#include"myAI.h"

prime_score score_balanced = {
	{
		0,0,5,9,9,5,0,0,
		0,0,7,4,4,7,0,0,
		5,7,3,2,2,3,7,5,
		9,4,2,1,1,2,4,9,
		9,4,2,1,1,2,4,9,
		5,7,3,2,2,3,7,5,
		0,0,7,4,4,7,0,0,
		0,0,5,9,9,5,0,0
	}
};
prime_score score_conservative = {
	{
		0,0,1,3,3,1,0,0,
		0,0,5,6,6,5,0,0,
		1,5,4,7,7,4,5,1,
		3,6,7,8,8,7,6,3,
		3,6,7,8,8,7,6,3,
		1,5,4,7,7,4,5,1,
		0,0,5,6,6,5,0,0,
		0,0,1,3,3,1,0,0
	}
};
prime_score score_aggressive = {
	{
		0,0,7,6,6,7,0,0,
		0,0,8,4,4,8,0,0,
		7,8,9,3,3,9,8,7,
		6,4,3,2,2,3,4,6,
		6,4,3,2,2,3,4,6,
		7,8,9,3,3,9,8,7,
		0,0,8,4,4,8,0,0,
		0,0,7,6,6,7,0,0
	}
};
prime_score score_use = score_balanced;
char tree[11][3] = {};
double score[11] = {};
double sc = 0;
char counter = 0;


//������Ȩ��
weight_change getstate(void) {
	//���Ǳ�����mainboard�ϣ���ֹ����ʱ������Ȩ������
	double chess, value, tag, restrict, oddeven;
	if (mainboard.round < 18) {
		chess = -2;
		value = 1.2;
		tag = 1000;
		restrict = 1;
		oddeven = 1;
	}
	else if (mainboard.round < 25) {
		chess = 0;
		value = 2;
		tag = 800;
		restrict = 4;
		oddeven = 2;
	}
	else if (mainboard.round < 45) {
		chess = 1;
		value = 0.8;
		tag = 750;
		restrict = 10;
		oddeven = 2;
	}
	else if (mainboard.round < 58) {
		chess = 4;
		value = 0.1;
		tag = 500;
		restrict = 3;
		oddeven = 3;
	}
	else {
		chess = 20;
		value = 0.03;
		tag = 50;
		restrict = 2;
		oddeven = 1;
	}
	return { chess, value, tag, restrict, oddeven };
}
//���ں��������
char getchess(void) {//���ӣ����ں���
	return AIboard.count(0);
}
int getvalue(void) {//��ȡ��ֵ�����ں���
	int counter = 0;
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			if (AIboard.board[i][j]) {
				counter += score_use.score[i][j] * AIboard.board[i][j];
			}
		}
	}
	return counter;
}
char gettag(void) {//��ȡ��ǩ�����ں���
	char tag = 0;

	if (AIboard.board[0][0]) tag += 5 * AIboard.board[0][0];
	else if (AIboard.board[1][1]) tag -= 5 * AIboard.board[1][1];
	else if (AIboard.board[0][1] || AIboard.board[1][0]) tag -= (AIboard.board[0][1] + AIboard.board[1][0]);

	if (AIboard.board[0][7]) tag += 5 * AIboard.board[0][7];
	else if (AIboard.board[1][6]) tag -= 5 * AIboard.board[1][6];
	else if (AIboard.board[0][6] || AIboard.board[1][0]) tag -= (AIboard.board[0][6] + AIboard.board[1][7]);

	if (AIboard.board[7][0]) tag += 5 * AIboard.board[7][0];
	else if (AIboard.board[6][1]) tag -= 5 * AIboard.board[6][1];
	else if (AIboard.board[7][1] || AIboard.board[6][0]) tag -= (AIboard.board[7][1] + AIboard.board[6][0]);

	if (AIboard.board[7][7]) tag += 5 * AIboard.board[7][7];
	else if (AIboard.board[6][6]) tag -= 5 * AIboard.board[6][6];
	else if (AIboard.board[7][6] || AIboard.board[6][7]) tag -= (AIboard.board[7][6] + AIboard.board[6][7]);

	return tag;
}
char getrestrict(char color) {//��һ��������λ�����������ڶ�̬
	char counter = 0;
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			if (AIboard.isPossible(i, j, AIboard.nextmove)) {
				++counter;
			}
		}
	}
	//�����һ���Ǳ�������Խ��Խ��
	if (color != AIboard.nextmove)counter = -counter;
	return counter;
}
bool getoddeven(char color) {//��ż���ƣ����ڶ�̬

	//����ϣ����ż���������ܴ�
	if (color == 1) return !(AIboard.round % 2);
	else return (AIboard.round % 2);
}
//AI����
double getAI(char color) {
	weight_change wei = getstate();
	double SCORE = 0;
	double w[5] = {};
	if (color == 1) {
		for (char i = 0; i < 5; ++i) {
			w[i] = blackweight[i];
		}
	}
	else if (color == -1) {
		for (char i = 0; i < 5; ++i) {
			w[i] = whiteweight[i];
		}
	}
	SCORE = 
		w[0] * getchess() * wei.chess + //��������
		w[1] * getvalue() * wei.value + //��������
		w[2] * gettag() * wei.tag + //�ȶ���
		w[3] * getrestrict(color) * wei.restrict + //�Է�������λ����
		w[4] * getoddeven(color) * wei.oddeven;//��ż����
	return SCORE;
}
void bot(char color) {

	AIboard = mainboard;
	for (char i = 0; i < 11; ++i) {
		score[i] = 0;
		for (char j = 0; j < 3; ++j) {
			tree[i][j] = 0;
		}
	}
	sc = 0;
	counter = 0;

	if (AIboard.nextmove == 1) {//����ϣ��ȡ���ֵ
		score[counter] = -1E8;
	}
	else if (AIboard.nextmove == -1) {//����ϣ��ȡ��Сֵ
		score[counter] = 1E8;
	}
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			if (AIboard.isPossible(i, j, AIboard.nextmove)) {
				tree[counter][0] = i;
				tree[counter][1] = j;
				tree[counter][2] = AIboard.nextmove;
				AIboard.move(i, j);

				if (AIboard.isFinished) {
					char win = getchess();
					if (win == 0)sc = 0;//ƽ��
					else if (win > 0)sc = 9E7;//��ʤ
					else if (win < 0)sc = -9E7;//��ʤ
				}
				else {
					//���

					deep_bot(color, 1);

				}
				//��λ
				counter = 0;
				AIboard = mainboard;

				//min-max
				if (tree[counter][2] == 1) {//����ϣ��ȡ���ֵ
					if (score[counter + 1] > score[counter]) {
						score[counter] = score[counter + 1];
						AIhelpx = i;
						AIhelpy = j;
						for (char q = 0; q < 4 && q < AIdepth; ++q) {
							chess_tree[q][0] = tree[q][0];
							chess_tree[q][1] = tree[q][1];
						}
						for (char q = AIdepth; q < 4; ++q) {
							chess_tree[q][0] = 0;
							chess_tree[q][1] = 0;
						}
					}
				}
				else if (tree[counter][2] == -1) {//����ϣ��ȡ��Сֵ
					if (score[counter + 1] < score[counter]) {
						score[counter] = score[counter + 1];
						AIhelpx = i;
						AIhelpy = j;
						for (char q = 0; q < 4 && q < AIdepth; ++q) {
							chess_tree[q][0] = tree[q][0];
							chess_tree[q][1] = tree[q][1];
						}
						for (char q = AIdepth; q < 4; ++q) {
							chess_tree[q][0] = -1;
							chess_tree[q][1] = -1;
						}
					}
				}
			}
		}
	}

	return;
}
void deep_bot(char color, char round) {
	if (AIdepth == 1) {
		score[1] = getAI(1);
		return;
	}
	double screc = 0;
	counter = round;
	if (AIboard.nextmove == 1) {//����ϣ��ȡ���ֵ
		score[counter] = screc = -1E8;
	}
	else if (AIboard.nextmove == -1) {//����ϣ��ȡ��Сֵ
		score[counter] = screc = 1E8;
	}
	for (char i = 0; i < 8; ++i) {
		for (char j = 0; j < 8; ++j) {
			if (AIboard.isPossible(i, j, AIboard.nextmove)) {
				tree[counter][0] = i;
				tree[counter][1] = j;
				tree[counter][2] = AIboard.nextmove;
				AIboard.move(i, j);

				if (AIboard.isFinished) {
					char win = getchess();
					if (win == 0)sc = 0;//ƽ��
					else if (win > 0)sc = 9E7;//��ʤ
					else if (win < 0)sc = -9E7;//��ʤ
				}
				else {
					//���

					if (round == AIdepth - 1) {
						sc = getAI(1);
						//cout << sc << endl;
					}
					else if ((AIdepth > 5 && (round == 3 || round == 5)) || (AIdepth > 8 && (round == 7 || round == 6))) {

						double sctest = getAI(1);
						if (tree[counter][2] == 1) {//����ϣ��ȡ���ֵ
							if (sctest >= screc * 0.75) {//ֵ�÷���
								if (sctest > screc)
									screc = sctest;
								deep_bot(color, round + 1);
							}
						}
						else if (tree[counter][2] == -1) {//����ϣ��ȡ��Сֵ
							if (sctest <= screc * 0.75) {//ֵ�÷���
								if (sctest < screc)
									screc = sctest;
								deep_bot(color, round + 1);
							}
						}

					}
					else {
						deep_bot(color, round + 1);
					}

				}
				//��λ
				counter = round;
				AIboard = mainboard;
				for (char t = 0; t < counter; ++t) {
					AIboard.move(tree[t][0], tree[t][1], tree[t][2]);
				}
				//min-max
				if (tree[counter][2] == 1) {//����ϣ��ȡ���ֵ
					if (round == AIdepth - 1) {
						if (sc > score[counter]) {
							score[counter] = sc;
						}
					}
					else {
						if (score[counter + 1] > score[counter]) {
							score[counter] = score[counter + 1];
						}
					}
				}
				else if (tree[counter][2] == -1) {//����ϣ��ȡ��Сֵ
					if (round == AIdepth - 1) {
						if (sc < score[counter]) {
							score[counter] = sc;
						}
					}
					else {
						if (score[counter + 1] < score[counter]) {
							score[counter] = score[counter + 1];
						}
					}
				}
			}
		}
	}
}