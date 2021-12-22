#include "common.h"


void getScore(int* _p1, int* _p2)
{
	int i, j;
	*_p1 = 0;
	*_p2 = 0;
	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			if (map[i][j] == PLAYER1)
				(*_p1)++;
			else if (map[i][j] == PLAYER2)
				(*_p2)++;
		}
	}
}

int whoseWin()
{
	int x, y;
	getScore(&x, &y);

	if (x > y)
		return PLAYER1;
	else if (x < y)
		return PLAYER2;
	else
		return DRAW;
}

bool putStone(bool _black_turn, int _a, int _b)
{
	if (map[_a][_b] != EMPTY)
		return false;

	if (_black_turn)
		map[_a][_b] = PLAYER1;
	else
		map[_a][_b] = PLAYER2;
	return true;
}

bool putRandomStone(bool _black_turn, int* _a, int* _b)
{
	int i, j;
	typedef struct pos {
		int pi;
		int pj;
	} Pos;

	Pos possible[64];
	int poss_num = 0;

	if (_black_turn) {
		for (i = 1; i <= 8; i++) {
			for (j = 1; j <= 8; j++) {
				if (isBlackPos(i, j)) {
					Pos p;
					p.pi = i;
					p.pj = j;
					possible[poss_num++] = p;
				}
			}
		}
	}
	else {
		for (i = 1; i <= 8; i++) {
			for (j = 1; j <= 8; j++) {
				if (isWhitePos(i, j)) {
					Pos p;
					p.pi = i;
					p.pj = j;
					possible[poss_num++] = p;
				}
			}
		}
	}

	if(poss_num == 0)
		return false;

	srand((unsigned int)time(NULL));
	int random = (int)rand() % poss_num;

	*_a = possible[random].pi;
	*_b = possible[random].pj;

	if (putStone(_black_turn, *_a, *_b))
		return true;
	else
		return false;
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

bool isBlackPos(int _x, int _y)
{
	return true;
}

bool isWhitePos(int _x, int _y)
{
	return true;
}

void gotoxy(int _x, int _y) {
	COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

