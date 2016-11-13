#include <stdio.h> //printf()函数头文件
// stdio "standard buffered input & output
// 带缓冲区的标准输入输出，用到标准输入输出函数时，就要包含这个头文件！
#include <windows.h>;
#include <conio.h>

#define MAX 15
const char CHESS_BLANK[4] = "╋";

///////////////////////////////////////////////////////
// 函数声明
/****************************************************
[函数名称] printMainMenu
[函数功能] 输出菜单，并获取用户选择
[函数参数] 无
[返 回 值] int: 返回用户选项
****************************************************/
int printMainMenu(); 

/****************************************************
[函数名称] printChess
[函数功能] 输出棋盘
[函数参数] 无
[返 回 值] 无
****************************************************/
void printChess();

///////////////////////////////////////////////////////

void gotoxy(int x, int y) //goto语句
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/****************************************************
[函数名称] main
[函数功能] 程序主函数，即入口函数
[函数参数] 无
[返 回 值] int: 说明程序的退出状态
****************************************************/
int main(void)
{
	int nSelect;
	do
	{
		//输出欢迎界面
		system("cls");
		printf("\n\t\t\t┏━━━━━━━━━┓\n");
		printf("\t\t\t┃欢迎进入五子棋游戏┃\n");
		printf("\t\t\t┗━━━━━━━━━┛\n");
		nSelect = printMainMenu();
		switch (nSelect)
		{
		case 0:// 退出

			continue;
		case 1:// 开始游戏
			system("cls");
			printChess();
			gotoxy(28, 12);
			printf("╔════════╗\n");
			gotoxy(28, 13);
			printf("║按任意键开始游戏║\n");
			gotoxy(28, 14);
			printf("╚════════╝\n");
			_getch();
			system("cls");
			printChess();
			break;
		case 2:// 加载棋局
			printf("\t\t加载棋局");
			break;
		case 3:// 排行榜
			printf("\t\t排行榜");
			break;
		case 4:// 查看规则
			printf("\t\t查看规则");
			break;
		case 5:// 关于我们
			printf("\t\t关于我们");
			break;
		default:
			printf("\t\t输入有误，请确认选项！");

		}
		printf("\n\t\t按任意键继续！");
		_getch();
	} while (nSelect != 0);

	// 退出
	for (int i = 5; i != 0; i--)
	{
		system("cls");
		printf("\n\t\t\t┏━━━━━━━━━┓\n");
		printf(  "\t\t\t┃     感谢使用!    ┃\n");
		printf(  "\t\t\t┃    (%d秒后退出)   ┃\n", i);
		printf(  "\t\t\t┗━━━━━━━━━┛\n");
		Sleep(1000);
	}
	return 0;// 如果返回0，则代表程序正常退出；
}

int printMainMenu()
{
	// 使用char以增强程序健壮性
	int nSelect;

	printf("\n");
	printf("\t\t========================================\n");
	printf("\t\t1.开始游戏\t2.加载棋局\t3.排行榜\n");
	printf("\t\t4.查看规则\t5.关于我们\t0.退出\n");
	printf("\t\t----------------------------------------\n");
	printf("\t\t请选择菜单序号：");

	// 获得用户的输入
	scanf_s("%d", &nSelect);

	// 清除输入流缓存
	fflush(stdin);

	// 返回用户选择的菜单项序号
	return nSelect;

}

void printChess()
{
	// 初始化棋盘信息
	int a[MAX][MAX] = {0};
	memset(a, -1, sizeof(a)); // 将a所指向的一块内存中的前sizeof(a)个字节的内容全部设置为-1

	/////////////
	//测试棋子样式
	a[6][6] = 0;
	a[7][7] = 1;
	/////////////

	// 输出棋盘列号
	char cA = 'A';
	printf("\n\n\n\t\t       ");
	for (int i = 0; i < MAX; i++)
		printf("%C ", cA + i);
	printf("\n");
	
	//输出棋盘上沿
	printf("\t\t    ┏");
	for (int i = 0; i < MAX; i++)
		printf("┳");
	printf("┓\n");

	// 输出棋盘
	for (int row = 0; row < MAX; row++)
	{
		for (int line = -1; line < MAX; line++)
		{
			if (line == -1)
			{
				printf("\t\t  %02d┣", row + 1);
				continue;
			}
			else if (a[row][line] == -1)// 此处为空
				printf(CHESS_BLANK);
			else if (a[row][line] == 0)// 此处为白子
				printf("○");
			else // 此处为黑子 
				printf("●");
		}
		printf("┫\n");
	}

	//输出棋盘下沿
	printf("\t\t    ┗");
	for (int i = 0; i < MAX; i++)
		printf("┻");
	printf("┛\n");

}
