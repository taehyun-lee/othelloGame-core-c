#pragma once
#include "common.h"

typedef struct pos {
	int a;
	int b;
} Pos;


/*
*	특정 위치에 돌을 놓는 함수
*	@param int _a:놓을 돌의 x좌표 int_b:놓을 돌의 y좌표
*   @return 특정 위치가 빈칸이 아니였다면 false반환
*/
bool putStone(bool _black_turn, int _a, int _b);

/*
*	제한시간 안에 돌을 놓지 않았을 시 랜덤으로 돌을 놓는 함수
*	@param int _player: 제한시간 안에 돌을 놓지 못한 플레이어
*	@return 랜덤으로 돌을 놓을 수 있는 자리가 없다면 false반환
*/
bool putRandomStone(bool _black_turn, int* _a, int* _b);

/*
*	주변 돌을 뒤집는 함수
*	@param int_player:현재 턴을 진행중인 플레이어
*/
void flipStone(int _player);

/*
*	마우스입력을 받아 해당 xy값 반환하는 함수
*	@param int* _x: 입력받은 마우스의 x값, int* _y: 입력받은 마우스의 y값 time_t _start: 턴이 시작했을때의 시간값
*/
void getXY(int* _x, int* _y);

/*
*	마우스로 입력된 xy값을 배열의 인덱스로 보정해 주는 함수
*	@param int* _x: 입력받은 마우스의 x값, int* _y: 입력받은 마우스의 y값
*   @return 판 안에 있는 x,y좌표을 입력받아서 정상적으로 변환되었을 때 true반환
*/
bool coordToIndex(int _x, int _y, int* _a, int* _b);

/*
* 입력받은 인덱스가 돌을 놓을 수 있는 자리인지 확인
* 놓을 수 있다면, 뒤집여하는 돌들의 인덱스 배열 변경
* @param _black_turn 흑 차례이면 true
* @param _a, _b 확인할 인덱스
* @param _pos 뒤집을 돌들의 인덱스 배열
*/
bool isPossiblePos(bool _black_turn, int _a, int _b, Pos* _pos);

/*
*	현재 판의 score를 계산하는 함수
*	@parameter int* _p1: player1의 점수 int* _p2:player2의 점수
*/
void getScore(int* _p1, int* _p2);

/*
*	게임이 종료되었는지 판단하는 함수
*	@return	종료 true 종료 되지 않았다면 false
*/
bool isGameEnd();

/*
*	누가 이겼는지 판단하는 함수
*	@return	p1의 승: return 1; p2의 승리: return 2; 동점이면 return -1;
*/
int whoseWin();

/*
* 커서를 X,Y 위치로 옮기는 함수
* @parameter _x: 옮기고 싶은 x값 _y: 옮기고 싶은 y값
*/
void gotoxy(int _x, int _y);

/*
* x,y 마우스 입력 받는 함수
*/
int beInput();

/*
* x,y 마우스 입력 받는 함수
*/
int getInput(WORD* vkey, COORD* pos);

/*
* 시간 다운 카운팅 및 출력
* @param avg	제한시간
* @return NULL
*/
void* threadTime(void* avg);

/*
* 유효한 마우스 입력시 좌표값 반환
* @param avg	NULL
* @return x, y array
*/
void* threadMouse(void* avg);

/*
* 어느 메뉴가 선택됬는지 확인
* @param _x, _y 클릭된 좌표
* @return 정수	아무 메뉴도 선택되지 않음(-1) new game 선택(1) continue 선택(2) record 선택(3) exit 선택(4)
*/
int whichMenuSelect(int _x, int _y);

/*
* 나가기 버튼이 선택됬는지 확인
* @param _x, _y 클릭된 좌표
* @return T/F
*/
bool isBtnExit(int _x, int _y);

/*
* 확인 버튼이 선택됬는지 확인
* @param _x, _y 클릭된 좌표
* @return T/F
*/
bool isbtnOk(int _x, int _y);

/*
* yes,no버튼이 선택됬는지 확인
* @param _x, _y 클릭된 좌표
* @return 정수 아무버튼도 선택되지 않음(-1) yes버튼(1) no버튼(0)
*/
int whichBtnSelect(int _x, int _y);

