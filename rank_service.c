#include "rank_service.h"
#include "rank_file.h"
#include "model.h"

Rank AsrRanks[10];
int NRankSize = 0;

int JudgeOrder(const int nStep)
{
	// 数组元素遍历时的索引号
	int nIndex = 0;

	// 找到第一个大于该步数的玩家，则新玩家的排名为找到的玩家的前一名
	while (nIndex < NRankSize)
	{
		if (AsrRanks[nIndex].step > nStep)
		{
			break;
		}
		nIndex++;
	}

	// 排名比索引号数值上大1
	return nIndex + 1;
}

void InsertRank(const int nPostion, const Rank srRank)
{
	// 元素数组索引号
	int nIndex = NRankSize;

	// 当插入点为最后一个元素时，直接覆盖原数据，否则，将其他元素依次后移一位
	if (nPostion < 9)
	{
		while (nIndex > nPostion)
		{
			AsrRanks[nIndex] = AsrRanks[nIndex - 1];
			nIndex--;
		}
	}

	// 在插入点添加新的元素
	AsrRanks[nPostion] = srRank;

	if (NRankSize < 10)
	{
		// 增加排名人数
		NRankSize++;
	}
}

void SaveRanks()
{
	WriteRanklist(AsrRanks,NRankSize);
}

int GetRankSize()
{
	return NRankSize;
}

int GetRanks(Rank* psrRanks, const int nMaxSize)
{
	// 数组索引号
	int nIndex = 0;

	// 循环从全局变量中取出数据，放到临时存放的数组中
	for (nIndex = 0; nIndex < NRankSize&&nIndex < nMaxSize; nIndex++)
	{
		psrRanks[nIndex] = AsrRanks[nIndex];
	}

	// 索引号递增后正好为正确读到的玩家个数
	return nIndex;
}

void InitRanks()
{
	//读取排名数组，获得个数
	NRankSize = ReadRanklist(AsrRanks, 10);
}

