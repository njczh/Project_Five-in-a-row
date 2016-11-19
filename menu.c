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
	// 退出
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
				return *nSelect;
			ch = _getch();

			//上
			if (ch == 0x48)
			{
				if ((*nSelect) == 1)
				{
					(*nSelect) = OPTIONS;
					coord.Y += OPTIONS-1;

				}
				else
				{
					(*nSelect)--;
					coord.Y--;

				}
			}
			//下
			else if (ch == 0x50)
			{
				if ((*nSelect) == OPTIONS)
				{
					coord.Y -= OPTIONS-1;
					(*nSelect) = 1;
				}
				else
				{
					coord.Y++;
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

	printf("\n");
	printf("\t\t========================================\n\n");
	printf("\t\t\t        NEW GAME\n");
	printf("\t\t\t        加载棋局\n");
	printf("\t\t\t        分数排行\n");
	printf("\t\t\t        查看规则\n");
	printf("\t\t\t        关于我们\n");
	printf("\t\t\t        退出游戏\n");
	printf("\n\t\t----------------------------------------\n");
	printf("\t\t请使用↑↓键选择功能，按回车键确认！");
	
	gotoxy(42, 8);
	printf("○");
	gotoxy(30,8);
	printf("●");
	hout = GetStdHandle(STD_OUTPUT_HANDLE);					 //获得标准输出设备句柄  
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
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

void PlayGame()
{
	Point spPoint;						// 坐标点
	int nStep = 0;						// 下子的步数
	int nResult = JUDGE_CONTINUE;		// 棋局判断结果

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

		spPoint.status = nStep % 2;
		// 获得用户下子坐标
		InputPoint(&spPoint);

		// 设置坐标点状态
		SetStatus(spPoint);

		// 更新棋盘
		PrintChess();

		//步数增加
		nStep++;

		// 判断棋局
		nResult = JudgeGame(spPoint);
	} while (nResult == JUDGE_CONTINUE);	// 循环落子，当获胜时，则结束循环
	
	// 游戏结束判断输出输赢或平局
	if (nResult == JUDGE_WIN)
	{
		PrintWinner(spPoint);	// 输出胜利信息
	}
	else if (nResult == JUDGE_DRAW)		// 输出和棋信息
	{
		PrintDraw();
	}
}

void PrintGameRule()
{
	system("cls");
	printf("━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("游戏规则\n");
	printf("…………………………………………………………\n");
	printf("1、五子棋为两个人之间的竞技。\n");
	printf("2、黑棋先行，白棋后行。\n");
	printf("3、棋盘为：15*15。\n");
	printf("4、同色棋子在横竖斜某一方向连成5子为胜。\n");
	printf("5、对局双方均未形成五连且棋盘已满为和棋。\n");
	printf("6、棋盘横向以字母编号，纵向以数字编号。\n");
	printf("7、用户选择开始游戏即可开始下棋！\n");
	printf("8、用户输入对应点的列号与行号，如:A0。\n");
	printf("…………………………………………………………\n");
	printf("按任意键返回…\n");
	_getch();
}

void PrintAboutUs()
{
	system("cls");
	printf("━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("关于我们\n");
	printf("…………………………………………………………\n");
	printf("\t五子棋游戏 Verison 1.0 Beta\n");
	printf("版权所有 2016 征晖 www.ghostcoming.space\n");
	printf("…………………………………………………………\n");
	printf("按任意键返回…\n");
	_getch();
}
