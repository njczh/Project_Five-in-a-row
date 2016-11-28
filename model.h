#ifndef _MODAL_H_
#define _MODAL_H_

// 坐标点的状态类型

enum PointStatus
{
	BLANK = -1,		// blank
	BLACK = 0,		// black
	WHITE = 1		// white
};

// 定义坐标点数据
typedef struct Point
{
	int row;				// 行号
	int col;				// 列号
	int status;				// 当前点的状态值，取值对应PointStatus类型
}Point;

// 定义排名数据
typedef struct Rank
{
	char name[64];			// 玩家ID
	int step;				// 胜利时所用的步数
}Rank;

// 定义排名链表
typedef struct Node
{
	Rank rank;
	struct Node* next;
}Node;

#endif