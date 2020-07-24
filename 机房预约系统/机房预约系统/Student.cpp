#include"public.h"
#include"globalFile.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////学生类功能函数实现接口

order odr;

////有参构造
Student::Student(string id, string name, string pwd)
{
	m_id = id;
	m_name = name;
	m_pwd = pwd;

	//获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	room r;
	while (ifs >> r.room_name&&ifs >> r.count&&ifs >> r.Used_count)
	{
		Vr.push_back(r);
	}

	ifs.close();

}

//////////////////////////////////////////////
//显示机房信息
void Student::showcomputer()
{
	string s_room = getroom();
	//////显示
	WindowInit("空背景");

	char* c_room = (char*)s_room.c_str();

	setcolor(RED);//设置文本颜色 
	settextstyle(30, 0, "黑体");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("机房选择界面"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "黑体");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("机房信息如下：\n\n房间号    容量（人）   已用（人）\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_room), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "黑体");
	RECT rect3 = { 30, 240, 780, 470 };
	drawtext(_T("\n\n请按回车键键进行选择……"), &rect3, DT_WORDBREAK);
	
}

//////////////////////////////////////////////
//写入预约状态
void order::Writeorder()
{
	/////写入预约文件中
	ofstream ofs(ORDER_FILE, ios::app);
	ofs << _id << " " << _name << " ";
	ofs << _week << " " << _time << " ";
	ofs << _roomid << " " << _state << endl;//1代表审核中

	ofs.close();
}



//////////////////////////////////////////////
//读入预约状态    flas==1,只读自己的信息  flas==2,读全部信息
string order::Readorder(int flas, string s_id)
{
	string outodr;
	ifstream ifs;
	vector<order> Vo;

	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return 0;
	}
	if (flas == 1)
	{
		while (ifs >> odr._id && ifs >> odr._name && ifs >> odr._week
			&& ifs >> odr._time && ifs >> odr._roomid && ifs >> odr._state)
		{
			if (odr._id == s_id)
			{
				if (odr._state[0] == '0')
					odr._state = "预约失败";
				else if (odr._state[0] == '1')
					odr._state = "预约中";
				else
					odr._state = "预约成功";
				
				Vo.push_back(odr);
				
			}
				
		}

		ifs.close();
	}
	else if (flas==2)
	{
		while (ifs >> odr._id && ifs >> odr._name && ifs >> odr._week
			&& ifs >> odr._time && ifs >> odr._roomid && ifs >> odr._state)
		{
			if (odr._state[0] == '0')
				odr._state = "预约失败";
			else if (odr._state[0] == '1')
				odr._state = "预约中";
			else
				odr._state = "预约成功";
				Vo.push_back(odr);
				odr.count++;
		}
		ifs.close();
	}


	for (int i = 0; i < Vo.size(); ++i)
	{

		char m[2];
		itoa(i+1, m, 10);
		outodr += m;
		outodr += "      ";
		outodr += Vo[i]._id;
		outodr += "      ";
		outodr += Vo[i]._name;
		outodr += "      ";
		outodr += Vo[i]._week;
		outodr += "      ";
		outodr += Vo[i]._time;
		outodr += "      ";
		outodr += Vo[i]._roomid;
		outodr += "      ";
		outodr += Vo[i]._state;
		outodr += "\n\n";

	}

	return outodr;

}



//////////////////////////////////////////////
////学生操作菜单
void Student::operMenu(char* _name)
{
	WindowInit("空背景");
	char name[50] = "";

	sprintf(name, "欢迎学生：%s  登录 ", _name);
	settextcolor(RED);
	settextstyle(20, 0, "黑体");//设置字体及大小
	outtextxy(270, 40, name);

	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("您可以进行以下操作：\n\n请选择：\n\n【1】:   申请预约\n\n【2】:   查看我的预约\n\n【3】:   查看所有预约\n\n【4】:   注销登录\n\n【0】:   退出"), &rect, DT_WORDBREAK);
	setcolor(RED);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect1 = { 270, 390, 780, 470 };
	drawtext(_T("\n\n请按回车键进行选择……"), &rect1, DT_WORDBREAK);

}



//////////////////////////////////////////////
//////申请预约	
int Student:: applyorder()
{

	WindowInit("空背景");
	char week[20];
	char time[20];
	char room[2];

	InputBox(week, 20, "请输入日期（周一 ~ 周五）：");

	while (strcmp(week, "周一") && strcmp(week, "周二") && strcmp(week, "周三") && strcmp(week, "周四") && strcmp(week, "周五") )
	{
		InputBox(week, 20, "输入有误，请重新输入（周一 ~ 周五）：");
	}

	InputBox(time, 20, "请输入时间 （上午或下午）：");

	while (strcmp(time, "上午") && strcmp(time, "下午"))
	{
		InputBox(time, 20, "输入有误，请重新输入 （上午或下午）：");
	}

	showcomputer();

	while (1)
	{
		int c = getch();
		if (c == 13)
			break;
	}

	InputBox(room, 2, "请输入房间号（1~3）：");

	while (strcmp(room, "1") && strcmp(room, "2") && strcmp(room, "3"))
	{
		InputBox(room, 2, "输入有误，请重新输入 （1~3）：");
	}

	WindowInit("空背景");
	setcolor(RED);//设置文本颜色
	settextstyle(35, 0, "宋体");//设置字体及大小
	outtextxy(170, 130, "预约成功，等待审核中！");
	settextstyle(15, 0, "宋体");
	outtextxy(270, 190, "请按【P】退出");

	/////写入预约文件中
	ofstream ofs(ORDER_FILE, ios::app);

	order or(m_id, m_name, week, time, room, "1");

	or.Writeorder();

	while (1)
	{
		int c = getch();
		if (c == 80)
			break;
	}

	return 0;
}

//////////////////////////////////////////////
//查看我的预约
int Student::showmyorder()
{
	string s_order = order::Readorder(1,m_id);
	//////显示
	WindowInit("空背景");

	char* c_order = (char*)s_order.c_str();

	setcolor(RED);//设置文本颜色 
	settextstyle(30, 0, "黑体");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("我的预约信息"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "黑体");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("预约信息如下：\n\n编号  学号   姓名      星期      时间    房间号   预约状态\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_order), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "黑体");
	RECT rect3 = { 30, 390, 780, 470 };
	drawtext(_T("\n\n请按【P】键返回……"), &rect3, DT_WORDBREAK);

	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}

}




//////////////////////////////////////////////
//查看所有预约
int Student::showallorder()
{
	string s_order = order::Readorder(2,"");
	//////显示
	WindowInit("空背景");

	char* c_order = (char*)s_order.c_str();

	setcolor(RED);//设置文本颜色 
	settextstyle(30, 0, "黑体");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("所有预约信息"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "黑体");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("预约信息如下：\n\n编号  学号   姓名      星期      时间    房间号   预约状态\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_order), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "黑体");
	RECT rect3 = { 30, 390, 780, 470 };
	drawtext(_T("\n\n请按【P】键返回……"), &rect3, DT_WORDBREAK);

	while (1)
	{
		int c = getch();
		if (c == 80)
			return 0;
	}

}

//////////////////////////////////////////////
//取消预约
int Student::cancelorder()
{
	return 0;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////学生菜单
int Student::Student_menu(Student &st)
{
start:char _name[20];
	WindowInit("空背景");
	std::strcpy(_name, st.m_name.c_str());
	st.operMenu(_name);

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
			   int m = applyorder();
			   if (m == 0)
				   goto start;
			   return 1;
			   break;
	}

	case 50:
	{
			   int m = showmyorder();
			   if (m == 0)
				   goto start;
			   return 2;
			   break;

	}

	case 51:
	{
			   int m = showallorder();
			   if (m == 0)
				   goto start;

			   return 3;
			   break;

	}
	case 52:
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

	return 1;
}

