#include "menu.h"


HANDLE hout;

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
	printf("\t\t\t        开始游戏\n");
	printf("\t\t\t        加载棋局\n");
	printf("\t\t\t        排行榜\n");
	printf("\t\t\t        查看规则\n");
	printf("\t\t\t        关于我们\n");
	printf("\t\t\t        退出\n");
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