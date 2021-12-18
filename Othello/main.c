#include "common.h"

int map[10][10];
#define NUMBER 10
int main() {

	init();

	//printMainmenu();

	int record[NUMBER][5] = { 0 };

	if (!getRecord(record)) {
		printf("empty");
	}
	else {
		for (int i = 0; i < NUMBER; i++) {
			for (int j = 0; j < 5; j++) {
				printf("%d\t", record[i][j]);
			}
			printf("\n");
		}

	}

	return 0;
}