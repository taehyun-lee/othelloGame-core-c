#include "common.h"


void printMainmenu()
{
	int width = 38;
	int margin_left = 30;
	int margin_top = 10;
	int base_line = margin_top;
	int i, j, k;

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
	int margin_top = 8;
	int margin_left = 17;
	int base_line = margin_top;
	int i, j, k;

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
			if (map[i + 1][j + 1] == 1)
				printf("●");
			else if (map[i + 1][j + 1] == 2)
				printf("○");
			else if (map[i + 1][j + 1] == 0)
				continue;
			else
				printf("＃");  //  avoid case
		}
	}
	gotoxy(0, 45);
}

void printEndMsg(int _playtime, int _p1_score, int _p2_score)
{
	int margin_top = 18;
	int margin_left = 35;
	int base_line = margin_top;
	int width = 30, height = 15;
	int i, j;

	for (i = 0; i < height; i++) {
		gotoxy(margin_left, base_line++);
		for (j = 0; j < width; j++)
			printf(" ");
	}
	base_line = margin_top;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(margin_left, base_line++);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	
	for (i = 0; i < height - 2; i++) {
		gotoxy(margin_left, base_line++);
		printf("┃                            ┃");
	}

	gotoxy(margin_left, base_line++);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	
	char* comment;
	if (_p1_score > _p2_score)
		comment = "!!Black Win!!";
	else if (_p1_score < _p2_score)
		comment = "!!White win!!";
	else
		comment = "~~~~~Draw~~~~";

	base_line = margin_top;
	gotoxy(margin_left + 8, base_line + 4);
	printf("%s", comment);
	
	gotoxy(margin_left + 8, base_line + 8);
	if (_playtime >= 60 * 60) 
		printf("playtime : %dm %ds", 59, 59);
	else
		printf("playtime : %dm %ds", _playtime / 60, _playtime % 60);


	gotoxy(margin_left + 8, base_line + 10);
	printf("score : %d : %d", _p1_score, _p2_score);

	gotoxy(0, 45);
}

void printSave()
{
	int margin_top = 14;
	int margin_left = 29;
	int base_line = margin_top, btn_base_line;
	int width = 40, height = 20;
	int i;

	gotoxy(margin_left, base_line++);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	for (i = 0; i < height - 2; i++) {
		gotoxy(margin_left, base_line++);
		printf("┃                                      ┃");
	}
	gotoxy(margin_left, base_line);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(margin_left + 10, margin_top + 5);
	printf("Do yout want to save");
	gotoxy(margin_left + 10, margin_top + 7);
	printf("the current game?");

	btn_base_line = base_line - 7;
	gotoxy(margin_left + 7, btn_base_line++);
	printf("┏━━━━━━━━━┓");
	gotoxy(margin_left + 7, btn_base_line++);
	printf("┃   N  O  ┃");
	gotoxy(margin_left + 7, btn_base_line++);
	printf("┗━━━━━━━━━┛");
	
	btn_base_line = base_line - 7;
	gotoxy(margin_left + 22, btn_base_line++);
	printf("┏━━━━━━━━━┓");
	gotoxy(margin_left + 22, btn_base_line++);
	printf("┃  Y E S  ┃");
	gotoxy(margin_left + 22, btn_base_line++);
	printf("┗━━━━━━━━━┛");

	gotoxy(0, 45);
}

void printSubmenu(boolean _black_turn, int _p1_score, int _p2_score) {
	
	int margin_left = 8;
	int margin_top = 8;

	gotoxy(margin_left, CONSOLE_HEIGHT / 2 ); // 흑 스코어 출력
	printf("● %d",_p1_score);
	
	gotoxy(CONSOLE_WIDTH - margin_left, CONSOLE_HEIGHT / 2 ); // 백 스코어 출력
	printf("○ %d",_p2_score);
	
	gotoxy(CONSOLE_WIDTH / 2 - 5, CONSOLE_HEIGHT - margin_top ); // 현재 진행중인 플레이어 출력
		if (_black_turn)
			printf("Black Turn");
		else
			printf("White Turn");

	gotoxy(0, 45);
}

void gotoxy(int _x, int _y) {
	COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}