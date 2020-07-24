#include"public.h"
#include"globalFile.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////管理员类功能函数实现接口


//////////////////////////////////////////////
////管理员操作菜单
void Administrator::operMenu(char* _name)
{
	WindowInit("空背景");
	char name[50] = "";
	
	sprintf(name, "欢迎管理员：%s  登录 ", _name);
	settextcolor(RED);
	settextstyle(20, 0, "黑体");//设置字体及大小
	outtextxy(270, 40, name);

	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("您可以进行以下操作：\n\n请选择：\n\n【1】:   添加账号\n\n【2】:   查看账号\n\n【3】:   查看机房\n\n【4】:   清空预约\n\n【5】:   注销登录\n\n【0】:   退出"), &rect, DT_WORDBREAK);
	setcolor(RED);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect1 = { 270, 390, 780, 470 };
	drawtext(_T("\n\n请按回车键进行选择……"), &rect1, DT_WORDBREAK);
}

//////////////////////////////////////////////
//添加账号
int Administrator:: addperson()
{
	start:WindowInit("空背景");
	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("【1】:   添加学生\n\n【2】:   添加老师\n\n【0】:   返回"), &rect, DT_WORDBREAK);
	settextstyle(15, 0, "黑体");
	RECT rect1 = { 270, 180, 780, 470 };
	drawtext(_T("\n\n请按任意键进行选择……"), &rect1, DT_WORDBREAK);
	while (!kbhit())
	{
	}

	char select[2];
	InputBox(select, 2, "请输入选项：");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s))
	{
		InputBox(select, 2, "输入有误，请重新输入：");
		s = (int)select[0];
	}

	string fileName;
	char id[20];
	ofstream ofs;

	switch (s)
	{
	case 49:
	{
			  ////添加学生
		       WindowInit("空背景");
			   fileName = STUDENT_FILE;
			   InputBox(id, 20, "请输入学生学号：");
			   break;
	}

	case 50:
	{
			   ////添加教师
			   WindowInit("空背景");
			   fileName = TEACHER_FILE;
			   InputBox(id, 20, "请输入教师职工号：");
			   break;

	}

	case 48:
		return 0;
		break;
	}

	ofs.open(fileName,ios::out|ios::app);
	char name[20];
	char pwd[20];
	InputBox(name, 20, "请输入用户名：");
	InputBox(pwd, 20, "请输入密码：");

	ofs << id << " " << name << " " << pwd << " " << endl;

	ofs.close();
	
	WindowInit("空背景");
	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect2 = { 270, 100, 780, 470 };
	drawtext(_T("添加成功！"), &rect2, DT_WORDBREAK);
	settextstyle(15, 0, "黑体");
	RECT rect3 = { 270, 100, 780, 470 };
	drawtext(_T("\n\n请按【P】键返回……"), &rect3, DT_WORDBREAK);
	
	while (1)
	{
		int c = getch();
		if (c == 80)
			break;
	}
	char c;
	c=getchar();
	goto start;

}


//////////////////////////////////////////////
//读入学生容器
string Administrator:: initvector_s()
{
	Vstu.clear();
	Vtea.clear();
	string s_Vstu;
	ifstream ifs;
	ifs.open(STUDENT_FILE,ios::in);
	if (!ifs.is_open())
	{
		return "";
	}
	Student s;
	
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		Vstu.push_back(s);
	}
	ifs.close();

	for (int i = 0; i < Vstu.size(); ++i)
	{
		s_Vstu += Vstu[i].m_id;
		s_Vstu += ' ';
		s_Vstu += Vstu[i].m_name;
		s_Vstu += ' ';
		s_Vstu += Vstu[i].m_pwd;
		s_Vstu += "\n\n";
	}

	ifs.close();

	return s_Vstu;
}

//////////////////////////////////////////////
//读入教师容器
string Administrator::initvector_t()
{
	Vstu.clear();
	Vtea.clear();
	string s_Vtea;
	ifstream ifs;
	
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return "";
	}
	Teacher t;

	while (ifs >> t.m_empid && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		Vtea.push_back(t);
	}
	ifs.close();

	for (int i = 0; i < Vtea.size(); ++i)
	{
		s_Vtea += Vtea[i].m_empid;
		s_Vtea += ' ';
		s_Vtea += Vtea[i].m_name;
		s_Vtea += ' ';
		s_Vtea += Vtea[i].m_pwd;
		s_Vtea += "\n\n";
	}

	return s_Vtea;
}

//////////////////////////////////////////////
//查看账号
int Administrator::showperson()
{
start:WindowInit("空背景");
	
	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("【1】:   查看学生账号\n\n【2】:   查看教师账号\n\n【0】:   返回"), &rect, DT_WORDBREAK);
	settextstyle(15, 0, "黑体");
	RECT rect1 = { 270, 180, 780, 470 };
	drawtext(_T("\n\n请按任回车进行选择……"), &rect1, DT_WORDBREAK);
	while (1)
	{
		int c = getch();
		if (c == 13)
			break;
	}

	char select[2];
	InputBox(select, 2, "请输入选项：");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s))
	{
		InputBox(select, 2, "输入有误，请重新输入：");
		s = (int)select[0];
	}

	string fileName;
	ofstream ofs;
	switch (s)
	{
	case 49:
	{
			   ////查看学生账号
			   WindowInit("空背景");
			   string s = initvector_s();
			   char* c_Vstu = (char*)s.c_str();
			   setcolor(RED);//设置文本颜色 
			   settextstyle(20, 0, "黑体");
			   RECT rect = { 30, 30, 780, 470 };
			   drawtext(_T("学生账号信息如下："), &rect, DT_WORDBREAK);

			   RECT rect1 = { 30, 80, 780, 470 };
			   drawtext(_T(c_Vstu), &rect1, DT_WORDBREAK);
			  
			   settextstyle(15, 0, "黑体");
			   RECT rect2 = { 270, 400, 780, 470 };
			   drawtext(_T("\n\n请按【P】键返回……"), &rect2, DT_WORDBREAK);
			   while (1)
			   {
				   int c = getch();
				   if (c == 80)
					   goto start;
			   }
				   break;
	}

	case 50:
	{
			   ////查看教师账号
			   WindowInit("空背景");
			   string s = initvector_t();
			   char* c_Vtea = (char*)s.c_str();
			   setcolor(RED);//设置文本颜色 
			   settextstyle(20, 0, "黑体");
			   RECT rect = { 30, 30, 780, 470 };
			   drawtext(_T("教师账号信息如下："), &rect, DT_WORDBREAK);

			   RECT rect1 = { 30, 80, 780, 470 };
			   drawtext(_T(c_Vtea), &rect1, DT_WORDBREAK);

			   settextstyle(15, 0, "黑体");
			   RECT rect2 = { 270, 400, 780, 470 };
			   drawtext(_T("\n\n请按【P】键返回……"), &rect2, DT_WORDBREAK);
			   while (1)
			   {
				   int c = getch();
				   if (c == 80)
					   goto start;
			   }
			   break;

	}

	case 48:
		return 0;
		break;
	}
}

//////////////////////////////////////////////
//查看机房信息
int Administrator::showcomputer()
{
	
	string s_room = getroom();
	//////显示
	WindowInit("空背景");

	char* c_room = (char*)s_room.c_str();

	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect = { 30, 30, 780, 470 };
	drawtext(_T("机房信息如下：\n\n房间号    容量（人）   已用（人）\n\n"), &rect, DT_WORDBREAK);

	RECT rect1 = { 30, 120, 780, 470 };
	drawtext(_T(c_room), &rect1, DT_WORDBREAK);

	settextstyle(15, 0, "黑体");
	RECT rect2 = { 270, 400, 780, 470 };
	drawtext(_T("\n\n请按【P】键返回……"), &rect2, DT_WORDBREAK);
	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}
	return 1;
}

//////////////////////////////////////////////
//清空预约记录
int Administrator::cleanfile()
{
	ofstream ofs(ORDER_FILE,ios::trunc);
	ofs.close();

	WindowInit("空背景");
	setcolor(RED);//设置文本颜色
	settextstyle(35, 0, "宋体");//设置字体及大小
	outtextxy(270, 130, "预约清空成功！");

	settextstyle(15, 0, "黑体");
	RECT rect2 = { 270, 180, 780, 470 };
	drawtext(_T("\n\n请按【P】键返回……"), &rect2, DT_WORDBREAK);
	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}


	return 1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////管理员菜单
int Administrator:: Administrator_menu(Administrator &ads)
{
	start:char _name[20];
	std::strcpy(_name,ads.m_name.c_str());
	ads.operMenu(_name);
	
	char select[2];
	while (1)
	{
		int c = getch();
		if (c == 13)
			break;
	}
	InputBox(select, 2, "请输入选项：");
	int s = (int)select[0];
	while (!(48 == s || 49 == s || 50 == s || 51 == s || 52 == s || 53 == s))
	{
		InputBox(select, 2, "输入有误，请重新输入：");
		s = (int)select[0];
	}
	switch (s)
	{
	case 49:
	{
			   int m = addperson();
			   if (m == 0)
				   goto start;
			   return 1;
			   break;
	}

	case 50:
	{
			   int m = showperson();
			   if (m == 0)
				   goto start;
			   return 2;
			   break;

	}

	case 51:
	{
			   int m = showcomputer();
			   if (m == 0)
				   goto start;
			 
			   return 3;
			   break;

	}
	case 52:
	{
			   int m = cleanfile();
			   if (m == 0)
				   goto start;
			   return 4;
			   break;

	}
	case 53:
	{
			   WindowInit("空背景");
			   setcolor(RED);//设置文本颜色 
			   settextstyle(20, 0, "黑体");
			   RECT rect = { 270, 120, 780, 470 };
			   drawtext(_T("注销成功！"), &rect, DT_WORDBREAK);
			   settextstyle(15, 0, "黑体");
			   RECT rect1 = { 270, 150, 780, 470 };
			   drawtext(_T("\n\n请按任意键进行退出……"), &rect1, DT_WORDBREAK);
			   while (!kbhit())
			   {
			   }
			   return 0;
			   break;
	}

	case 48:
		return 0;
		break;
	}


}