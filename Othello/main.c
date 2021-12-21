#include "common.h"

int map[10][10];

int main() {
	
	init();

	int x = 78;
	int y = 10;

	printMap();
	gotoxy(x,y);
	printf("*");

	if (convertToIndex(&x, &y)) {
		gotoxy(0, 45);
		printf("i = %d , j = %d", x, y);
	}
	else {
		gotoxy(0, 45);
		printf("error");
	}


	return 0;
}