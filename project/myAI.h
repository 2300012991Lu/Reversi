#ifndef MY_AI_H
#define MY_AI_H 0

#include"myvarible.h"

extern struct weight_change {
	double chess;
	double value;
	double tag;
	double restrict;
	double oddeven;
};
extern struct prime_score {
	char score[8][8];
};

//������Ȩ��
weight_change getstate(void);
//���ں��������
char getchess(void);
int getvalue(void);
char gettag(void);
char getrestrict(char);
bool getoddeven(char);
//AI����
double getAI(char);
void bot(char);
void deep_bot(char, char);

#endif