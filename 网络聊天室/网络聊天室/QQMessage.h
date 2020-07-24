#pragma once
class QQMessage
{
public:
	QQMessage();
	~QQMessage();
	

	//为这个类写一个入口
	static QQMessage *Instance()
	{
		static QQMessage object;//创建对象并返回
		return &object;
	}

	//为功能函数写一个入口,用*msg接受要发送的消息
	void start(const wchar_t *msg);


private:
	//开启一个线程
	static unsigned int WINAPI RunThredProc(void* parm);

	//发送的流程
	void SendAll();

	//模拟按键
	void PreesKey(BYTE vkey);

	//发送消息
	void SendMsg();

	//需要把消息拷贝
	void AaaToClipBoard();

private:
	CString m_msg;

};

