#define HAVE_STRUCT_TIMESPEC
#define _CRTDBG_MAP_ALLOC
/*
* 스레드 라이브러리
*/
#include <pthread.h>
#include "common.h"
int g_map[10][10];

boolean g_time_th_end = FALSE;  //  제한시간 스레드 종료 여부
boolean g_mouse_th_end = FALSE;  //  마우스 입력 스레드 종료 여부

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

void main()
{
	//  메모리 누수 체크 (디버그 모드)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*
	* 시간제한으로 턴이 종료된 경우
	* situation = "timeout"
	* 유효한 마우스 입력으로 턴이 종료된 경우
	* situation = "progress"
	*/
	char* situation = "";
	int pos[2];  //  마우스를 통해 받은 x, y좌표 값
	int time_limit = 3;  //  제한시간
	int* status_time, * status_mouse;
	pthread_t th_time_id, th_mouse_id;

	/*
	* 이 부분에 게임이 종료 될때 까지 반복되는 while문 추가
	*
	*
	*
	*
	*
	*/

	pos[0] = 0;
	pos[1] = 0;
	//  시간 체크 스레드 시작
	if (pthread_create(&th_time_id, NULL, thread_time, (void*)&time_limit) < 0) {
		perror("time thread create error:");
		exit(0);
	}
	// 유효한 마우스 입력 스레드 시작
	if (pthread_create(&th_mouse_id, NULL, thread_mouse, NULL) < 0) {
		perror("mouse thread create error:");
		exit(0);
	}

	while (1) {
		//  제한시간 초과하는 경우
		if (g_time_th_end) {
			pthread_cancel(th_mouse_id);
			pthread_join(th_time_id, (void**)&status_time);

			//  테스팅 코드 시작
			gotoxy(0, 0);
			//printf("th_time return value : %d\n", *status_time);
			printf("mouse thread end");
			//  테스팅 코드 종료

			free(status_time);
			situation = "timeout";
			break;
		}
		//  유효한 마우스 입력이 있는 경우
		if (g_mouse_th_end) {
			pthread_cancel(th_time_id);
			pthread_join(th_mouse_id, (void**)&status_mouse);
			pos[0] = ((int*)status_mouse)[0];
			pos[1] = ((int*)status_mouse)[1];

			//  테스팅 코드 시작
			gotoxy(0, 0);
			printf("x : %d, y : %d\n", status_mouse[0], status_mouse[1]);
			printf("time thread end");
			//  테스팅 코드 종료

			free(status_mouse);
			situation = "progress";
			break;
		}
	}
	g_time_th_end = FALSE;
	g_mouse_th_end = FALSE;

	if (!strcmp(situation, "timeout")) {
		//  랜덤으로 해당 턴의 돌을 배치
	}

	if (!strcmp(situation, "progress")) {
		//  테스팅 코드 시작
		gotoxy(50, 3);
		printf("x : %d, y : %d", pos[0], pos[1]);
		//  테스팅 코드 종료


		//  pos 변수를 이용하여 x, y좌표에 해당하는 위치에 돌 추가
		//  주변 돌 뒤집기
	}

	//  게임화면 출력

	/*
	* 이 부분에 게임이 종료 될때 까지 반복되는 while문 종료
	*
	*
	*
	*
	*
	*/





}
