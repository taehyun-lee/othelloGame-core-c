#include "common.h"

int g_map[10][10];
int g_playtime;
bool g_time_th_end;  //  제한시간 스레드 종료 여부
bool g_mouse_th_end;  //  마우스 입력 스레드 종료 여부
bool g_is_black_turn;  // 현재 플레이어 차례 확인


void main()
{
	//  메모리 누수 체크 (디버그 모드)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	init();
	//gameInit();
	//getBackup();
	//printMap();

	//int x = 8;
	//int y = 5;

	//printStone();
	//if (isTherePlacePutBlack()) {
	//	gotoxy(0, 45);
	//	//printf("END!!");
	//	printf("yes");
	//}
	//else {
	//	gotoxy(0, 45);
	//	//printf("NOT END...");
	//	printf("no");

	//}
	getBackup();
	gamePrompt(false);

}
