#include"public.h"
#include"globalFile.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////教师类功能函数实现接口

extern order odr;


//////////////////////////////////////////////
////教师操作菜单
void Teacher::operMenu(char* _name)
{
	WindowInit("空背景");
	char name[50] = "";

	sprintf(name, "欢迎教师：%s  登录 ", _name);
	settextcolor(RED);
	settextstyle(20, 0, "黑体");//设置字体及大小
	outtextxy(270, 40, name);

	setcolor(RED);//设置文本颜色 
	settextstyle(20, 0, "黑体");
	RECT rect = { 270, 100, 780, 470 };
	drawtext(_T("您可以进行以下操作：\n\n请选择：\n\n【1】:   查看所有预约\n\n【2】:   审核预约\n\n【0】:   退出"), &rect, DT_WORDBREAK);
	setcolor(RED);//设置文本颜色 
	settextstyle(15, 0, "黑体");
	RECT rect1 = { 270, 290, 780, 470 };
	drawtext(_T("\n\n请按回车键进行选择……"), &rect1, DT_WORDBREAK);
}



//////////////////////////////////////////////
//修改机房信息
void Teacher:: Modifycomputer(int n)
{
	queue<room> q;
	ifstream ifs;
	fstream ofs;
	room om;

	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return;
	}

	int i = 1;
	while (ifs >> om.room_name && ifs >> om.count && ifs >> om.Used_count)
	{
		if (i != n)
		{
			q.push(om);
		}
		else
		{
			const char *r = om.Used_count.c_str();
			int a = atoi(r);
			char b[5];
			string s;
			a++;
			itoa(a, b, 10);
			int i = 0;
			while (b[i] != '\0')
			{
				s.push_back(b[i]);
				++i;
			}

			om.Used_count = s;
			q.push(om);
		}

		i++;
	}

	ifs.close();

	ofs.open(COMPUTER_FILE, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		return;
	}

	ofs.close();


	while(!q.empty())
	{
		room tmp = q.front();
		q.pop();

		/////写入预约文件中
		ofstream ofs(COMPUTER_FILE, ios::app);
		ofs << tmp.room_name << " " << tmp.count << " " << tmp.Used_count << endl;
		
		ofs.close();
	}

}



//////////////////////////////////////////////
//批阅
int Teacher:: Marking()
{

	char select[2];
	InputBox(select, 2, "请输入要批阅的编号：");

	int s = (int)select[0]-48;



	while (s>odr.count)
	{
		InputBox(select, 2, "输入有误，请重新输入：");
		s = (int)select[0]-48;
	}


	ifstream ifs;
	order or;
	order tmpr;
	fstream ofs;
	queue<order> q;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		return 0;
	}


	int i = 1;
	while (ifs >> or._id && ifs >> or._name && ifs >> or._week
		&& ifs >> or._time && ifs >> or._roomid && ifs >> or._state)
	{

		if (i != s)
		    q.push(or);

		else
		{
			char se[2];
			InputBox(se, 2, "您确定通过该学生的申请吗？：（Y or N）");

			int s = (int)se[0];

			while (!(78 == s || 110 == s || 89 == s || 121 == s))
			{
				InputBox(se, 2, "输入有误，请重新输入：（Y or N）");
				int s = (int)se[0];
			}

			if (78 == s || 110 == s)
			{
				or._state = '0';
				tmpr = or;

				WindowInit("空背景");
				setcolor(RED);//设置文本颜色
				settextstyle(35, 0, "宋体");//设置字体及大小
				outtextxy(170, 130, "已拒绝该条预约！");
				settextstyle(15, 0, "宋体");//设置字体及大小
				outtextxy(170, 170, "按【P】键返回");
			}
			else
			{
				or._state = '2';
				tmpr = or;

				const char *c = or._roomid.c_str();
				int a = atoi(c);
				
				Modifycomputer(a);

				WindowInit("空背景");
				setcolor(RED);//设置文本颜色
				settextstyle(35, 0, "宋体");//设置字体及大小
				outtextxy(170, 130, "已同意该条预约！");
				settextstyle(15, 0, "宋体");//设置字体及大小
				outtextxy(170, 170, "按【P】键返回");
			}
		}
		i++;
	}

	ifs.close();

	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	if (!ofs.is_open())
	{
		return 0;
	}

	ofs.close();
	while (!q.empty())
	{
		order tmp = q.front();
		q.pop();

		tmp.Writeorder();
	}
	tmpr.Writeorder();


	
		while (1)
		{
			int c = getch();
			if (c == 80)
				return 0;
		}

	return 0;
}
	


//////////////////////////////////////////////
//审核预约
int Teacher:: validorder()
{
	start:string s_order = order::Readorder(2, "");
	//////显示
	WindowInit("空背景");

	char* c_order = (char*)s_order.c_str();

	setcolor(RED);//设置文本颜色 
	settextstyle(30, 0, "黑体");
	RECT rect = { 270, 30, 780, 470 };
	drawtext(_T("预约信息"), &rect, DT_WORDBREAK);

	settextstyle(20, 0, "黑体");
	RECT rect1 = { 30, 70, 780, 470 };
	drawtext(_T("预约信息如下：\n\n编号  学号   姓名      星期      时间    房间号   预约状态\n\n"), &rect1, DT_WORDBREAK);

	RECT rect2 = { 30, 160, 780, 470 };
	drawtext(_T(c_order), &rect2, DT_WORDBREAK);

	settextstyle(15, 0, "黑体");
	RECT rect3 = { 30, 390, 780, 470 };
	drawtext(_T("\n\n按【P】键查看机房信息\n\n按回车键进行批阅……"), &rect3, DT_WORDBREAK);

	while (1)
	{
		int m;
		int c = getch();
		if (c == 80)
		{
			Administrator::showcomputer();
			goto start;
		}
		else if (c == 13)
			m=Marking();
		if (m == 0)
			break;
	}
	return 0;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////教师菜单
int Teacher::Teacher_menu(Teacher &t)
{
start:char _name[20];
	WindowInit("空背景");
	std::strcpy(_name, t.m_name.c_str());
	t.operMenu(_name);

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
			   int m = Student::showallorder();
			   if (m == 0)
				   goto start;
			   return 1;
			   break;
	}

	case 50:
	{
			   int m =  validorder();
			   if (m == 0)
				   goto start;
			   return 2;
			   break;

	}
	
	case 48:
		return 0;
		break;
	}

	return 1;
}

