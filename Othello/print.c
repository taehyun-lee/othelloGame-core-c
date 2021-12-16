#include "common.h"


void printMap()
{
	int i, j, k;
	int margin_top = 8;
	int margin_bottom = 9;
	int margin_left = 17;
	int margin_right = 18;
	int base_line = margin_top;

	gotoxy(margin_left, base_line++);
	printf("┌");
	for (i = 0; i < MAPSIZE; i++)
		printf("───────┬");
	printf("\b┐");

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < 3; j++) {
			gotoxy(margin_left, base_line++);
			printf("│");
			for (k = 0; k < MAPSIZE; k++)
				printf("       │");
		}
		gotoxy(margin_left, base_line++);
		printf("├");
		for (j = 0; j < MAPSIZE; j++) {
			printf("───────┼");
		}
		printf("\b┤");
	}
	gotoxy(margin_left, --base_line);
	printf("└");
	for (i = 0; i < MAPSIZE; i++)
		printf("───────┴");
	printf("\b┘");
}

void gotoxy(int _x, int _y) {
	COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}