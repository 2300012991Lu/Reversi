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

//随局面的权变
weight_change getstate(void);
//基于黑棋的评分
char getchess(void);
int getvalue(void);
char gettag(void);
char getrestrict(char);
bool getoddeven(char);
//AI函数
double getAI(char);
void bot(char);
void deep_bot(char, char);

#endif