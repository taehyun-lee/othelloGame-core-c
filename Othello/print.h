#pragma once
#define MAPSIZE 8
#define MENUNUM 4
#define CONSOLE_WIDTH 100
#define CONSOLE_HEIGHT 50

/**
* 게임 시작메인메뉴를 출력
*/
void printMainmenu();

/**
* 부가메뉴 출력(제한시간, 흑/백 스코어, 차례, 나가기버튼)
* @param _black_turn: 현재 플레이어 턴 확인 변수(boolean) , _p1_score: p1의 현재 돌 개수  _p2_score: p2의 현재 돌 개수
*/
void printSubmenu(boolean _black_turn, int _p1_score, int _p2_score);

/**
* 오셀로의 판 출력
*/
void printMap();

/**
* 흑/백 돌을 출력
*/
void printStone();

/**
* 특정 돌을 색깔로 출력
* @param _a : 색깔로 칠할 돌의 행, _b : 색깔로 칠할 돌의 열
*/
void printSpecificStone(int _a, int _b);

/**
* 게임 종료 메시지 출력
* @param _playtime : 총 플레이 시간(s), _p1_score : p1의 돌 개수, _p2_score : p2의 돌 개수
* 기록할 수 있는 최대 총 플레이 시간은 59m 59s
*/
void printEndMsg(int _p1_score, int _p2_score);

/**
* 게임 저장 여부 질문 출력
*/
void printSave();

/*
* 게임 기록 리스트 출력
* @param _record : 출력할 레코드의 리스트
* @param _n : 출력할 행의 개수
* p1score p2score winner playtime date
 */
void printRecord(int(*_record)[5], int _n);