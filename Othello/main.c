﻿#include "common.h"
#include <pthread.h>
int map[10][10];
HANDLE COUT = 0;    // 콘솔 출력 장치
HANDLE CIN = 0;        // 콘솔 입력 장치

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

void* limit_time_func(void* data) {
    static int retval = 99;
    int count = *((int*)data);
    int i = 0;
    int start_clk = clock();
    while (1) {
        if (clock() - start_clk == 10) {
            pthread_ex
        }
    }
}
void main()
{
    DWORD mode;
    WORD key;
    COORD pos;

    int event;        // 마우스 이벤트에 이용
    int x;            // 마우스의 x좌표 저장소
    int y;            // 마우스의 y좌표 저장소

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
                gotoxy(x, y);
                printf("*");
            }
        }

    }
}


//출처: https://www.crocus.co.kr/4 [Crocus]