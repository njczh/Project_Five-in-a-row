#include "rank_service.h"
#include "rank_file.h"
#include "model.h"

Node* psnRanklist = NULL;

int JudgeOrder(const int nStep)
{
	Node* psnNode = psnRanklist->next;
	int nOrder = 0;

	// 遍历列表，寻找插入点
	while (psnNode != NULL)
	{
		if (psnNode->rank.step > nStep)
			// 找到第一个大于该步数的玩家，则新玩家的排名为找到的玩家的前一名
			break;
		// 指向下一个结点
		psnNode = psnNode->next;
		nOrder++;
	}

	// 排名比索引号数值上大1
	return nOrder + 1;

}

void InsertRank(const int nPostion, const Rank srRank)
{
	// 操作节点指针
	Node *psnNode = psnRanklist->next;
	// 前一节点指针
	Node *psnPreNode = psnRanklist;

	// 节点位置记录
	int nPos = 0;

	// 寻找插入点
	for (nPos = 0; psnNode != NULL&&nPos != nPostion; nPos++)
	{
		psnPreNode = psnNode;
		psnNode = psnNode->next;
	}

	// 开辟一个Rank空间
	psnNode = (Node*)malloc(sizeof(Node));

	// 初始化新开辟的空间，全部赋值为0
	memset(psnNode, 0, sizeof(Node));

	// 添加玩家排名信息
	psnNode->rank = srRank;

	// 将新节点指向下一节点
	psnNode->next = psnPreNode->next;

	// 将前一节点指向新的节点
	psnPreNode->next = psnNode;

}

void SaveRanks()
{
	// 逻辑层中数据传递给数据处理层时需要将链表转换为数组

	// 获得玩家总数
	const int nMaxsize = GetRankSize();

	// 玩家数，用于写入文件,正常情况下，此值与nMaxsize相等
	int nSize = 0;

	// 开辟nMaxSize个Rank空间，即开辟一个Rank数组空间
	Rank* psrRanks = (Rank*)malloc(sizeof(Rank)*nMaxsize);

	// 初始化新空间
	memset(psrRanks, 0, sizeof(Rank)*nMaxsize);

	// 获得链表数据，将其保存在数组中
	nSize = GetRanks(psrRanks, nMaxsize); 

	// 将数据写入文件中
	WriteRanklist(psrRanks,nSize);

	// 释放开辟的空间
	free(psrRanks);
}

int GetRankSize()
{
	// 指向第一个玩家节点，第一个玩家从第二个节点开始
	Node* psnNode = psnRanklist->next;

	// 数组索引号
	int nIndex = 0;

	// 循环遍历链表各个节点
	while (psnNode != NULL)
	{
		// 移到下一个节点
		psnNode = psnNode->next;
		// 索引号递增
		nIndex++;
	}

	// nIndex 的值正好为排名玩家的个数
	return nIndex;
}

int GetRanks(Rank* psrRanks, const int nMaxSize)
{
	// 指向第一个玩家节点，第一个玩家从第二个节点开始
	Node* psnNode = psnRanklist->next;

	// 数组索引号
	int nIndex = 0;

	// 循环遍历链表各个节点
	while (psnNode != NULL&&nIndex < nMaxSize)
	{
		// 将数据存放到目标数组中
		psrRanks[nIndex] = psnNode->rank;

		// 移到下一个节点
		psnNode = psnNode->next;
		// 索引号递增
		nIndex++;
	}

	// 索引号递增后正好为正确读到的玩家个数
	return nIndex;
}

void InitRanks()
{
	// 从文件中读取保存为数组形式，在初始化排名信息时，需要把数据转换为链表保存

	// 获取文件中排名玩家的个数
	const int nMaxSize = GetRanklistCount();

	// Rank数组指针
	Rank* psrRanks = NULL;
	// 读取到的玩家个数，此值通常与nMaxSize相等
	int nSize = 0;
	// 数组索引值
	int nIndex = 0;

	// 初始化链表头
	if (psnRanklist == NULL)
	{
		// 开辟一个Node空间
		psnRanklist = (Node*)malloc(sizeof(Node));
		// 初始化为零
		memset(psnRanklist, 0, sizeof(Node));
	}

	// 开辟nMaxSize个Rank数组空间
	psrRanks = (Rank*)malloc(sizeof(Rank)*nMaxSize);
	// 初始化为零
	memset(psrRanks, 0, sizeof(Rank)*nMaxSize);

	//读取排名数组，获得个数
	nSize = ReadRanklist(psrRanks,nMaxSize);

	// 依次插入节点
	for (nIndex = 0; nIndex < nSize; nIndex++)
	{
		// 插入节点
		InsertRank(nIndex, psrRanks[nIndex]);
	}

	// 释放数组空间
	free(psrRanks);
}

void ClearRanks()
{
	// 遍历释放各节点元素
	Node* psnNode = psnRanklist;
	// 用来指向当前需要释放节点指针
	Node* psnCurNode = NULL;

	// 循环遍历释放链表
	while (psnNode != NULL)
	{
		// 保存当前需要释放的节点
		psnCurNode = psnNode;
		// 移到下一节点
		psnNode = psnNode->next;
		// 释放当前节点
		free(psnCurNode);
	}
	// 将指针置空
	psnRanklist = NULL;
}

