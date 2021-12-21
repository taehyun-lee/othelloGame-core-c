#pragma once
#include "common.h"

/*
*	특정 위치에 돌을 놓는 함수
*	@parameter int _a:놓을 돌의 x좌표 int_b:놓을 돌의 y좌표
*/
void putStone(int _a, int _b);

/*
*	제한시간 안에 돌을 놓지 않았을 시 랜덤으로 돌을 놓는 함수
*	@parameter int _player: 제한시간 안에 돌을 놓지 못한 플레이어
*/
void putRandomStone(int _player);

/*
*	주변 돌을 뒤집는 함수
*	@parameter int_player:현재 턴을 진행중인 플레이어
*/
void flipStone(int _player);

/*
*	마우스입력을 받아 해당 xy값 반환하는 함수
*	@parameter int* _x: 입력받은 마우스의 x값, int* _y: 입력받은 마우스의 y값 time_t _start: 턴이 시작했을때의 시간값
*/
void getXY(int* _x, int* _y,time_t _start);

/*
*	마우스로 입력된 xy값을 배열의 인덱스로 보정해 주는 함수
*	@parameter int* _x: 입력받은 마우스의 x값, int* _y: 입력받은 마우스의 y값
*   @return 판 안에 있는 x,y좌표을 입력받아서 정상적으로 변환되었을 때 true반환
*/
bool convertToIndex(int* _x, int* _y);

/*
*	흑돌이 놓을 수 있는 자리인지 계산
*	@parameter int _x: 계산될 자리의 x값 int_y: 계산될 자리의 y값
*	@return	놓을 수 있는 자리가 맞다면 true 놓을 수 있는 자리가 아니라면 false
*/
boolean isBlackPos(int _x, int _y);

/*
*	백돌이 놓을 수 있는 자리인지 계산
*	@parameter int _x: 계산될 자리의 x값 int_y: 계산될 자리의 y값
*	@return 놓을 수 있는 자리가 맞다면 true 놓을 수 있는 자리가 아니라면 false
*/
boolean isWhitePos(int _x, int _y);

/*
*	현재 판의 score를 계산하는 함수
*	@parameter int* _p1: player1의 점수 int* _p2:player2의 점수
*/
void getScore(int* _p1, int* _p2);

/*
*	게임이 종료되었는지 판단하는 함수
*	@return	종료 true 종료 되지 않았다면 false
*/
boolean isEndGame();

/*
*	누가 이겼는지 판단하는 함수
*	@return	p1의 승: return 1; p2의 승리: return 2; 동점이면 return -1;
*/
int whoseWin();

/*
*	클릭되었는지 확인하는 함수
*/
boolean isClick();

/*
* 커서를 X,Y 위치로 옮기는 함수
* @parameter _x: 옮기고 싶은 x값 _y: 옮기고 싶은 y값
*/
void gotoxy(int _x, int _y);
