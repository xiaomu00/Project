#ifndef _GREEDY_SNAKE_H_
#define _GREEDY_SNAKE_H_
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>//光标设置
#include<time.h>//食物随机
#include<conio.h>//按键监控
#include<graphics.h>//图形界面库
#include<mmsystem.h>//多媒体设备接口
#pragma comment(lib,"Winmm.lib")

//////////////////////////////////////////////////////////////////////////////////////////////
////宏定义

#define Sanke_Size  100     //蛇的最大长度


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
////函数声明接口

void Load_music();//加载音乐
void Start_interface();//绘制开始界面
void Description_interface();//绘制说明界面
void Game_over(int sh);//绘制结束界面
void GameInIt();  //初始化
void DrawSnake_1(int i);//用不同颜色绘制一节蛇
void DrawSnake();//绘制蛇
void SnakeMove(); //蛇的移动
void Changch(char input);//改变方向
void CreateFood();//计算食物坐标食物
void DrawFood();//绘制食物
int eatFood();//判断食物是否被吃食物
int  SnakeStatus();  //蛇的状态——判断是否结束游戏
void ShowStatus_bar();//显示状态栏
int myspeed();//获取速度
void Changespeed(char c);//改变速度
int myHight_Score();//获取当前最高分
void Hight_Score_in();//将最高分写入文件
int Hight_Score_out();//将文件里的分数读出

#endif /*_GREEDY_SNAKE_H_*/