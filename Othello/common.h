#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
/*
* 메모리 누수 체크를 위한 include
*/
#include <stdlib.h>
#include <crtdbg.h>

#include "game.h"
#include "logic.h"
#include "print.h"
#include "txtfile.h"

extern int g_map[10][10];
extern bool g_time_th_end;
extern bool g_mouse_th_end;
