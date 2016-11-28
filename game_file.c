#include "game_file.h"

void WriteGameInfo(int nStep, int aChessStatus[MAX][MAX])
{
	FILE* pfGame = NULL;
	int err = 0;
	
	err = fopen_s(&pfGame, "gamesaver.dat", "wb");

	// 打开文件出错
	if (err != 0)
	{
		printf("文件打开失败！");
		getchar();
		return FALSE;
	}

	fprintf_s(pfGame, "Step:%d\n", nStep);

	int i = 0;
	int j = 0;
	// 写入棋盘信息
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			fprintf_s(pfGame, "%d\n", aChessStatus[i][j]);
		}

	}

	// 关闭文件
	fclose(pfGame);
}

void ReadGameInfo(int *nStep, int aChessStatus[MAX][MAX])
{
	FILE* pfGame = NULL;
	int err = 0;

	err = fopen_s(&pfGame, "gamesaver.dat", "rb");

	// 打开文件出错
	if (err != 0)
	{
		printf("文件打开失败！");
		getchar();
		return FALSE;
	}

	fscanf_s(pfGame, "Step:%d\n", nStep);

	int i = 0;
	int j = 0;

	// 写入棋盘信息
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
		{
			fscanf_s(pfGame, "%d\n", &aChessStatus[i][j]);
		}

	// 关闭文件
	fclose(pfGame);
}

