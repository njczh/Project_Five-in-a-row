#ifndef _MODAL_H_
#define _MODAL_H_

//坐标点的状态类型

enum PointStatus
{
	STATUS_BLANK = -1,		// blank
	STATUS_BLACK = 0,		// black
	STATUS_WHITE = 1		// white
};

// 坐标点数据
typedef struct Point
{
	int row;				// 行号
	int col;				// 列号
	int status;				// 当前点的状态值，取值对应PointStatus类型
}Point;

#endif