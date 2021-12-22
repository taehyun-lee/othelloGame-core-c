#include "common.h"

INPUT_RECORD rec;
DWORD dwNOER;
//HANDLE CIN = 0;

HANDLE COUT = 0;    // 콘솔 출력 장치
HANDLE CIN = 0;        // 콘솔 입력 장치

boolean isClick(time_t _start) {
	//while (1)
	//{
	//	time_t end = clock();
	//	if ((float)(end - _start) > 30.0)
	//		return;
	//	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // 콘솔창 입력을 받아들임.
	//	if (rec.EventType == MOUSE_EVENT) {// 마우스 이벤트일 경우

	//		if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) { // 좌측 버튼이 클릭되었을 경우
	//			return 1;
	//			break;
	//		}
	//	}
	//}
	return 0;
}

int be_input()
{
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CIN, &input_record, 1, &input_count);
	return input_count;
}


int get_input(WORD* vkey, COORD* pos)
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


void* thread_time(void* avg) {
	int limit_time = *((int*)avg);
	while (limit_time != -1) {
		gotoxy(10, 10);
		Sleep(1000);
		printf("limitTime : %2ds", limit_time--);
	}
	g_time_th_end = TRUE;
	//int* retval = (int*)malloc(sizeof(int));
	//if (retval != NULL) {
	//	*retval = -1;
	//}
	//return (void*)retval;
	return NULL;
}


void* thread_mouse(void* avg) {
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
		if (be_input())
		{
			if (get_input(&key, &pos) != 0)
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
