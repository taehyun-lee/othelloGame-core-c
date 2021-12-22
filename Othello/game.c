#include "common.h"

void init()
{
	system(" mode  con lines=50   cols=100 ");  //  콘솔창 크기 가로 100 세로 50
	system("chcp 949<nul");
	gotoxy(0,0);
	printf("                        ");
	gotoxy(0,0);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0 || j == 0 || i == 9 || j == 9)
				g_map[i][j] = -1;
			else
				g_map[i][j] = 0;
		}
	}
}
