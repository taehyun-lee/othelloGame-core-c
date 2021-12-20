#include "common.h"

int map[10][10];
#define NUMBER 10
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	init();
	int record[NUMBER][5] = { 0 };
	int target[5] = { 99,11,1,800,211031 };
	setRecord(target, NUMBER);

	return 0;
}