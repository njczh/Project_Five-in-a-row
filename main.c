#include <stdio.h> //printf()函数头文件
// stdio "standard buffered input & output
// 带缓冲区的标准输入输出，用到标准输入输出函数时，就要包含这个头文件！
#include <Windows.h>
#include <conio.h>
#include "menu.h"
#include "game_service.h"

#define MAX 15

void intiApplication()
{
	//输出欢迎界面
	system("cls");
	printf("\n\t\t\t ┏━━━━━━━━━┓\n");
	printf("\t\t\t ┃欢迎进入五子棋游戏┃\n");
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
		intiApplication();

		nSelect = printMainMenu();
		switch (nSelect)
		{
		case 0:// 退出
			continue;

		case 1:// 开始游戏
			system("cls");
			PlayGame();
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
		gotoxy(17,12);
		system("pause");
	} while (nSelect != 0);

	exitApplication();
	return 0;// 如果返回0，则代表程序正常退出；
}

