#include "common.h"
#include "logic.h"

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;

boolean isClick(time_t _start) {
    while (1)
    {
        time_t end = clock();
        if ((float)(end - _start) > 30.0)
            return ;        
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // 콘솔창 입력을 받아들임.
        if (rec.EventType == MOUSE_EVENT) {// 마우스 이벤트일 경우

            if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) { // 좌측 버튼이 클릭되었을 경우
                return 1;
                break;
                }
            }
        }
    }
