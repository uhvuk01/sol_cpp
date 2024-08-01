#ifndef SOLO_H_
#define SOLO_H_
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include <climits>
#include <cctype>
#include<ctime>
#include <unistd.h>
#define sec 1
#define DoubleRand(x,y)  x+(double)rand()/RAND_MAX*(y-x)
#define FloatRand(x,y)  x+(float)rand()/RAND_MAX*(y-x)
#define IntRand(x,y)  x+rand()%(y-x)
using namespace std;
enum flag{lv0,lv1,quit,lv100};
struct hero{
    string name;
    int LV;
    double exp;
    double LV_exp_count[100];
};
void game_start(hero* any);                          // 게임시작 함수
void run_exp(hero* any,int* turn);                   // 경험치 득실 진행 함수
void Lv_UP(hero* any, double* up_exp,int(* flag));     // 레벨업 함수
void Lv_DOWN(hero* any, double* up_exp,int(* flag));     // 레벨다운 함수 (오버로딩)
void next_turn(hero* any,int* turn,int(* flag));     // 다음 턴 진행여부 판단 함수
void end_credit(hero* any,int(* flag),int* turn);    // 엔딩크레딧 함수
void quest(hero* any,int(* flag),int* quest_count);  // 퀘스트

#endif
