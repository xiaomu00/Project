#ifndef _PUBLIC_H
#define _PUBLIC_H

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>//光标设置
#include<time.h>//食物随机
#include<conio.h>//按键监控
#include<graphics.h>//图形界面库
//#include<mmsystem.h>//多媒体设备接口
#pragma comment(lib,"Winmm.lib")
using namespace std;



/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////类定义



/////////////////////////////////////////////////////////////////////////////////////////////////////
////机房类
class room
{
public:
	string room_name;
	string count;
	string Used_count;

};



/////////////////////////////////////////////////////////////////////////////////////////////////////
////预约信息类
class order
{
public:
	order()
	{}
	order(string id, string name, string week, string time, string roomid, string state)
	{
		_id = id;
		_name = name;
		_week = week;
		_time = time;
		_roomid = roomid;
		_state = state;
	}
public:
	void Writeorder();//写入预约状态
	static string order::Readorder(int flas, string s_id);//读入预约状态    flas==1,只读自己的信息  flas==2,读全部信息
	string _id;
	string _name;
	string _week;
	string _time;
	string _roomid;
	string _state;//预约状态 0：预约失败     1：预约中   2：预约成功
	int count=0;

};



/////////////////////////////////////////////////////////////////////////////////////////////////////
////身份抽象类
class Identity
{
public:
	////构造函数
	Identity()
	{}
	Identity(string name, string pwd) :m_name(name), m_pwd(pwd)
	{}

	////操作菜单
	virtual void  operMenu(char* _name) = 0;

	string m_name;//用户名
	string m_pwd; //密码
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
////学生类
class Student: public Identity
{
public:
	////构造函数
	Student()
	{}
	Student(string id, string name, string pwd);
	

public:

	

	////操作菜单
	int Student_menu(Student &st);//操作菜单
	virtual void  operMenu(char* _name);;
public:
	////功能函数声明接口
	void showcomputer();
	int applyorder();//申请预约
	int showmyorder();//查看我的预约
	static int showallorder();//查看所有预约
	int cancelorder();//取消预约
	vector<room> Vr;
	string m_id;//学号
	
};


/////////////////////////////////////////////////////////////////////////////////////////////////////
////教师类
class Teacher:public Identity
{
public:
	////构造函数
	Teacher()
	{}
	Teacher(string empid, string name, string pwd) :Identity(name, pwd)
	{
		m_empid = empid;
	}

public:
	////操作菜单
	int Teacher_menu(Teacher &t);//操作菜单
	virtual void  operMenu(char* _name);
	void Modifycomputer(int n);//修改机房信息
public:
	////功能函数声明接口
	int validorder();//审核预约
	int  Marking();//批阅
	string m_empid;//教师职工编号
};


/////////////////////////////////////////////////////////////////////////////////////////////////////
////管理员类
class Administrator:public Identity
{
public:
	////构造函数
	Administrator()
	{}
	Administrator(string name, string pwd) :Identity(name, pwd)
	{
		
	}

public:
	////操作菜单
	int  Administrator_menu(Administrator &ads);//操作菜单
	virtual void  operMenu(char* _name);//显示菜单界面
public:

	////功能函数声明接口
	int addperson();//添加账号
	int showperson();//查看账号
	static int showcomputer();//查看机房信息
	int cleanfile();//清空预约记录


	string initvector_s();//读入学生容器
	string initvector_t();//读入教师容器
	vector<Student> Vstu;
	vector<Teacher> Vtea;
	
};




/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////函数声明接口
void WindowInit(string _s);////初始化窗口
void Login_failed_menu(int s); //验证失败界面
void Main_menu();//主菜单
string getroom();


void printStudent(Student& s);//显示教师信息
void printTeacher(Teacher& t);//显示教师信息


int LoginIn(string filename, int type);//登录函数，参数为要操作的文件和身份。type: 1 学生    2 教师   3管理员    
int LoginIn_Verification(ifstream* ifs, char *name, char *pwd);////学生、教师登录验证







#endif  /*_PUBLIC_H*/