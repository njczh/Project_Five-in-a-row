#ifndef _GAME_FILE_H_
#define _GAME_FILE_H_

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#include "global.h"

void WriteGameInfo(int nStep, int aChessStatus[MAX][MAX]);

void ReadGameInfo(int *nStep, int aChessStatus[MAX][MAX]);

#endif

