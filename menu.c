#include "menu.h"

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
	getchar();

	// 清除输入流缓存
	fflush(stdin);

	// 返回用户选择的菜单项序号
	return nSelect;
	
}