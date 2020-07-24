#include"public.h"
#include"globalFile.h"

int main()
 {


start:Main_menu();////主菜单
	
	char select[2];
	while (1)
	{
		int c = getch();
		if (c ==13)
			break;
	}
    InputBox(select, 2, "请输入选项：");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s || 51 == s))
	{
		InputBox(select, 2, "输入有误，请重新输入：");
		s = (int)select[0];
	}
	switch(s)
	{
	case 49:
	{
			   int s = LoginIn(STUDENT_FILE, 1);
			   if (s == 1)
				   goto start;
			   break;
	}
		
	case 50:
	{
			   bool s = LoginIn(TEACHER_FILE, 2);
			   if (s == 1)
				   goto start;
			   break;

	}

	case 51:
	{
			   bool s = LoginIn(ADMIN_FILE, 3);
			   if (s == 1)
				   goto start;
			   break;

	}
		
	case 48:
		exit(0);
		break;
	}
	return 0;
}













//
//int main()
//{
//	IMAGE img;//定义变量 存放图片
//	loadimage(&img, "1.jpg", 1000, 800);//加载图片
//	initgraph(800, 480);//初始化一个800*480的窗口
//	putimage(0, 0, &img);//将图片作为背景
//	setbkmode(TRANSPARENT);//设置文本背景风格为透明
//
//	setcolor(BLACK);//设置文本颜色
//	settextstyle(45, 0, "宋体");//设置字体及大小
//	outtextxy(350,120,"xiaomu");
//
//	char ch[20];
//	InputBox(ch, 20, "请输入选项：");
//	
//
//	
//	getchar();
//	return 0;
//}