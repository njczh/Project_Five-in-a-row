#pragma once
#include <stdio.h> 
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 
#include "game_service.h"

#define OPTIONS 6


///////////////////////////////////////////////////////
// 函数声明

// 初始化应用程序
void intiApplication();

// 结束应用程序
void exitApplication();

// 通过上下键获得选项
void GetInput(int *nSelect);

/****************************************************
[函数名称] printMainMenu
[函数功能] 输出菜单，并获取用户选择
[函数参数] 无
[返 回 值] char: 返回用户选项
****************************************************/
int printMainMenu();

/****************************************************
[函数名称] PlayGame
[函数功能] 开始游戏
[函数参数] 无
[返 回 值] 无
****************************************************/
void PlayGame();

void PrintGameRule();

void PrintAboutUs();

///////////////////////////////////////////////////////