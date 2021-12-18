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
*/
void printSubmenu(boolean _black_turn, int _p1_score, int _p2_score);

/**
* 오셀로의 판 출력
*/
void printMap();

/**
* 흑/백 돌을 출력
*/
void printStone()

/**
* 게임 종료 메시지 출력
* @param _playtime : 총 플레이 시간(s), _p1_score : p1의 돌 개수, _p2_score : p2의 돌 개수
* 기록할 수 있는 최대 총 플레이 시간은 59m 59s
*/;
void printEndMsg(int _playtime, int _p1_score, int _p2_score);

/**
* 게임 저장 여부 질문 출력
*/
void printSave();

/**
* 콘솔 창에서 x,y좌표로 커서 이동
* @param _x : 이동할 x좌표, _y : 이동할 y좌표
*/
void gotoxy(int _x, int _y);
