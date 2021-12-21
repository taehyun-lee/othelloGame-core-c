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

int whoseWin()
{
	int x, y;
	getScore(&x, &y);

	if (x > y)
		return 1;
	else if (x < y)
		return 2;
	else
		return -1;
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

void gotoxy(int _x, int _y) {
	COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

