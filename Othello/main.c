#include "common.h"

int map[10][10];
int g_playtime;
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
	printf("hello");
	return 0;
}