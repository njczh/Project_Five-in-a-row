#include "game_service.h"
#include "global.h"
#include <windows.h>

int AnChessStatus[MAX][MAX];

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InitStatus()
{
	//行号与列号索引值
	int i, j;

	// 初始化状态值，使用双循环遍历二维数组
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			AnChessStatus[i][j] = STATUS_BLANK;
}

int GetStatus(const int nRow, const int nCol)
{
	return AnChessStatus[nRow][nCol];
}

void SetStatus(const int nRow, const int nCol,int nStatus)
{
	AnChessStatus[nRow][nCol] = nStatus;
}

void InputPoint(int * pnRow, int * pnCol, const int nColor)
{
	char acPoint[8];					// 用来获得用户输入
	int nStatus = STATUS_BLANK;			// 坐标状态，初始化为空
	int legal = 1;
	
	do
	{
		gotoxy(17,24);
		//以此标识，提示用户的输入
		printf("==========================================\n");
		//根据执子方，提示用户输入坐标
		if (nColor == 0)					// 黑方执子
		{
			gotoxy(20, 25);
			printf("黑子●下，请输入坐标编号（如：A1）：");
		}
		else if (nColor == 1)				// 白方执子
		{
			gotoxy(20, 25);
			printf("白子○下，请输入坐标编号（如：A1）：");
		}

		// 获得用户输入的坐标
		//getchar();
		fgets(acPoint, 8, stdin);

		*pnCol = toupper(acPoint[0]) - 'A';	// 将字符转换为大写英文字母,对应二维数组的第一个下标为0
		*pnRow = atoi(&acPoint[1]) - 1;		// 字符串的第二个字母后为数字，使用atoi函数进行转换

		// 判断输入的行号和列号是否有效
		if (*pnRow < 0 || *pnRow>MAX-1 || *pnCol < 0 || *pnCol >MAX-1)
		{
			legal = 0;						// 非法输入
			gotoxy(32, 26);
			printf("【落子失败】");
			gotoxy(26, 27);
			printf("坐标不存在！请确认输入！\n");
			continue;
		}

		// 获得坐标点的状态值
		nStatus = GetStatus(*pnRow, *pnCol);

		//判断状态
		if (nStatus != STATUS_BLANK)		// 当状态不为空是，不可落子
		{
			legal = 0;						// 非法输入
			// 当前位置已经存在棋子，提示用户
			gotoxy(32, 26);
			printf("【落子失败】");
			gotoxy(26, 27);
			printf("%02d行%c列已有棋子！不可落子！\n", *pnCol+1, *pnRow+'A');
			continue;
		}

		// 落子坐标有效，且该坐标状态为BLANK，即为合法位置
		legal = 1;							// 标记坐标合法

	} while (legal==0);						// 输入非法，需要重新落子

}

void PrintBound()
{
	int i;
	gotoxy(13, 2);
	printf("╔");
	for ( i = 0; i < 30; i++)
	{
		printf("═");
	}
	printf("╗");
	for ( i = 0; i < 25; i++)
	{
		gotoxy(13, 3 + i);
		printf("║");
		gotoxy(75, 3 + i);
		printf("║");
	}
	gotoxy(13, 28);
	printf("╚");
	for (i = 0; i < 30; i++)
	{
		printf("═");
	}
	gotoxy(75, 28);
	printf("╝");
	
	
}

void PrintPrompt()
{
	gotoxy(28, 12);
	printf("╔════════╗");
	gotoxy(28, 13);
	printf("║按任意键开始游戏║");
	gotoxy(28, 14);
	printf("╚════════╝");
	gotoxy(1, 1);
	_getch();
	system("cls");
}

void PrintChess()
{
	int nStatus;
	int i;

	system("cls");

	// 输出棋盘列号
	char cA = 'A';
	printf("\n\n\n\t\t       ");
	for (i = 0; i < MAX; i++)
		printf("%C ", cA + i);
	printf("\n");

	//输出棋盘上沿
	printf("\t\t    ┏");
	for (i = 0; i < MAX; i++)
		printf("┳");
	printf("┓\n");

	// 输出棋盘
	for (int row = 0; row < MAX; row++)
	{
		for (int line = -1; line < MAX; line++)
		{
			if (line == -1)
			{
				// 输出棋盘左边界
				printf("\t\t  %02d┣", row + 1);
				continue;
			}

			// 获得坐标状态
			nStatus = GetStatus(row, line);
			// 根据不同的状态值，绘制不同的图标
			
			if (nStatus == STATUS_BLANK)// 此处为空
			{
				printf(CHESS_BLANK);
			}
			else if (nStatus == STATUS_WHITE)// 此处为白子
			{
				printf(CHESS_WHITE);
			}
			else if (nStatus == STATUS_BLACK)// 此处为黑子 
			{
				printf(CHESS_BLACK);
			}
		} // for (int line = -1; line < MAX; line++)
		printf("┫%02d\n", row + 1);
	} // for (int row = 0; row < MAX; row++)

	//输出棋盘下沿
	printf("\t\t    ┗");
	for (i = 0; i < MAX; i++)
		printf("┻");
	printf("┛\n");

	// 输出棋盘列号(下)
	cA = 'A';
	printf("\t\t       ");
	for (i = 0; i < MAX; i++)
		printf("%C ", cA + i);
	printf("\n");
}

void PlayGame()
{
	int nRow = -1;						// 行索引号
	int nCol = -1;						// 列索引号
	int nStep = 0;						// 下子的步数
	int nResult;

	// 初始化游戏数据
	InitStatus();

	// 绘制棋盘
	PrintChess();
	//PrintBound();

	// 输出开始提示
	PrintPrompt();

	// 绘制棋盘
	PrintChess();
	//PrintBound();


	//开始下棋，使用do…while至少先落一子，再进行检查是否获胜
	do {
		// 获得用户下子坐标
		InputPoint(&nRow, &nCol, nStep % 2);

		// 设置坐标点状态
		SetStatus(nRow, nCol, nStep % 2);

		// 更新棋盘
		PrintChess();

		//步数增加
		nStep++;

		// 判断棋局
		nResult = JudgeGame(nRow, nCol);
	} while (nResult == JUDGE_CONTINUE);	// 循环落子，当获胜时，则结束循环

	if (nResult == JUDGE_WIN)
	{
		PrintWinner((nStep - 1) % 2);	// 输出胜利信息
	}
	else if (nResult == JUDGE_DRAW)		// 输出和棋信息
	{
		PrintDraw();
	}
	
}

int JudgeDraw()
{
	int i, j;
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			if (AnChessStatus[i][j] == STATUS_BLANK)
				return FALSE;
	return TRUE;
	return 0;
}

int JudgeGame(const int nRow, const int nCol)
{
	// 优先判断是否得胜
	// 计数器，用来记录连续相同的棋子数
	int nCount;	

	// 获取落子的标准状态,用于判断
	const int STANDARD = AnChessStatus[nRow][nCol];

	// 横向判断
	nCount = JudgeHorizontal(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 纵向判断
	nCount = JudgeVertical(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 对角线判断I（从左下到右上）
	nCount = JudgeHyperphoria(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 对角线判断II（从左上到右下）
	nCount = JudgeHypophoria(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 再
	// 判断棋盘是否已满
	if (JudgeDraw() == TRUE)
		return JUDGE_DRAW;
	
	// 没有胜者且棋盘未满，游戏继续
	return JUDGE_CONTINUE;
}

int JudgeHorizontal(const nRow, const nCol, const int nStandard)
{
	int i, j;
	int counter = 1;		// 计数同色相连棋子数
	j = nCol;

	//纵向(向上)
	i = nRow-1;
	while (i >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向上遍历，碰到同色计数器+1
			i--;			// 继续向上遍历
		}
		else
			break;			// 碰到非同色结束向上遍历
	}

	//纵向（向下）
	i = nRow + 1;
	while (i < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向下遍历，碰到同色计数器+1
			i++;			// 继续向下遍历
		}
		else
			break;			// 碰到非同色结束向下遍历
	}

	return counter;
}

int JudgeVertical(const nRow, const nCol, const int nStandard)
{
	int i, j;
	int counter = 1;		// 计数同色相连棋子数
	i = nRow;

	//横向(向左)
	j = nCol - 1;
	while (j >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向左遍历，碰到同色计数器+1
			j--;			// 继续向左遍历
		}
		else
			break;			// 碰到非同色结束向左遍历
	}

	//横向（向右）
	j = nCol + 1;
	while (j < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向左遍历，碰到同色计数器+1
			j++;			// 继续向右遍历
		}
		else
			break;			// 碰到非同色结束向右遍历
	}

	return counter;
}

int JudgeHyperphoria(const nRow, const nCol, const int nStandard)
{

	int i, j;
	int counter = 1;		// 计数同色相连棋子数
	

	//对角线(↙向左下)
	i = nRow - 1;
	j = nCol + 1;
	while (j < MAX&&i >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向左下遍历，碰到同色计数器+1
			j++;			// 继续向左下遍历
			i--;
		}
		else
			break;			// 碰到非同色结束向左下遍历
	}

	//对角线(↗向右上)
	i = nRow + 1;
	j = nCol - 1;
	while (j >= 0 && i < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向右上遍历，碰到同色计数器+1
			i++;			// 继续向右上遍历
			j--;
		}
		else
			break;			// 碰到非同色结束向右上遍历
	}

	return counter;
}

int JudgeHypophoria(const nRow, const nCol, const int nStandard)
{

	int i, j;
	int counter = 1;		// 计数同色相连棋子数


	//对角线(↖向左上)
	i = nRow - 1;
	j = nCol - 1;
	while (j >= 0 && i >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向左上遍历，碰到同色计数器+1
			j--;			// 继续向左上遍历
			i--;
		}
		else
			break;			// 碰到非同色结束向左上遍历
	}

	//对角线(↘向右下)
	i = nRow + 1;
	j = nCol + 1;
	while (i < MAX&&j < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// 落子点向右下遍历，碰到同色计数器+1
			i++;			// 继续向右下遍历
			j++;
		}
		else
			break;			// 碰到非同色结束向右下遍历
	}

	return counter;
}

void PrintWinner(const int nColor)
{
	if (nColor == 0)					// 表示黑棋胜
	{
		gotoxy(28, 12);
		printf("╔════════╗");
		gotoxy(28, 13);
		printf("║●恭喜黑棋获胜●║");
		gotoxy(28, 14);
		printf("╚════════╝");
		gotoxy(26, 24);

	}
	else if (nColor == 1)				// 表示白棋胜
	{
		gotoxy(28, 12);
		printf("╔════════╗");
		gotoxy(28, 13);
		printf("║○恭喜白棋获胜○║");
		gotoxy(28, 14);
		printf("╚════════╝");
		gotoxy(26, 24);

	}

}

void PrintDraw()
{
	gotoxy(28, 12);
	printf("╔════════╗");
	gotoxy(28, 13);
	printf("║  ●○和棋○●  ║");
	gotoxy(28, 14);
	printf("╚════════╝");
	gotoxy(26, 27);
}

