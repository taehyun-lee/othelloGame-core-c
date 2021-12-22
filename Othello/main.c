#define HAVE_STRUCT_TIMESPEC
#define _CRTDBG_MAP_ALLOC
#include <pthread.h>
#include "common.h"
int g_map[10][10];
bool g_time_th_end = FALSE;  //  제한시간 스레드 종료 여부
bool g_mouse_th_end = FALSE;  //  마우스 입력 스레드 종료 여부

void main()
{
	//  메모리 누수 체크 (디버그 모드)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	printf("hi");

}
