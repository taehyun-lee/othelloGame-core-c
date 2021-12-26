#include "common.h"

void init()
{
	system(" mode  con lines=50   cols=100 ");  //  콘솔창 크기 가로 100 세로 50
	system("chcp 949<nul");
	gotoxy(0,0);
	printf("                        ");
	gotoxy(0,0);
}

void gameInit()
{
	g_playtime = 0;
	g_time_th_end = false;
	g_mouse_th_end = false;
	g_is_black_turn = false;  //  게임 프롬프트 시작할 때 true로 바꿔주고 시작

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0 || j == 0 || i == 9 || j == 9)
				g_map[i][j] = -1;
			else
				g_map[i][j] = 0;
		}
	}
	g_map[4][4] = 2;
	g_map[5][5] = 2;
	g_map[4][5] = 1;
	g_map[5][4] = 1;
}

void start()
{
	int x, y;
	printMainmenu();
	while (true) {
		int choice;
		getXY(&x, &y);
		choice = whichBtnSelect(x, y);
		switch (choice)
		{
		case -1:
			break;
		case 1:
			gamePrompt(true);
			break;
		case 2:
			if (getBackup()) {
				gamePrompt(false);
			}
			break;
		case 3:
			recordPrompt();
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}
void gamePrompt(bool _is_newgame)
{
	int x = 0, y = 0;
	int a = 0, b = 0;
	int p1_score = 0, p2_score = 0;
	char* situation = "";
	int* status_time, * status_mouse;
	pthread_t th_time_id, th_mouse_id;

	if (_is_newgame)
		gameInit();

	//  플레이 시간 체크 시작
	time_t start_clock = clock();
	
	while (!isGameEnd()) {
		p1_score = 0;
		p2_score = 0;
		COORD Coor = { 0, 0 };
		DWORD dw;
		//  화면 지우기	
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 50, Coor, &dw);
		g_is_black_turn = !g_is_black_turn;
		printMap();
		getScore(&p1_score, &p2_score);
		printSubmenu(g_is_black_turn, p1_score, p2_score);
		printStone();
		
		//  모든 빈칸에 대해서 흑은 둘곳이 없지만 백을 둘 곳이 있을때
		//  흑의 차례인 경우에 대한 처리 -> 둘 곳이 없다는 메시지 출력후 차례를 넘긴다
		if (g_is_black_turn && !isTherePlacePutBlack()) {
			gotoxy(0, 0);
			printf("There's no place to put BLACK stones.");
			gotoxy(0, 1);
			printf("Turn Over");
			Sleep(1000);
			continue;
		}
		else if (!g_is_black_turn && !isTherePlacePutWhite()) {
			gotoxy(0, 0);
			printf("There's no place to put WHITE stones.");
			gotoxy(0, 1);
			printf("Turn Over");
			Sleep(1000);
			continue;
		}

		// 유효한 마우스 입력 스레드 시작
		if (pthread_create(&th_mouse_id, NULL, threadMouse, NULL) < 0) {
			perror("mouse thread create error:");
			exit(0);
		}
		//  시간 체크 스레드 시작
		if (pthread_create(&th_time_id, NULL, threadTime, NULL) < 0) {
			perror("time thread create error:");
			exit(0);
		}

		while (true) {
			//  제한시간 초과하는 경우
			if (g_time_th_end) {
				g_time_th_end = false;
				pthread_cancel(th_mouse_id);
				pthread_join(th_time_id, (void**)&status_time);
				//free(status_time);  메모리 해제할 것이 없음
				situation = "timeout";
				break;
			}
			//  유효한 마우스 입력이 있는 경우
			if (g_mouse_th_end) {
				g_mouse_th_end = false;
				pthread_join(th_mouse_id, (void**)&status_mouse);
				Pos* temp;
				temp = (Pos*)status_mouse;
				x = temp->a;
				y = temp->b;
				
				//  나가기 버튼이라면
				if (isBtnExit(x, y)) {
					pthread_cancel(th_time_id);
					situation = "exit";
					break;
				}

				// 판 안에 없다면
				if (!coordToIndex(x, y, &a, &b)) {
					if (pthread_create(&th_mouse_id, NULL, threadMouse, NULL) < 0) {
						perror("mouse thread create error:");
						exit(0);
					}
					continue;
				}
				else if (isPossiblePos(a, b)) {
					pthread_cancel(th_time_id);
					
					situation = "progress";
					break;
				}
				else {
					if (pthread_create(&th_mouse_id, NULL, threadMouse, NULL) < 0) {
						perror("mouse thread create error:");
						exit(0);
					}
					continue;

				}

			}

		}
		if (strcmp(situation, "timeout") == 0) {
			putRandomStone(&a, &b);
			flipStone(a, b);
			printSpecificStone(a, b);
			gotoxy(0, 0);
			printf("The position of the stone has been randomly selected.");
			Sleep(2000);
		}
		else if (strcmp(situation, "progress") == 0) {
			putStone(a, b);
			flipStone(a, b);
		}
		else if (strcmp(situation, "exit") == 0) {
			savePrompt();
			return;
		}
		else {
		}
		
	}

	printStone();
	getScore(&p1_score, &p2_score);

	printSubmenu(!g_is_black_turn, p1_score, p2_score);
	time_t end_clock = clock();

	g_playtime = g_playtime + (end_clock - start_clock)/1000;

	endPrompt();
}

void savePrompt()
{
}

void recordPrompt()
{
}

void endPrompt()
{
	int p1_score = 0, p2_score = 0;
	getScore(&p1_score, &p2_score);
	printEndMsg(p1_score, p2_score);

	//  마우스 입력 대기 ok버튼 클릭 할 경우 save프롬프트로 이동
}
