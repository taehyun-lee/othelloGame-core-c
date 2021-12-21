#include "common.h"

void getScore(int* _p1, int* _p2)
{
	int i, j;
	*_p1 = 0;
	*_p2 = 0;
	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			if (map[i][j] == 1)
				(*_p1)++;
			else if (map[i][j] == 2)
				(*_p2)++;
		}
	}
}

boolean isEndGame() {


	//흑돌이 놓을수 없음 경우&& 백돌이 놓을 자리가 없음
	//	return 1;

	boolean boardSummary[3]; // 판의 요약
						// boradSummary[0]은 판 안에 빈 자리가 있는지를 확인하는 자리
						// boradSummary[1]은 판 안에 놓여진 흑돌이 있는지를 확인하는 자리
						// boradSummary[2]은 판 안에 놓여진 백돌이 있는지를 확인하는 자리

	for (int i = 1; i < 9; i++) {		// 판 전체를 한번 훑는 반복문 (1,1)~(8,8)
		for (int j = 1; j < 9; j++) {	
			switch (map[i][j]) {
			case 0 :	// 빈 자리가 있다면
				boardSummary[0] = 1; // boardSummary[0]에 참 값 저장
				break;
			case 1:		// 흑돌이 있다면
				boardSummary[1] = 1;	//boardSummary[1]에 참 값 저장
				break;
			case 2:		// 백돌이 있다면
				boardSummary[2] = 1;	//boradSummary[2]에 참 값 저장
				break;
			}
		}
		
		if (boardSummary[1] == boardSummary[2]) // boardSummary 처리 ([1]==[2]인 상태면 게임을 진행해야 함, 모르겠으면 노가다 ㄱㄱ)
			return 0;
		return 1;
	}
}

bool convertToIndex(int* _x, int* _y)
{
	int i, j;
	int base_x = 18, base_y = 9;
	int dx = 8, dy = 4;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (*_x >= base_x + i * dx && *_x < base_x + (i + 1) * dx && *_y >= base_y + j * dy && *_y < base_y - 1 + (j + 1) * dy) {
				*_x = j;
				*_y = i;
				return true;
			}
		}
	}

	return false;
}

boolean isBlackPos(int _x,int _y) {
	int x = 0;
	int y = 0;
	const int WAYS = 8;
	const int WAY[8][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 }, { 1, 1 } };
	for (int w = 0; w < WAYS; w++) {
		int nx = x + WAY[w][0];
		int	ny = y + WAY[w][1];
		if (nx < 0 || nx >= 3 || ny < 0 || ny >= 5) 
			continue;
	}
}

void gotoxy(int _x, int _y) {
	COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
