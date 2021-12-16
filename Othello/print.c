#include "common.h"


void printMainmenu()
{
	int i, j, k;
	int width = 38;
	int margin_left = 30;
	int margin_top = 10;
	int base_line = margin_top;

	gotoxy(margin_left + 10, margin_top - 2);
	printf("<< O T H E L L O >>");

	gotoxy(margin_left, base_line++);
	printf("┌");
	for (i = 0; i < width; i++) {
		printf("─");
	}
	printf("┐");
	int line[MENUNUM];
	for (i = 0; i < MENUNUM; i++) {
		for (j = 0; j < 5; j++) {
			gotoxy(margin_left, base_line++);
			printf("│");
			for (k = 0; k < width; k++)
				printf(" ");
			printf("│");
		}
		line[i] = base_line - 3;
		gotoxy(margin_left, base_line++);
		printf("├");
		for (j = 0; j < width; j++)
			printf("─");
		printf("┤");
	}
	gotoxy(margin_left, --base_line);
	printf("└");
	for (int i = 0; i < width; i++)
		printf("─");
	printf("┘");
	
	//printf("%d", line[0]);
	gotoxy(margin_left + 13, line[0]);
	printf("N E W   G A M E");

	gotoxy(margin_left + 13, line[1]);
	printf("C O N T I N U E");

	gotoxy(margin_left + 13, line[2]);
	printf("  R E C O R D");

	gotoxy(margin_left + 13, line[3]);
	printf("    E X I T");

	gotoxy(0, 40);
}

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