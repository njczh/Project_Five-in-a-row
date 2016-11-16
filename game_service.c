#include "game_service.h"
#include "global.h"
#include <windows.h>

int AnChessStatus[15][15];

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
		//以此标识，提示用户的输入
		printf("\n\t\t==========================================\n");
		//根据执子方，提示用户输入坐标
		if (nColor == 0)					// 黑方执子
		{
			printf("\t\t黑子下，请输入坐标编号（如：A1）：");
		}
		else if (nColor == 1)				// 白方执子
		{
			printf("\t\t白子下，请输入坐标编号（如：A1）：");
		}

		// 获得用户输入的坐标
		//getchar();
		fgets(acPoint, 8, stdin);
		fflush(stdin);

		*pnCol = toupper(acPoint[0]) - 'A';	// 将字符转换为大写英文字母,对应二维数组的第一个下标为0
		*pnRow = atoi(&acPoint[1]) - 1;		// 字符串的第二个字母后为数字，使用atoi函数进行转换

		// 判断输入的行号和列号是否有效
		if (*pnRow < 0 || *pnRow>14 || *pnCol < 0 || *pnCol >14)
		{
			legal = 0;						// 非法输入
			printf("\t\t坐标不存在！请确认输入！\n");
			continue;
		}

		// 获得坐标点的状态值
		nStatus = GetStatus(*pnRow, *pnCol);

		//判断状态
		if (nStatus != STATUS_BLANK)		// 当状态不为空是，不可落子
		{
			legal = 0;						// 非法输入
			// 当前位置已经存在棋子，提示用户
			printf("\t\t已有棋子！%d%d位置不可落子\n", *pnCol, *pnRow);
			continue;
		}

		// 落子坐标有效，且该坐标状态为BLANK，即为合法位置
		legal = 1;							// 标记坐标合法

	} while (legal==0);						// 输入非法，需要重新落子

}

void PrintPrompt()
{
	gotoxy(28, 12);
	printf("╔════════╗\n");
	gotoxy(28, 13);
	printf("║按任意键开始游戏║\n");
	gotoxy(28, 14);
	printf("╚════════╝\n");
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

	// 初始化游戏数据
	InitStatus();

	// 绘制棋盘
	PrintChess();

	// 输出开始提示
	PrintPrompt();

	// 绘制棋盘
	PrintChess();

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

	} while (1);						// 循环落子，当获胜时，则结束循环

	
}
