#include"Greedy _Snake.h"

static int speed = 0;
int ch;//按键
int flag=0;//食物状态（是否被吃,0代表被吃了）
int fg = 1;



int main()
{

Loop:Load_music();
	Start_interface();//开始界面
	int s;
	while (1)//只有当按下有效键，才进入下一步，否则保留在当前界面
	{
		s = getch();
		if (s == 106 || s == 107)
			s -= 32;
		if (s == 74 || s == 75 || s == 27)
			break;
	}

	switch (s)
	{
	case 74:
	{

		   CK:GameInIt();
			   int sh = Hight_Score_out();
			   while (1)
			   {
			
				   while (!kbhit())//如果没有按下键盘，则进入循环
				   {
					   if (0 == flag)//表示食物被吃了，计算新食物坐标
					   {
						   CreateFood();
					   }
					   DrawFood();
					   flag = eatFood();
					   SnakeMove();//移动

					   fg = SnakeStatus(); //判断是否结束游戏
					   if (0 == fg)
					   while (1)
					   {
						   Game_over(sh);//调动结束页面
						   int sh = Hight_Score_out();
						   int Hight_Score = myHight_Score();
						   if (Hight_Score > sh)//判断是否需要更新文件中的最高分
						   {
							   Hight_Score_in();
						   }
						   while (1)
						   {
							   int c = getch();
							   if (c == 80 || c == 112)//如果是p或者P,则重新开始
								   goto CK;
							   if (c == 27)
								   goto Loop;
						   }
					   }
					   speed = myspeed();
    				   /*for (int i = 0; i <= speed * 40; i++)
					   {
						   Sleep(1);
					   }*/

					   ShowStatus_bar();
					  // cleardevice(); //刷新屏幕

				   }
				   //退出循环表示有按下键盘，判断按下的是什么键
				   ch = getch();
				   if (ch == 27)//如果是Esc,则退出游戏
					   goto Loop;
				   else if (ch == 80 || ch == 112)//如果是p或者P,则重新开始
					   goto CK;

				   else if (ch == 32)//如果是空格,则进入死循环，表示暂停
				   while (1)
				   {
					   int c = getch();
					   if (c == 32)//如果再次按下空格,则退出循环，表示继续游戏
						   break;
				   }
				   else if (ch == 87 || ch == 119 || ch == 83 || ch == 115)
				   {
					   Changespeed(ch);
				   }
				   else 
				   {
					   Changch(ch);//按下方向键，改变方向
				   }

			   }
	}
		break;

	case 75:
		Description_interface();//说明界面
		int ch;
		while (1)
		{
			ch = getch();
			if (ch == 27)
				goto Loop;
		}

		getchar();
		break;
	case 27:
		exit(0);
		break;
	}

	return 0;
}









//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
////图形界面库的用法

//int main()
//{
//	
//	//初始化一个640*480的窗口，左上角是坐标原点，往右为x轴，往下为y轴
//	initgraph(640, 480);//  init(初始化)   graph(图形) 
//	//rectangle(320,240,500,400);//从坐标中间开始，画一个500*400的矩形
//	//circle(320,240,200);//在中间画一个半径为200的圆形
//	////通过传递参数(改变坐标的改变方式)，让图形出现一些理想效果
//	int x = 0, y = 50,speed=0;
//	while (1)
//	{
//		
//		circle(320, y, 50);
//	    //circle(x, y, 50);
//		Sleep(100);
//		y += speed++;
//		if (y<50 || y>430)
//		{
//			speed = -speed;
//		}
//		cleardevice();//system("cls");
//	}
//	getchar();
//	return 0;
//}

