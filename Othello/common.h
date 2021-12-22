#pragma once
#define HAVE_STRUCT_TIMESPEC
#include <crtdbg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <pthread.h>

#include "game.h"
#include "logic.h"
#include "print.h"
#include "txtfile.h"

//  fopen_s 오류 무시
#pragma warning(disable:4996)

extern int g_map[10][10];
extern int g_playtime;
extern bool g_time_th_end;
extern bool g_mouse_th_end;

//#if !define(HAVE_STRUCT_TIMESPEC)
//#define HAVE_STRUCT_TIMESPEC
//#if !define(_TIMESPEC_DEFINED)
//#define _TIMESPEC_DEFINED
//#if defined(_MSC_VER) && _MSC_VER >= 1900 && defined(_CRT_NO_TIME_T)



#define _CRTDBG_MAP_ALLOC
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2
#define DRAW 3
#define EDGE -1

