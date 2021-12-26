#include "common.h"

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE COUT = 0;    // 콘솔 출력 장치
HANDLE CIN = 0;        // 콘솔 입력 장치


bool isPossiblePos(int _a, int _b)
{
	/*
	* <흑색 차례의 경우>
	돌의 색	first_case		결과

	빈			T			종료
	빈			F			종료
	끝			T			종료
	끝			F			종료
	흑			T			종료
	흑			F			true
	백			T			계속
	백			F			계속
	*/
	int interval[8][2] = {
		{-1,-1},
		{-1,0 },
		{-1,1 },
		{0,1 },
		{1,1 },
		{1,0 },
		{1,-1},
		{0,-1}
	};

	if (_a < 1 || _a>8 || _b < 1 || _b>8)
		return false;

	if (g_map[_a][_b] == PLAYER1 || g_map[_a][_b] == PLAYER2)
		return false;

	if (g_is_black_turn) {
		for (int i = 0; i < 8; i++) {
			bool first_case = true;
			int dx = interval[i][0];
			int dy = interval[i][1];
			while (g_map[_a + dx][_b + dy] == PLAYER1 || g_map[_a + dx][_b + dy] == PLAYER2) {
				if (g_map[_a + dx][_b + dy] == PLAYER1 && !first_case)
					return true;
				else if (g_map[_a + dx][_b + dy] == PLAYER2) {
					dx += interval[i][0];
					dy += interval[i][1];
					first_case = false;
				}
				else
					break;
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			bool first_case = true;
			int dx = interval[i][0];
			int dy = interval[i][1];
			while (g_map[_a + dx][_b + dy] == PLAYER2 || g_map[_a + dx][_b + dy] == PLAYER1) {
				if (g_map[_a + dx][_b + dy] == PLAYER2 && !first_case)
					return true;
				else if (g_map[_a + dx][_b + dy] == PLAYER1) {
					dx += interval[i][0];
					dy += interval[i][1];
					first_case = false;
				}
				else
					break;
			}
		}
	}
	return false;
}

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

bool isGameEnd()
{
	if (isTherePlacePutBlack() || isTherePlacePutWhite())
		return false;
	else
		return true;

/*
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (g_map[i][j] == EMPTY) {
				if (isPossiblePos(i, j)) {
					return false;
				}
				
				g_is_black_turn = !g_is_black_turn;
				if (isPossiblePos(i, j)) {
					g_is_black_turn = !g_is_black_turn;
					return false;
				}
				
			}

		}
	}
	return true;
*/
}

bool isTherePlacePutBlack()
{
	bool temp = g_is_black_turn;
	g_is_black_turn = true;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (g_map[i][j] == EMPTY && isPossiblePos(i, j)) {
				g_is_black_turn = temp;
				return true;
			}
		}
	}

	g_is_black_turn = temp;
	return false;
}

bool isTherePlacePutWhite()
{
	bool temp = g_is_black_turn;
	g_is_black_turn = false;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (g_map[i][j] == EMPTY && isPossiblePos(i, j)) {
				g_is_black_turn = temp;
				return true;
			}
		}
	}

	g_is_black_turn = temp;
	return false;
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

void putStone(int _a, int _b)
{
	if (g_is_black_turn)
		g_map[_a][_b] = PLAYER1;
	else
		g_map[_a][_b] = PLAYER2;
}

bool putRandomStone(int* _a, int* _b)
{
	int i, j;
	Pos possible[64];
	int poss_num = 0;
	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 8; j++) {
			if (g_map[i][j] == EMPTY && isPossiblePos(i, j)) {
				Pos p;
				p.a = i;
				p.b = j;
				possible[poss_num++] = p;
			}
		}
	}
	//  둘 곳이 없으므로 다음차례로 넘겨야 함
	if(poss_num == 0)
		return false;

	srand((unsigned int)time(NULL));
	int random = (int)rand() % poss_num;

	*_a = possible[random].a;
	*_b = possible[random].b;

	putStone(*_a, *_b);
	return true;
}

void flipStone(int _a, int _b)
{
	int interval[8][2] = {
	{-1,-1},
	{-1,0 },
	{-1,1 },
	{0,1 },
	{1,1 },
	{1,0 },
	{1,-1},
	{0,-1}
	};
	if (g_is_black_turn) {
		for (int i = 0; i < 8; i++) {
			Pos flip[10] = { 0, 0 }; // 뒤집어야 하는 돌의 좌표를 저장 할 배열, 맵의 크기로 설정
			int flip_size = 0;
			bool first_case = true;
			int dx = interval[i][0];
			int dy = interval[i][1];
			while (g_map[_a + dx][_b + dy] == PLAYER1 || g_map[_a + dx][_b + dy] == PLAYER2) {
				if (g_map[_a + dx][_b + dy] == PLAYER1 && !first_case) {
					for (int j = 0;j<flip_size; j++) {
						putStone(flip[j].a, flip[j].b);
					}
					break;
				}
				else if (g_map[_a + dx][_b + dy] == PLAYER2) {
					Pos p;
					p.a = _a + dx;
					p.b = _b + dy;
					flip[flip_size++] = p;
					dx += interval[i][0];
					dy += interval[i][1];
					first_case = false;
				}
				else
					break;
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			Pos flip[10] = { 0, 0 }; // 뒤집어야 하는 돌의 좌표를 저장 할 배열, 맵의 크기로 설정
			int flip_size = 0;
			bool first_case = true;
			int dx = interval[i][0];
			int dy = interval[i][1];
			while (g_map[_a + dx][_b + dy] == PLAYER2 || g_map[_a + dx][_b + dy] == PLAYER1) {
				if (g_map[_a + dx][_b + dy] == PLAYER2 && !first_case) {
					for (int j = 0;j<flip_size; j++) {
						putStone(flip[j].a, flip[j].b);
					}
					break;
				}
				else if (g_map[_a + dx][_b + dy] == PLAYER1) {
					Pos p;
					p.a = _a + dx;
					p.b = _b + dy;
					flip[flip_size++] = p;
					dx += interval[i][0];
					dy += interval[i][1];
					first_case = false;
				}
				else
					break;
			}
		}
	}

}

void getXY(int* _x, int* _y)
{
	int* status_mouse;
	pthread_t th_mouse_id;

	// 유효한 마우스 입력 스레드 시작
	if (pthread_create(&th_mouse_id, NULL, threadMouse, NULL) < 0) {
		perror("mouse thread create error:");
		exit(0);
	}

	pthread_join(th_mouse_id, (void**)&status_mouse);
	*_x = ((int*)status_mouse)[0];
	*_y = ((int*)status_mouse)[1];
	free(status_mouse);

}

bool coordToIndex(int _x, int _y, int* _a, int* _b)
{
	int i, j;
	int base_x = 18, base_y = 9;
	int dx = 8, dy = 4;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (_x >= base_x + i * dx && _x < base_x + (i + 1) * dx && _y >= base_y + j * dy && _y < base_y - 1 + (j + 1) * dy) {
				*_a = j + 1;
				*_b = i + 1;
				return true;
			}
		}
	}

	return false;
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
	
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	g_time_th_end = false;
	
	int limit_time = 30;
	while (limit_time != -1) {
		gotoxy(43, 2);
		Sleep(1000);
		printf("limitTime : %2ds", limit_time--);
	}
	g_time_th_end = true;
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
		g_mouse_th_end = false;
		if (beInput())
		{
			if (getInput(&key, &pos) != 0)
			{
				MOUSE_EVENT;
				x = pos.X;    // 마우스클릭값이 x,y변수에 저장되도록함
				y = pos.Y;
				/*retval = malloc(sizeof(int) * 2);
				if (retval != NULL) {
					retval[0] = x;
					retval[1] = y;
					g_mouse_th_end = TRUE;
					return (void*)retval;
				}*/
				static Pos p;
				p.a = x;
				p.b = y;
				g_mouse_th_end = true;
				return &p;
			}
		}
	}
}

bool isBtnExit(int _x, int _y)
{
	return false;
}

int whichBtnSelect(int _x, int _y)
{
	return 0;
}

void screenClear()
{
	COORD Coor = { 2, 2 };
	DWORD dw;

	//  화면 지우기	
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 10*2, Coor, &dw);
	Coor.X = 3;
	Coor.Y = 3;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 10*2, Coor, &dw);

}
