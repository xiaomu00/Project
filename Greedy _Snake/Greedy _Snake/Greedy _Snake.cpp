#include"Greedy _Snake.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////1、数据定义
//////////////////////////////////////////////


////坐标
typedef struct Coor
{
	int x;
	int y;
}Coor;

////蛇的方向
typedef enum ch
{
	up = 72,//上键键值
	down = 80,//下键键值
	left = 75,//左键键值
	right = 77//右键键值
}CH;

//////////////////////////////////////////////
////蛇
typedef struct Snake
{
	//每一节蛇的坐标
	struct Coor scr[Sanke_Size]; //每一节蛇的坐标
	int n;      //蛇的长度
	CH ch;
	int speed = 3;//获取速度
}Snake;

//////////////////////////////////////////////
////食物
typedef struct food
{
	//定位
	Coor fco;//食物坐标
	int flag;//食物状态（是否被吃）
	
}food;
food fo;

Snake Sn;
//////////////////////////////////////////////
////得分
int Score=0; //总得分
int add = 10;//表示每次吃到食物加10分
int Hight_Score =0;//表示历史最高分
int r=0;//颜色变量


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2、模块设计 ——> 功能划分（函数）

////函数实现接口
/////////////////////////////////////////////////////////////////////////////////////////////////
////加载音乐
void Load_music()
{
	////加载一首音乐
	////PlaySound(L"",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);  //wav音乐格式
	////打开MP3音乐
	mciSendString("open mymusic.mp3 alias mymusic", 0, 0, 0);//ARNO是对秋的思念.mp3起的别名
	////循环播放
	mciSendString("play mymusic repeat", 0, 0, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//绘制开始界面
void Start_interface()
{
	IMAGE img;//定义变量 存放图片
	loadimage(&img, "开始界面.jpg", 800, 480);//加载图片
	initgraph(800, 480);//初始化一个800*480的窗口
	putimage(0, 0, &img);//将图片作为背景

	////剪裁一片区域，输入游戏名
	HRGN  rgn = CreateRectRgn(320, 300, 500, 420);
	setcliprgn(rgn);//将上述320, 300, 500, 420的矩形区剪裁出来，作为信息区
	DeleteObject(rgn);//不要占用系统内存
	setcolor(RED);//设置文本颜色
	settextstyle(45, 0, "黑体");//设置字体及大小
	setbkmode(TRANSPARENT);//设置文本背景风格为透明
	outtextxy(330, 320, "贪吃蛇");
	setcolor(RED);//设置文本颜色
	settextstyle(20, 0, "黑体");//设置字体及大小
	outtextxy(400, 390, "——xiaomu");


	////剪裁一片区域，输入菜单选项
	HRGN  rgn1 = CreateRectRgn(585, 65, 800, 480);
	setcliprgn(rgn1);//将上述585, 65,800,480的矩形区剪裁出来，作为信息区
	DeleteObject(rgn1);//不要占用系统内存
	setcolor(LIGHTRED);//设置文本颜色
	settextstyle(18, 0, "黑体");//设置字体及大小
	outtextxy(640, 80, "欢迎来到");
	settextstyle(22, 0, "黑体");//设置字体及大小
	outtextxy(610, 110, "贪吃蛇大作战");
	
	//一种很多文字的输出
	setcolor(BLACK);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect = { 600, 180, 780, 470 };
	drawtext(_T("请选择：\n\n\n【J】:   开始游戏\n\n【K】:   游戏说明\n\n【Esc】: 退出游戏"), &rect, DT_WORDBREAK);

	settextstyle(13, 0, "黑体");
	RECT rect1 = { 610, 330, 750, 470 };
	drawtext(_T("温馨提示：\n\n需要更换音乐时，只需将您喜欢的音乐命名为“mymusic.mp3”后，和运行文件放到同一文件夹即可。"), &rect1, DT_WORDBREAK);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//绘制说明界面
void Description_interface()
{
	IMAGE img;//定义变量 存放图片
	loadimage(&img, "说明界面.jpg", 800, 480);//加载图片
	initgraph(800, 480);//初始化一个800*480的窗口
	putimage(0, 0, &img);//将图片作为背景

	setbkmode(TRANSPARENT);//设置文本背景风格为透明

	////剪裁一片区域，输入菜单选项
	HRGN  rgn1 = CreateRectRgn(0, 0, 800, 480);
	setcliprgn(rgn1);//将上述585, 65,800,480的矩形区剪裁出来，作为信息区
	DeleteObject(rgn1);//不要占用系统内存
	setcolor(RED);//设置文本颜色
	settextstyle(24, 0, "黑体");//设置字体及大小
	outtextxy(340, 80, "游戏说明");

	setcolor(LIGHTRED);//设置文本颜色
	settextstyle(18, 0, "黑体");//设置字体及大小
	outtextxy(230, 110, "游戏规则：");

	//一种很多文字的输出
	setcolor(BLACK);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect = { 270, 140, 800, 480 };
	drawtext(_T("[1]：不能穿墙\n\n[2]：不能撞到自己"), &rect, DT_WORDBREAK);

	setcolor(LIGHTRED);//设置文本颜色
	settextstyle(18, 0, "黑体");//设置字体及大小
	outtextxy(230, 200, "功能及操作方法：");

	//一种很多文字的输出
	setcolor(BLACK);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect1 = { 270, 230, 800, 480 };
	drawtext(_T("[1]：用 ↑、↓、←、→ 控制移动方向\n\n[2]：【W】为加速、【S】为减速\n\n[3]：按空格暂停游戏，再按空格继续游戏\n\n[4]：【P】重新开始\n\n[5]：【Esc】退出游戏\n\n[6]：游戏可记录得分和历史最高分"), &rect1, DT_WORDBREAK);

	setcolor(LIGHTRED);//设置文本颜色
	settextstyle(18, 0, "黑体");//设置字体及大小
	outtextxy(230, 410, "返回：");
	setcolor(LIGHTRED);//设置文本颜色
	outtextxy(280, 410, "【Esc】");
	setcolor(RED);
	settextstyle(40, 0, "黑体");
	RECT rect3 = { 650, 150, 780, 470 };
	drawtext(_T("贪\n\n吃\n\n蛇"), &rect3, DT_WORDBREAK);

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//绘制结束界面
void Game_over(int sh)
{
	IMAGE img;//定义变量 存放图片
	loadimage(&img, "结束界面.jpg", 800, 480);//加载图片
	initgraph(800, 480);//初始化一个800*480的窗口
	putimage(0, 0, &img);//将图片作为背景

	HRGN  rgn = CreateRectRgn(185, 65, 790, 445);
	setcliprgn(rgn);//将上述185, 65, 585, 445的矩形区剪裁出来，作为信息区
	DeleteObject(rgn);//不要占用系统内存
	setcolor(RED);//设置文本颜色
	settextstyle(45, 0, "黑体");//设置字体及大小
	setbkmode(TRANSPARENT);//设置文本背景风格为透明
	outtextxy(270, 100, "Game Over.");

	
	char SP[20] = "";
	sprintf(SP, "您的得分是：:%d ", Score);
	settextcolor(RED);
	settextstyle(18, 0, "黑体");//设置字体及大小
	outtextxy(320, 180, SP);
	

	if (sh > Score)
	{
		char SP1[50] = "";
		sprintf(SP1, "很遗憾，您和历史最高分还差：:%d ", sh - Score);
		settextcolor(RED);
		settextstyle(18, 0, "黑体");//设置字体及大小
		outtextxy(240, 230, SP1);
		Score = 0;
	}
	else
	{
		settextstyle(18, 0, "黑体");
		RECT rect1 = { 270, 230, 600, 350 };
		drawtext(_T("恭喜您，刷新了历史最高分！"), &rect1, DT_WORDBREAK);
	}


	setcolor(RED);//设置文本颜色 
	RECT rect2 = { 250, 330, 780, 470 };
	drawtext(_T("您可以选择重新开始或退出游戏！\n\n      【P】：  重新开始  \n\n      【Esc】：退出游戏  "), &rect2, DT_WORDBREAK);
	settextstyle(40, 0, "黑体");
	RECT rect3 = { 650, 150, 780, 470 };
	drawtext(_T("贪\n\n吃\n\n蛇"), &rect3, DT_WORDBREAK);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//游戏初始化
void GameInIt()
{

	
	IMAGE img;//定义变量 存放图片
	loadimage(&img, "游戏界面.jpg", 800, 480);//加载图片
	initgraph(800, 480);//初始化一个800*480的窗口
	putimage(0, 0, &img);//将图片作为背景

	////剪裁一片区域，作为信息区
	HRGN  rgn = CreateRectRgn(585, 65, 800, 480);
	setcliprgn(rgn);//将上述585, 65,800,480的矩形区剪裁出来，作为信息区
	DeleteObject(rgn);//不要占用系统内存
	setcolor(RED);//设置文本颜色
	settextstyle(30, 0, "黑体");//设置字体及大小
	setbkmode(TRANSPARENT);//设置文本背景风格为透明
	outtextxy(630, 80, "贪吃蛇");
	setcolor(RED);//设置文本颜色
	settextstyle(15, 0, "黑体");//设置字体及大小
	outtextxy(650, 125, "——xiaomu");



	//一种很多文字的输出
	setcolor(BLACK);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect = { 600, 280, 780, 470 };
	drawtext(_T("游戏说明：\n\n方向键: 控制方向\n\n空格：  暂停/继续\n\n【P】:  重新开始\n\n【ESC】:结束游戏\n\n【W】加速【S】减速"), &rect, DT_WORDBREAK);

	

	////对蛇初始化
	//cleardevice();//清屏
	Sn.scr[0].x = 185;
	Sn.scr[0].y = 65;
	Sn.ch = right;//方向为右
	Sn.n = 2;//长度为2+1
	Sn.speed = 3;//速度为5-3
	fo.flag = 0;//被吃了
	Score = 0;//分数为0
	Hight_Score = Hight_Score_out();//历史最高分为文件存储的最高分

	setfillcolor(LIGHTCYAN);
	fillrectangle(185, 65, 195, 75);
	

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//用不同颜色绘制一节蛇
void DrawSnake_1(int i)
{
	switch (r)
	{
	case 0:
		rectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 1;
		break;
	case 1:
		setfillcolor(LIGHTCYAN);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 2;
		break;
	case 2:
		setfillcolor(LIGHTBLUE);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 3;
		break;
	case 3:
		setfillcolor(LIGHTGREEN);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 4;
		break;
	case 4:
		setfillcolor(LIGHTMAGENTA);
		fillrectangle(Sn.scr[i].x, Sn.scr[i].y, Sn.scr[i].x + 10, Sn.scr[i].y + 10);
		r = 0;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//绘制n节蛇
void DrawSnake()
{	
	for (int i = Sn.n; i >= 0;i--)
	{
		DrawSnake_1(i);
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//蛇的移动
void SnakeMove()
{
	
	for (int i = Sn.n; i > 0; i--)
	{
		Sn.scr[i].x = Sn.scr[i-1].x;
		Sn.scr[i].y = Sn.scr[i - 1].y;
	}
	
	switch (Sn.ch)
	{
	case up:
		Sn.scr[0].y -= 10;
		break;
	case down:
		Sn.scr[0].y += 10;
		break;
	case left:
		Sn.scr[0].x -= 10;
		break;
	case right:
		Sn.scr[0].x += 10;
		break;
	}
	DrawSnake();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//改变方向
void Changch(char input)
{
	
	input = getch();
	switch (input)
	{
	case up:
		if (Sn.ch != down)
		Sn.ch = up;
		break;
	case down:
		if (Sn.ch != up)
		Sn.ch = down;
		break;
	case left:
		if (Sn.ch != right)
		Sn.ch = left;
		break;
	case right:
		if (Sn.ch != left)
		Sn.ch = right;
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//计算食物坐标食物
void CreateFood()
{
	srand(unsigned int (time(NULL)));

	fo.fco.x = 185+ (rand() % ((585 - 185) /10)) * 10;
	fo.fco.y = 65 + (rand() % ((445 - 65) / 10)) * 10;
	fo.flag = 1;//没被吃
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//绘制食物
void DrawFood()
{
	setlinecolor(RED);
	roundrect(fo.fco.x, fo.fco.y, fo.fco.x + 10,fo.fco.y + 10, 10,10);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//判断食物是否被吃食物
int eatFood()
{
	if (Sn.scr[0].x == fo.fco.x && Sn.scr[0].y == fo.fco.y)
	{
		Score += add;
		Sn.n++;
		
		if (Score > Hight_Score)
		{
			Hight_Score += add;
		}

		fo.flag = 0;
		return fo.flag;
	}

	else
		return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//蛇的状态——判断是否结束游戏
int  SnakeStatus()
{
	if (Sn.scr[0].x<185 || Sn.scr[0].x>575|| Sn.scr[0].y<65 || Sn.scr[0].y>440)//撞墙结束
	{
		return 0;
	}
		
	else
	{
		for (int i = 1; i <= Sn.n; ++i)
		{
			if (Sn.scr[0].x == Sn.scr[i].x && Sn.scr[0].y == Sn.scr[i].y)
			{
				return 0;
			}
				
		}

		return 1;

	}
	
}

//获取速度
int  myspeed()
{
	return Sn.speed;
}

//改变速度
void Changespeed(char c)
{
	if (c == 87 || c == 119)
	{
		if (Sn.speed>0)
			Sn.speed--;
	}
		
	else if (Sn.speed<4)
	{
		 Sn.speed++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//显示状态栏
void ShowStatus_bar()
{
	Sleep(100);

	////剪裁一片区域，作为信息区
	HRGN  rgn = CreateRectRgn(609, 140, 760, 270);
	setcliprgn(rgn);//将上述609, 120, 800, 250的矩形区剪裁出来，作为得分区
	//setbkcolor(WHITE);
	setfillcolor(WHITE);
	solidrectangle(609, 120, 800, 270);	
	DeleteObject(rgn);//不要占用系统内存
	setbkmode(TRANSPARENT);//设置文本背景风格为透明
	

	char SP[20] = "";
	sprintf(SP, "速度：:%d ", 5-Sn.speed);
	settextcolor(RED);
	settextstyle(15, 0, "黑体");//设置字体及大小
	outtextxy(610, 165, SP);
	
	char n[20] = "";
	sprintf(n, "长度：:%d ", Sn.n+1);
	settextcolor(RED);
	settextstyle(15, 0, "黑体");//设置字体及大小
	outtextxy(610, 190, n);

	char S[20] = "";
	sprintf(S, "得分：:%d ", Score);
	settextcolor(RED);
	settextstyle(15, 0, "黑体");//设置字体及大小
	outtextxy(610, 215, S);
	
	char H_S[20] = "";
	sprintf(H_S, "历史最高分：%d ", Hight_Score);
	settextcolor(RED);
	settextstyle(15, 0, "黑体");//设置字体及大小
	outtextxy(610, 240, H_S);


	////剪裁区域，作为游戏区
	HRGN  rgn1 = CreateRectRgn(185, 65, 585, 445);
	setcliprgn(rgn1);//将上述185, 65, 585, 445的矩形区剪裁出来，作为游戏区
	DeleteObject(rgn1);//不要占用系统内存
	solidrectangle(185, 65, 585, 445);
	setbkcolor(WHITE);


	

}

//获取当前最高分
int myHight_Score()
{
	return Hight_Score;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//将最高分写入文件
void Hight_Score_in()
{
	FILE *fp = fopen("Hight_Score.txt", "w");
	if (NULL != fp)
	{
		fprintf(fp, "%d", Hight_Score);
	}
	
	fclose(fp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//将文件里的分数读出
int Hight_Score_out()
{
	int s = 0;
	FILE *fp = fopen("Hight_Score.txt","r");
	if (NULL != fp)
	{
		fscanf(fp,"%d",&s);
	}
	fclose(fp);
	return s;
}