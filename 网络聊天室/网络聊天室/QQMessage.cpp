#include "stdafx.h"
#include "QQMessage.h"
//实现群发功能

QQMessage::QQMessage()
{
}


QQMessage::~QQMessage()
{
}


////////////////////////////////////////////////////////////////////////////////////////
//为功能函数写一个入口,用*msg接受要发送的消息
void QQMessage::start(const wchar_t *msg)
{
	//保存需要发送的消息
	m_msg = CString(msg);

	//创建一个线程
	_beginthreadex(NULL,0,QQMessage::RunThredProc,NULL,0,NULL);
}



////////////////////////////////////////////////////////////////////////////////////////
//开启一个线程
unsigned int QQMessage::RunThredProc(void* parm)
{
	QQMessage::Instance()->SendAll();   //开启发送流程
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////
//发送的流程
void QQMessage:: SendAll()
{
	//将消息粘贴到粘贴板
	AaaToClipBoard();
	
    int fals = 1;
	//1.找到窗口   FindWindow(L"窗口的类名称",L"标题");
	HWND qqhend = FindWindow(L"TXGuiFoundation", L"QQ");

	//2.找到的qq窗口是不是在桌面的最前方 
	HWND fronthwnd = GetForegroundWindow();
	if (qqhend != fronthwnd)  //判断qq窗口是不是在桌面的最前方 
	{
		if (!SetForegroundWindow(qqhend))//如果不在最前方 ，需要将qq窗口放到最前方 
		{
			MessageBox(NULL, L"找不到QQ窗口", NULL, NULL);
		}
	}

	int group = 1;
	
	//模拟按键Tab Tab
	PreesKey(VK_TAB);
	PreesKey(VK_TAB);

	PreesKey(VK_DOWN);
	//模拟按键回车	
	PreesKey(VK_RETURN);

	while (1)
	{
		//模拟按键Down
		PreesKey(VK_DOWN);
		//模拟按键回车	
		PreesKey(VK_RETURN);
		//模拟按键Down
		PreesKey(VK_DOWN);
		//模拟按键回车	
		PreesKey(VK_RETURN);

		HWND curhwnd = GetForegroundWindow();
		if (curhwnd==qqhend)
		{
			MessageBox(NULL, L"已发送完毕！", NULL, NULL);
			break;
		}

	    ///////////////////////////////////////////////////////////////
		//到这里已经打开联系人了

		////发送消息
		SendMsg();
		//模拟按键Tab Tab
		PreesKey(VK_TAB);
		PreesKey(VK_TAB);
	}

}


////////////////////////////////////////////////////////////////////////////////////////
//模拟按键
void QQMessage:: PreesKey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);  //模拟一个按键  按下
	Sleep(100);
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);  //模拟一个按键  弹起
	Sleep(100);
}


////////////////////////////////////////////////////////////////////////////////////////
//发送消息
void QQMessage:: SendMsg()
{
	/////////////////////////////////////
	//Ctrl+V

	//模拟Ctrl 按下
	keybd_event(VK_CONTROL, 0, 0, 0); 
	Sleep(100);
	//模拟V 按下
	keybd_event(0x56, 0, 0, 0);
	Sleep(100);

	//模拟V 弹起
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	//模拟Ctrl弹起
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);

	/////////////////////////////////////////////
	//回车键发送  
	PreesKey(VK_RETURN);

	//模拟ESC退出
	PreesKey(VK_ESCAPE);
}


////////////////////////////////////////////////////////////////////////////////////////
//需要把消息拷贝
void QQMessage:: AaaToClipBoard()
{
	int memLenth = m_msg.GetLength()*sizeof(wchar_t)+2;
	HANDLE hGlobalMenory = GlobalAlloc(GHND,memLenth);
	void* memAddr = GlobalLock(hGlobalMenory);
	ZeroMemory(memAddr,memLenth);

	memcpy(memAddr,(const void*)m_msg.GetBuffer(),memLenth);

	GlobalUnlock(hGlobalMenory);

	//剪贴板操作
	::OpenClipboard(NULL);
	::EmptyClipboard();
	::SetClipboardData(CF_UNICODETEXT,hGlobalMenory);
	::CloseClipboard();
}