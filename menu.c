#include "menu.h"

HANDLE hout;

void intiApplication()
{
	//输出欢迎界面
	system("cls");
	printf("\n\t\t\t ┏━━━━━━━━━┓\n");
	printf("\t\t\t ┃欢迎使用五子棋游戏┃\n");
	printf("\t\t\t ┗━━━━━━━━━┛\n");
}

void exitApplication()
{
	// 保存排名信息
	SaveRanks();

	// 释放链表空间
	ClearRanks();

	// 输出游戏结束提示信息
	for (int i = 5; i != 0; i--)
	{
		system("cls");
		printf("\n\t\t\t┏━━━━━━━━━┓\n");
		printf("\t\t\t┃     感谢使用!    ┃\n");
		printf("\t\t\t┃    (%d秒后退出)   ┃\n", i);
		printf("\t\t\t┗━━━━━━━━━┛\n");
		Sleep(1000);
	}
}

void GetInput(int *nSelect)
{
	int ch=_getch();

	COORD coord;			//屏幕上的坐标
	coord.X = 1;
	coord.Y = 1;

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	while (1)
	{
		while (ch == 0xE0 || ch == 0x0d) {

			printf("\b\b  ");
			

			GetConsoleScreenBufferInfo(hout, &csbi);
			coord.X = csbi.dwCursorPosition.X;// 得到坐标x的值
			coord.Y = csbi.dwCursorPosition.Y;// 得到坐标y的值

			coord.X += 12;
			SetConsoleCursorPosition(hout, coord);
			printf("\b\b  ");
			coord.X -= 12;
			SetConsoleCursorPosition(hout, coord);

			if (ch == 0x0d)				      // 如果是回车
				return;
			ch = _getch();

			//上
			if (ch == 0x48)
			{
				if ((*nSelect) == 1)
				{
					(*nSelect) = OPTIONS;
					coord.Y += 2 * (OPTIONS - 1);
				}
				else
				{
					(*nSelect)--;
					coord.Y-=2;
				}
			}
			//下
			else if (ch == 0x50)
			{
				if ((*nSelect) == OPTIONS)
				{
					coord.Y -= 2 * (OPTIONS - 1);
					(*nSelect) = 1;
				}
				else
				{
					coord.Y+=2;
					(*nSelect)++;
				}
			}

			SetConsoleCursorPosition(hout, coord);
			printf("\b\b●");
			coord.X += 12;
			SetConsoleCursorPosition(hout, coord);
			printf("\b\b○");
			coord.X -= 12;
			SetConsoleCursorPosition(hout, coord);

			ch = _getch();
		}
		ch = _getch();
	}
}

int printMainMenu()
{
	int nSelect = 1; // 默认为1

	printf("\n\t\t========================================\n\n");
	printf("\t\t\t        人人对战\n\n");
	printf("\t\t\t        人机对战\n\n");
	printf("\t\t\t        加载棋局\n\n");
	printf("\t\t\t        分数排行\n\n");
	printf("\t\t\t        查看规则\n\n");
	printf("\t\t\t        关于我们\n\n");
	printf("\t\t\t        退出游戏\n");
	printf("\n\t\t----------------------------------------\n");
	printf("\t\t请使用↑↓键选择功能，按回车键确认！");
	
	gotoxy(42, 8);
	printf("○");
	gotoxy(30,8);
	printf("●");
	hout = GetStdHandle(STD_OUTPUT_HANDLE);					 // 获得标准输出设备句柄  

	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };				 // 隐藏光标
	SetConsoleCursorInfo(hout, &cursor_info);

	GetInput(&nSelect);
	nSelect = nSelect % OPTIONS;
	
	/*
	// 获得用户的输入
	scanf_s("%d", &nSelect);
	
	// 清除输入流缓存
	char s[1024];
	fgets(s, 1024, stdin);
	// fflush(stdin);
	*/

	
	// 返回用户选择的菜单项序号
	return nSelect;

}

void PlayGame(int nSelect)
{
	Point spPoint;						// 坐标点
	int nStep = 0;						// 下子的步数
	int nResult = JUDGE_CONTINUE;		// 棋局判断结果

	if (nSelect == 1)					
	{
		// 开始新游戏
		// 初始化游戏数据
		InitStatus();
	}
	else if (nSelect == 3)				
	{
		// 加载游戏
		LoadGame(&nStep);
	}

	// 绘制棋盘
	PrintChess();
	//PrintBound();

	// 输出开始提示
	PrintStartPrompt();

	// 绘制棋盘
	PrintChess();
	//PrintBound();

	//开始下棋，使用do…while至少先落一子，再进行检查是否获胜
	do 
	{

		spPoint.status = nStep % 2;

		// 使用方向键获得用户下子坐标
		
		switch (InputCoord(&spPoint))
		{
		case 1:			// 玩家正确落子
			break;
		case 0:			// 玩家选择退出游戏
			if (PrintPrompt() == 0)
			{
				// 玩家是否保存游戏
				SaveGame(nStep);
			}				
			return;
			break;
		case -1:		// 玩家退出选择否
			PrintChess();
			continue;
		}

		// 通过输入坐标落子
		// InputPoint(&spPoint);

		// 设置坐标点状态
		SetStatus(spPoint);

		// 更新棋盘
		PrintChess();

		//步数增加
		nStep++;

		// 判断棋局
		nResult = JudgeGame(spPoint);
		
		// 循环落子，当获胜时，则结束循环
	} while (nResult == JUDGE_CONTINUE);	
	
	// 游戏结束判断输出输赢或平局
	if (nResult == JUDGE_WIN)
	{
		// 输出胜利信息
		PrintWinner(spPoint);	
		// 保存排名信息
		PrintAddRank(nStep);
	}
	else if (nResult == JUDGE_DRAW)		
	{
		// 输出和棋信息
		PrintDraw();			
	}

	// 保存排名信息
	SaveRanks();
}

void PrintGameRule()
{
	// 输出游戏规则界面
	system("cls");
	gotoxy(1, 6);
	printf("\t\t━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("\t\t游戏规则\n");
	printf("\t\t┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄\n");
	printf("\t\t1、五子棋为两个人之间的竞技。\n");
	printf("\t\t2、黑棋先行，白棋后行。\n");
	printf("\t\t3、棋盘为：15*15。\n");
	printf("\t\t4、同色棋子在横竖斜某一方向连成5子为胜。\n");
	printf("\t\t5、对局双方均未形成五连且棋盘已满为和棋。\n");
	printf("\t\t6、棋盘横向以字母编号，纵向以数字编号。\n");
	printf("\t\t7、用户选择开始游戏即可开始下棋！\n");
	printf("\t\t8、用户输入对应点的列号与行号，如:A0。\n");
	printf("\t\t┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄\n");
	printf("\t\t按任意键返回…\n");
	_getch();
}

void PrintAboutUs()
{
	// 输出关于我们界面
	system("cls");
	gotoxy(1, 6);
	printf("\t\t━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("\t\t关于我们\n");
	printf("\t\t┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄\n");
	printf("\t\t\t五子棋游戏 Verison 1.0 Beta\n");
	printf("\t\t版权所有 2016 征晖 www.ghostcoming.space\n");
	printf("\t\t┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄\n");
	printf("\t\t按任意键返回…\n");
	_getch();
}

void PrintAddRank(const int nStep)
{
	char acName[64];				// 获得用户输入的姓名
	Rank srRank;					// 排名信息结构体对象

	int nOrder = JudgeOrder(nStep);	// 判断排名

	// 判断排名是否在前10之内
	if (nOrder <= 10)
	{
		// 提示用户输入姓名
		gotoxy(24, 24);
		printf("恭喜你获得了胜利，本局用了%d步。\n",nStep);
		printf("\t\t---------------------------------------------\n");
		printf("\t\t请输入姓名：");
		scanf_s("%s", acName, 64);
		strcpy_s(srRank.name, sizeof(srRank.name), acName);
		srRank.step = nStep;
	}
	else
	{
		gotoxy(24, 24);
		system("pause");
	}
	// 添加排名信息
	InsertRank(nOrder - 1, srRank);
	
}

void PrintRanklist()
{
	system("cls");
	const int nMaxSize = GetRankSize();			// 获得个数
	int nSize = 0;								// 实际的玩家个数，正常情况下，此值与nMaxSize相等；
	Rank* psrRanks = NULL;						// 获得排名数组
	int nIndex = 0;								// 遍历数组索引号

	// 输出排行榜与表头
	gotoxy(1, 6);
	printf("\t\t━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("\t\t排行榜\n");
	printf("\t\t┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄\n");
	printf("\t\t名次\t\t用户名\t\t步数\n");

	// 开辟nMaxSize个Rank空间，即开辟一个Rank数组空间
	psrRanks = (Rank*)malloc(sizeof(Rank)*nMaxSize);
	// 初始化新的空间，全部赋值为0
	memset(psrRanks, 0, sizeof(Rank)*nMaxSize);
	
	// 获得玩家列表
	nSize = GetRanks(psrRanks, nMaxSize);

	// 获得排名数组
	for (nIndex = 0; nIndex < nMaxSize; nIndex++)
	{
		printf("\t\t%d\t\t%s\t\t%d\n", nIndex + 1, psrRanks[nIndex].name, psrRanks[nIndex].step);
	}

	// 释放开辟的空间
	free(psrRanks);

	// 提示用户返回操作
	printf("\t\t┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄\n");
	printf("\t\t按任意键返回…\n");
	_getch();
}
