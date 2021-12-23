#include "common.h"

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE COUT = 0;    // 콘솔 출력 장치
HANDLE CIN = 0;        // 콘솔 입력 장치

void getScore(int* _p1, int* _p2)
{
	int i, j;
	*_p1 = 0;
	*_p2 = 0;
	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			if (g_map[i][j] == PLAYER1)
				(*_p1)++;
			else if (g_map[i][j] == PLAYER2)
				(*_p2)++;
		}
	}
}

int whoseWin()
{
	int x, y;
	getScore(&x, &y);

	if (x > y)
		return PLAYER1;
	else if (x < y)
		return PLAYER2;
	else
		return DRAW;
}

bool putStone(bool _black_turn, int _a, int _b)
{
	if (g_map[_a][_b] != EMPTY)
		return false;

	if (_black_turn)
		g_map[_a][_b] = PLAYER1;
	else
		g_map[_a][_b] = PLAYER2;
	return true;
}

bool putRandomStone(bool _black_turn, int* _a, int* _b)
{
	int i, j;

	Pos possible[64];
	int poss_num = 0;

	if (_black_turn) {
		for (i = 1; i <= 8; i++) {
			for (j = 1; j <= 8; j++) {
				if (isBlackPos(i, j)) {
					Pos p;
					p.a = i;
					p.b = j;
					possible[poss_num++] = p;
				}
			}
		}
	}
	else {
		for (i = 1; i <= 8; i++) {
			for (j = 1; j <= 8; j++) {
				if (isWhitePos(i, j)) {
					Pos p;
					p.a = i;
					p.b = j;
					possible[poss_num++] = p;
				}
			}
		}
	}

	if(poss_num == 0)
		return false;

	srand((unsigned int)time(NULL));
	int random = (int)rand() % poss_num;

	*_a = possible[random].a;
	*_b = possible[random].b;

	if (putStone(_black_turn, *_a, *_b))
		return true;
	else
		return false;
}

bool coordToIndex(int _x, int _y, int* _a, int* _b)
{
	int i, j;
	int base_x = 18, base_y = 9;
	int dx = 8, dy = 4;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (_x >= base_x + i * dx && _x < base_x + (i + 1) * dx && _y >= base_y + j * dy && _y < base_y - 1 + (j + 1) * dy) {
				*_a = j;
				*_b = i;
				return true;
			}
		}
	}

	return false;
}

bool isBlackPos(int _x, int _y)
{
	return true;
}

bool isWhitePos(int _x, int _y)
{
	return true;
}

void gotoxy(int _x, int _y) {
	COORD pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int beInput()
{
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CIN, &input_record, 1, &input_count);
	return input_count;
}

int getInput(WORD* vkey, COORD* pos)
{
	INPUT_RECORD input_record;
	DWORD input_count;

	ReadConsoleInput(CIN, &input_record, 1, &input_count);
	switch (input_record.EventType) {
	case MOUSE_EVENT:
		if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			GetConsoleScreenBufferInfo(COUT, &csbi);

			*pos = input_record.Event.MouseEvent.dwMousePosition;
			pos->X -= csbi.srWindow.Left;
			pos->Y -= csbi.srWindow.Top;

			return MOUSE_EVENT;
		}
		break;
	}
	//    FlushConsoleInputBuffer(CIN);
	return 0;
}

void* threadTime(void* avg) {
	int limit_time = *((int*)avg);
	while (limit_time != -1) {
		gotoxy(10, 10);
		Sleep(1000);
		printf("limitTime : %2ds", limit_time--);
	}
	g_time_th_end = TRUE;
	return NULL;
}

void* threadMouse(void* avg) {
	DWORD mode;
	WORD key;
	COORD pos;

	//int event; // 어디서 사용하는지 불명확       // 마우스 이벤트에 이용 
	int x;            // 마우스의 x좌표 저장소
	int y;            // 마우스의 y좌표 저장소
	int* retval; // 1차원 동적 배열 x,y 좌표

	CIN = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);

	// 마우스 활성화
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
	int clk_s = clock();
	while (1)
	{
		if (beInput())
		{
			if (getInput(&key, &pos) != 0)
			{
				MOUSE_EVENT;
				x = pos.X;    // 마우스클릭값이 x,y변수에 저장되도록함
				y = pos.Y;
				// x, y 가 유효한지 판단하는 함수 추가
				if (1) {  //  위의 함수에 값이 참이라면 좌표값 반환
					retval = (int*)malloc(sizeof(int) * 2);
					retval[0] = x;
					retval[1] = y;
					g_mouse_th_end = TRUE;
					return (void*)retval;
				}
			}
		}
	}
}
