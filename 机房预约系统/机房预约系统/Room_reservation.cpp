#include"public.h"
#include"globalFile.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////函数实现接口

///////////////////////////////////////////////////////////
////初始化窗口
void WindowInit(string _s)
{
	IMAGE img;//定义变量 存放图片
	int s=0;
	char* str = new char[_s.length() + 1];
	std::strcpy(str, _s.c_str());
	if (!(strcmp(str, "主界面")))
	{s = 1;}
	if (!(strcmp(str, "空背景")))
	{s = 2;}
	switch (s)
	{
	case 1:
		loadimage(&img, "主界面.jpg", 800, 480);//加载图片
		break;
	case 2:
		loadimage(&img, "空背景.jpg", 800, 480);//加载图片
		break;

	default:
		break;
	}
	initgraph(800, 480);//初始化一个800*480的窗口
	putimage(0, 0, &img);//将图片作为背景
	setbkmode(TRANSPARENT);//设置文本背景风格为透明
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
////界面

///////////////////////////////////
////主菜单
void Main_menu()
{
	string s = "主界面";
	WindowInit(s);
	setcolor(RED);//设置文本颜色
	settextstyle(35, 0, "宋体");//设置字体及大小
	outtextxy(170, 130, "欢迎来到xiaomu机房预约系统");

	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect = { 290, 190, 780, 470 };
	drawtext(_T("请选择：\n\n【1】:   学    生\n\n【2】:   教    师\n\n【3】:   管 理 员\n\n【0】:   退出游戏"), &rect, DT_WORDBREAK);
	setcolor(RED);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect1 = { 300, 370, 780, 470 };
	drawtext(_T("\n\n请按回车键进行选择……"), &rect1, DT_WORDBREAK);
	
}

///////////////////////////////////
////验证失败界面
void Login_failed_menu()
{
	WindowInit("空背景");
	setcolor(RED);//设置文本颜色
	settextstyle(35, 0, "宋体");//设置字体及大小
	outtextxy(170, 130, "登录失败，用户不存在！");
	
	
}


////将字符型转化为int型
int c_s(char*  id)
{
	int i = 0;
	int s = 0;
	while (id[i] != '\0')
	{
		s = s * 10 + id[i] - '0';
		++i;
	}
	return s;
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
////登录

////学生、教师登录验证
int LoginIn_Verification(ifstream* ifs, char* id, char *name, char *pwd)
{
	char fid[20];
	char fname[20] ;
	char fpwd[20];
	while (*ifs >> fid && *ifs >> fname && *ifs >> fpwd)
	{	
		while (!strcmp(id, fid) && !strcmp(name, fname))//编号和用户名相等
		{
			while (strcmp(pwd, fpwd))//密码不相等，即密码错误时进入循环。
			{
				InputBox(pwd, 20, "密码错误，请重新输入密码（按Q退出）：");
				char a[2] = { 'Q', '\0' };
				if (!strcmp(pwd, a))
					return 1;
				else if (!strcmp(pwd, fpwd))
				{
					break;
				}
			}
			return 0;
		}	
	}

	Login_failed_menu();//登录失败界面
	while (!kbhit())//无按键按下，进入循环
	{
	}
	return 1;

}

////管理员登录验证
int LoginIn_Administrator(ifstream* ifs, char *name, char *pwd)
{
	char fname[20];
	char fpwd[20];
	while ( *ifs >> fname && *ifs >> fpwd)
	{
		while (!strcmp(name, fname))//用户名相等
		{
			while (strcmp(pwd, fpwd))//密码不相等，即密码错误时进入循环。
			{
				InputBox(pwd, 20, "密码错误，请重新输入密码（按Q退出）：");
				char a[2] = { 'Q', '\0' };
				if (!strcmp(pwd, a))
					return 1;
				else if (!strcmp(pwd, fpwd))
				{
					break;
				}

			}
			return 0;
		}
	}
	if (strcmp(name, fname))//用户不存在
	{
		Login_failed_menu();//登录失败界面
		while (!kbhit())//无按键按下，进入循环
		{
		}
		return 1;
	}
}


//登录函数，参数为要操作的文件和身份。type: 1 学生    2 教师   3管理员 
int LoginIn(string fileName, int type)
{
	WindowInit("空背景");
	Identity *person = nullptr;
	ifstream ifs;
	ifs.open(fileName,ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return false;
	}

	char id[20];
	char name[20];
	char pwd[20];

	/*string name;
	string pwd;*/

	if (1 == type)
	{
		InputBox(id, 20, "请输入学生学号：");
	}
	else if (2 == type)
	{
		InputBox(id, 20, "请输入教师职工号：");
	}


	InputBox(name, 20, "请输入用户名：");
    InputBox(pwd, 20, "请输入密码：");
	int s;
	if (1 == type)
	{
		////学生验证
		s = LoginIn_Verification(&ifs, id, name, pwd);
		if (!s)
		{
			////学生功能实现
			Student* st;
			st = new Student(id,name, pwd);
			int m = (*st).Student_menu(*st);
		    if (m == 0)
				s = 1;
		}
		
	}
	else if (2 == type)
	{
		////教师验证
		s = LoginIn_Verification(&ifs, id, name, pwd); 
		if (!s)
		{
			////教师功能实现
			Teacher* t;
			t = new Teacher(id, name, pwd);
			int m = (*t).Teacher_menu(*t);
			if (m == 0)
				s = 1;
		}
		
		
	}
	else if (3 == type)
	{
		////管理员验证
		

		s = LoginIn_Administrator(&ifs, name, pwd);
		if (!s)
		{
			////管理员功能实现
			Administrator* ads;
			ads = new Administrator(name, pwd);
			int m = (*ads).Administrator_menu(*ads);
			if (m == 5)
				delete ads;
			else if (m == 0)
				s = 1;

		}
		
	}
	//setcolor(RED);//设置文本颜色
	//settextstyle(35, 0, "宋体");//设置字体及大小
	//outtextxy(170, 130, "登录验证失败");
	//system("pause");
	return s;
}


////////////////////////////////////////////////////////////////////////////////////////
////获取机房信息并转换
string getroom()
{
	///////初始化
	room r;
	ifstream ifs;
	vector<room> Vr;
	string s;

	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return 0;
	}

	while (ifs >> r.room_name && ifs >> r.count&& ifs >> r.Used_count)
	{
		Vr.push_back(r);
	}
	ifs.close();

	for (int i = 0; i < Vr.size(); ++i)
	{
		s += Vr[i].room_name;
		s += "            ";
		s += Vr[i].count;
		s += "            ";
		s += Vr[i].Used_count;
		s += "\n\n";
	}
	return s;
}