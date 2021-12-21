#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "game.h"
#include "logic.h"
#include "print.h"
#include "txtfile.h"

//  fopen_s 오류 무시
#pragma warning(disable:4996)

extern int map[10][10];