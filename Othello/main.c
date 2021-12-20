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
	int target[5] = { 99,11,1,800,211031 };
	//  setRecord test
	//setRecord(target, NUMBER);

	//  getRecord test
	//if (getRecord(record, NUMBER) == true) {
	//	for (int i = 0; i < NUMBER; i++) {
	//		for (int j = 0; j < 5; j++) {
	//			printf("%d ", record[i][j]);
	//		}
	//		printf("\n");
	//	}
	//}
	//else {
	//	printf("empty");
	//}

	//  getBackup test
	//if (getBackup(map)) {
	//	for (int i = 0; i < 10; i++) {
	//		for (int j = 0; j < 10; j++) {
	//			printf("%d ", map[i][j]);
	//		}
	//		printf("\n");
	//	}
	//}
	//else {
	//	printf("empty");
	//}

	//  setbackup test
	setBackup(testmap);
	return 0;
}