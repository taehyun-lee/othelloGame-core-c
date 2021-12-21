#include "common.h"

int map[10][10];
#define NUMBER 10
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	init();
	int record[NUMBER][5] = { 0, };
	int testmap[10][10] = { {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{-1, 1 ,1, 0, 2, 0, 1, 0, 1, -1},
{-1, 1, 0, 2, 1, 2, 0, 1, 2 ,-1},
{-1, 1, 2, 2, 1, 1, 0, 0, 1 ,-1},
{-1, 1, 2, 1, 2, 0, 0, 2, 1 ,-1},
{-1, 1, 1, 0, 2, 0, 1, 0, 1 ,-1},
{-1, 1, 0, 2, 1, 2, 0, 1, 2 ,-1},
{-1, 1, 2, 2, 1, 1, 1, 0, 0 ,-1},
{-1, 1, 1, 2, 2, 0, 1, 2, 1 ,-1},
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	};
	/*
	int x, y;
	getBackup(map);
	getScore(&x, &y);

	printf("p1 : %d, p2 : %d\n", x, y);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%2d  ", map[i][j]);
		}
		printf("\n");
	}
	printf("whoose win : %d", whoseWin());
	*/
	printMap();
	printSubmenu(true,12,54);
	return 0;
}