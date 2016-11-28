#ifndef _RANK_FILE_H_
#define _RANK_FILE_H_

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#include "global.h"
#include "model.h"

///////////////////////////////////////////////////////
// º¯ÊıÉùÃ÷

int WriteRanklist(Rank*, const int);

int ReadRanklist(Rank* psrRanks, const int nMaxSize);

Rank ParseRank(char*);

int GetRanklistCount();

///////////////////////////////////////////////////////
#endif
