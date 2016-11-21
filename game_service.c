#include "game_service.h"

int AnChessStatus[MAX][MAX];
HANDLE hout;


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
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			AnChessStatus[i][j] = STATUS_BLANK;
}

int GetStatus(const Point point)
{
	return AnChessStatus[point.row][point.col];
}

void SetStatus(const Point point)
{
	AnChessStatus[point.row][point.col] = point.status;
}

void InputPoint(Point* point)
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
		if (point->status == STATUS_BLACK)					// 黑方执子
		{
			gotoxy(20, 25);
			printf("黑子●下，请输入坐标编号（如：A1）：");
		}
		else if (point->status == STATUS_WHITE)				// 白方执子
		{
			gotoxy(20, 25);
			printf("白子○下，请输入坐标编号（如：A1）：");
		}

		// 获得用户输入的坐标
		//getchar();
		fgets(acPoint, 8, stdin);

		point->col = toupper(acPoint[0]) - 'A';	// 将字符转换为大写英文字母,对应二维数组的第一个下标为0
		point->row = atoi(&acPoint[1]) - 1;		// 字符串的第二个字母后为数字，使用atoi函数进行转换

		// 判断输入的行号和列号是否有效
		if (point->row < 0 || point->row>MAX-1 || point->col < 0 || point->col >MAX-1)
		{
			legal = 0;						// 非法输入
			gotoxy(32, 26);
			printf("【落子失败】");
			gotoxy(26, 27);
			printf("坐标不存在！请确认输入！\n");
			continue;
		}

		// 获得坐标点的状态值
		nStatus = GetStatus(*point);

		//判断状态
		if (nStatus != STATUS_BLANK)		// 当状态不为空是，不可落子
		{
			legal = 0;						// 非法输入
			// 当前位置已经存在棋子，提示用户
			gotoxy(32, 26);
			printf("【落子失败】");
			gotoxy(26, 27);
			printf("%02d行%c列已有棋子！不可落子！\n", point->col +1, point->row +'A');
			continue;
		}

		// 落子坐标有效，且该坐标状态为BLANK，即为合法位置
		legal = 1;							// 标记坐标合法

	} while (legal==0);						// 输入非法，需要重新落子

}

int InputCoord(Point *point)
{
	gotoxy(17, 24);
	//以此标识，提示用户的输入
	printf("==========================================\n");
	if (point->status == STATUS_BLACK)
	{
		gotoxy(20, 25);
		printf("【黑子●】，请使用↑↓←→键选择落子位置。");
		gotoxy(23, 6);
		printf("●\b");
	}
	else if (point->status == STATUS_WHITE)
	{
		gotoxy(20, 25);
		printf("【白子○】，请使用↑↓←→键选择落子位置。");
		gotoxy(23, 6);
		printf("○\b");
	}

	COORD coord;			//屏幕上的坐标
	coord.X = 1;
	coord.Y = 1;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	point->col = 0;
	point->row = 0;
	
	char key = 0;

	do
	{
		
		GetConsoleScreenBufferInfo(hout, &csbi);
		coord.X = csbi.dwCursorPosition.X;// 得到坐标x的值
		coord.Y = csbi.dwCursorPosition.Y;// 得到坐标y的值
		
		if (key != 13)
			key = _getch();
		
		int nStatus = GetStatus(*point);

		switch (key)
		{
		
		//up	 
		case 72:
			if (coord.Y == 5)
			{
				point->row = MAX-1;
				if (nStatus == STATUS_BLANK)
					printf("╋");
				else if (nStatus == STATUS_BLACK)
					printf("●");
				else if (nStatus == STATUS_WHITE)
					printf("○");
				coord.Y = MAX + 4;
				SetConsoleCursorPosition(hout, coord);
			}
			else
			{
				point->row--;
				if (nStatus == STATUS_BLANK)
					printf("╋");
				else if (nStatus == STATUS_BLACK)
					printf("●");
				else if (nStatus == STATUS_WHITE)
					printf("○");
				coord.Y--;
				SetConsoleCursorPosition(hout, coord);
			}
			break;

		//down
		case 80:
			if (coord.Y == MAX + 4)
			{
				point->row = 0;
				if (nStatus == STATUS_BLANK)
					printf("╋");
				else if (nStatus == STATUS_BLACK)
					printf("●");
				else if (nStatus == STATUS_WHITE)
					printf("○");
				coord.Y = 5;
				SetConsoleCursorPosition(hout, coord);
			}
				
			else
			{
				point->row++;
				if (nStatus == STATUS_BLANK)
					printf("╋");
				else if (nStatus == STATUS_BLACK)
					printf("●");
				else if (nStatus == STATUS_WHITE)
					printf("○");
				coord.Y++;
				SetConsoleCursorPosition(hout, coord);
			}
			break;
		
		//left
		case 75:
			if (coord.X == 22)
			{
				point->col = MAX - 1;
				if (nStatus == STATUS_BLANK)
					printf("╋\b\b");
				else if (nStatus == STATUS_BLACK)
					printf("●\b\b");
				else if (nStatus == STATUS_WHITE)
					printf("○\b\b");
				coord.X = 2 * MAX + 20;
				SetConsoleCursorPosition(hout, coord);
			}
			else
			{
				point->col--;
				if (nStatus == STATUS_BLANK)
					printf("╋");
				else if (nStatus == STATUS_BLACK)
					printf("●");
				else if (nStatus == STATUS_WHITE)
					printf("○");
				coord.X -= 2;
				SetConsoleCursorPosition(hout, coord);
			}
			break;
		
		//right
		case 77:
			if (coord.X == 2 * MAX + 20)
			{
				point->col = 0;
				if (nStatus == STATUS_BLANK)
					printf("╋\b\b");
				else if (nStatus == STATUS_BLACK)
					printf("●\b\b");
				else if (nStatus == STATUS_WHITE)
					printf("○\b\b");
				coord.X = 22;
				SetConsoleCursorPosition(hout, coord);
			}
			else
			{
				point->col ++;
				coord.X += 2;
				SetConsoleCursorPosition(hout, coord);
				if (nStatus == STATUS_BLANK)
					printf("\b\b╋");
				else if (nStatus == STATUS_BLACK)
					printf("\b\b●");
				else if (nStatus == STATUS_WHITE)
					printf("\b\b○");
			}
			break;
		
		//回车确认
		case 13:
			
			if (point->row < 0 || point->row>MAX - 1 || point->col < 0 || point->col >MAX - 1)
			{
				gotoxy(32, 26);
				printf("【落子失败】");
				gotoxy(26, 27);
				printf("坐标不存在！请确认输入！\n");
				SetConsoleCursorPosition(hout, coord);
				continue;
			}
			//判断状态
			if (GetStatus(*point) != STATUS_BLANK)		// 当状态不为空是，不可落子
			{
				// 当前位置已经存在棋子，提示用户
				gotoxy(32, 26);
				printf("【落子失败】");
				gotoxy(26, 27);
				printf("%02d行%c列已有棋子！不可落子！\n", point->col + 1, point->row + 'A');
				SetConsoleCursorPosition(hout, coord);
				key = _getch();
				continue;
			}
			return 1;

		default:
			continue;
			break;

		}

		if (point->status == STATUS_BLACK)
			printf("●");
		else if (point->status == STATUS_WHITE)
			printf("○");
		SetConsoleCursorPosition(hout, coord);

		key = _getch();

	} while (key != 27);

	char running = 'N';
	do
	{
		gotoxy(28, 12);
		printf("╔════════╗");
		gotoxy(28, 13);
		printf("║ 结束游戏(Y/N)? ║");
		gotoxy(28, 14);
		printf("╚════════╝");
		gotoxy(1, 1);
		running = _getch();
		running = toupper(running);	// 将字符转换为大写英文字母
	} while (running != 'Y' && running != 'N');

	if (running == 'Y')
		return 0;
	else if(running == 'N')
		return -1;
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
	_getch();
	gotoxy(24, 12);
	printf("╔════════════╗");
	gotoxy(24, 13);
	printf("║游戏过程中可按ESC键退出!║");
	gotoxy(24, 14);
	printf("╚════════════╝");
	_getch();
	system("cls");
}

void PrintChess()
{
	int nStatus;
	int i;
	Point point;

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
			point.col = line;
			point.row = row;

			// 获得坐标状态
			nStatus = GetStatus(point);
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

int JudgeGame(Point point)
{
	// 优先判断是否得胜
	// 计数器，用来记录连续相同的棋子数
	int nCount;	

	// 获取落子的标准状态,用于判断
	point.status = AnChessStatus[point.row][point.col];

	// 横向判断
	nCount = JudgeHorizontal(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 纵向判断
	nCount = JudgeVertical(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 对角线判断I（从左下到右上）
	nCount = JudgeHyperphoria(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 对角线判断II（从左上到右下）
	nCount = JudgeHypophoria(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// 再
	// 判断棋盘是否已满
	if (JudgeDraw() == TRUE)
		return JUDGE_DRAW;
	
	// 没有胜者且棋盘未满，游戏继续
	return JUDGE_CONTINUE;
}

int JudgeHorizontal(const Point point)
{
	int i, j;
	int counter = 1;		// 计数同色相连棋子数
	int nStandard = point.status;
	j = point.col;

	//纵向(向上)
	i = point.row-1;
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
	i = point.row + 1;
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

int JudgeVertical(const Point point)
{
	int i, j;
	int counter = 1;		// 计数同色相连棋子数
	int nStandard = point.status;
	i = point.row;

	//横向(向左)
	j = point.col - 1;
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
	j = point.col + 1;
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

int JudgeHyperphoria(const Point point)
{

	int i, j;
	int counter = 1;		// 计数同色相连棋子数
	int nStandard = point.status;


	//对角线(↙向左下)
	i = point.row - 1;
	j = point.col + 1;
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
	i = point.row + 1;
	j = point.col - 1;
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

int JudgeHypophoria(const Point point)
{

	int i, j;
	int counter = 1;		// 计数同色相连棋子数
	int nStandard = point.status;


	//对角线(↖向左上)
	i = point.row - 1;
	j = point.col - 1;
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
	i = point.row + 1;
	j = point.col + 1;
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

void PrintWinner(const Point point)
{
	if (point.status == 0)					// 表示黑棋胜
	{
		gotoxy(28, 12);
		printf("╔════════╗");
		gotoxy(28, 13);
		printf("║●恭喜黑棋获胜●║");
		gotoxy(28, 14);
		printf("╚════════╝");
	}
	else if (point.status == 1)				// 表示白棋胜
	{
		gotoxy(28, 12);
		printf("╔════════╗");
		gotoxy(28, 13);
		printf("║○恭喜白棋获胜○║");
		gotoxy(28, 14);
		printf("╚════════╝");
	}
	gotoxy(24, 24);
	system("pause");
}

void PrintDraw()
{
	gotoxy(28, 12);
	printf("╔════════╗");
	gotoxy(28, 13);
	printf("║  ●○和棋○●  ║");
	gotoxy(28, 14);
	printf("╚════════╝");
	gotoxy(24, 24);
	system("pause");
}

