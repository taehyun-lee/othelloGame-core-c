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
	printf("┏");
	for (i = 0; i < width; i++) {
		printf("━");
	}
	printf("┓");
	int line[MENUNUM];
	for (i = 0; i < MENUNUM; i++) {
		for (j = 0; j < 5; j++) {
			gotoxy(margin_left, base_line++);
			printf("┃");
			for (k = 0; k < width; k++)
				printf(" ");
			printf("┃");
		}
		line[i] = base_line - 3;
		gotoxy(margin_left, base_line++);
		printf("┣");
		for (j = 0; j < width; j++)
			printf("━");
		printf("┫");
	}
	gotoxy(margin_left, --base_line);
	printf("┗");
	for (int i = 0; i < width; i++)
		printf("━");
	printf("┛");
	
	gotoxy(margin_left + 13, line[0]);
	printf("N E W   G A M E");

	gotoxy(margin_left + 13, line[1]);
	printf("C O N T I N U E");

	gotoxy(margin_left + 13, line[2]);
	printf("  R E C O R D");

	gotoxy(margin_left + 13, line[3]);
	printf("    E X I T");

	gotoxy(0, 45);
}

void printMap()
{
	int i, j, k;
	int margin_top = 8;
	int margin_left = 17;
	int base_line = margin_top;

	gotoxy(margin_left, base_line++);
	printf("┏");
	for (i = 0; i < MAPSIZE; i++)
		printf("━━━━━━━┳");
	printf("\b┓");

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < 3; j++) {
			gotoxy(margin_left, base_line++);
			printf("┃");
			for (k = 0; k < MAPSIZE; k++)
				printf("       ┃");
		}
		gotoxy(margin_left, base_line++);
		printf("┣");
		for (j = 0; j < MAPSIZE; j++) {
			printf("━━━━━━━╋");
		}
		printf("\b┫");
	}
	gotoxy(margin_left, --base_line);
	printf("┗");
	for (i = 0; i < MAPSIZE; i++)
		printf("━━━━━━━┻");
	printf("\b┛");

	gotoxy(0, 45);
}

void printStone()
{
	int base_x = 21;
	int base_y = 10;
	int dx = 8;
	int dy = 4;
	int i, j;

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) {
			gotoxy(base_x + j * dx, base_y + i * dy);
			if (g_map[i + 1][j + 1] == 1)
				printf("●");
			else if (g_map[i + 1][j + 1] == 2)
				printf("○");
			else if (g_map[i + 1][j + 1] == 0)
				continue;
			else
				printf("＃");  //  avoid case
		}
	}
	gotoxy(0, 45);
}

void gotoxy(int _x, int _y) {
	COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}