
// 音乐播放器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "音乐播放器.h"
#include "音乐播放器Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C音乐播放器Dlg 对话框



C音乐播放器Dlg::C音乐播放器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C音乐播放器Dlg::IDD, pParent)
	, m_nVolume(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C音乐播放器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_EDIT1, m_nVolume);
}

BEGIN_MESSAGE_MAP(C音乐播放器Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &C音乐播放器Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_PLAY, &C音乐播放器Dlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_PAUSE, &C音乐播放器Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_STOP, &C音乐播放器Dlg::OnBnClickedStop)
	ON_WM_DROPFILES()
	
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &C音乐播放器Dlg::OnCustomdrawSlider1)
END_MESSAGE_MAP()


// C音乐播放器Dlg 消息处理程序

BOOL C音乐播放器Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	
	m_slider.SetRange(0,1000);
	m_slider.SetPos(500);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C音乐播放器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CPaintDC dc(this);
		//获取客户端宽度
		CRect rect;
		GetClientRect(&rect);

		//加载一张图片
		CBitmap bmp;
		bmp.LoadBitmap(IDB_MAIN_BJ);
		

		//获取图片大小
		BITMAP logBmp;
		bmp.GetBitmap(&logBmp);

		//创建内存DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject(&bmp);
		//绘制到界面
		//dc.BitBlt(0, 0, rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
		dc.SetStretchBltMode(HALFTONE);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0,
			logBmp.bmWidth, logBmp.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C音乐播放器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



////////////////////////////////////////////////////
////打开
void C音乐播放器Dlg::OnBnClickedOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE);
	dlg.DoModal();

	//获取选择的文件的路径
	CString strmusicPath = dlg.GetPathName();

	//1. 关闭上一个音乐
	//多媒体设备接口（MCI）
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);


	//2. 打开音乐文件
	MCI_OPEN_PARMS mciopenparms;
	mciopenparms.lpstrElementName = strmusicPath;
	MCIERROR mciError;
	mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&mciopenparms);
	if (mciError)//mciError为真时，说明打开失败
	{
		wchar_t szErrorMsg[256];
		mciGetErrorString(mciError, szErrorMsg, 256);//获取错误信息
		AfxMessageBox(szErrorMsg);//弹出错误信息
		return;
	}
	m_DeviceID = mciopenparms.wDeviceID;//
}


////////////////////////////////////////////////////
////播放
void C音乐播放器Dlg::OnBnClickedPlay()
{
	// TODO:  在此添加控件通知处理程序代码
	MCI_PLAY_PARMS mcipalyparms;
	mcipalyparms.dwCallback = NULL;
	mcipalyparms.dwFrom = 0;//从头开始播放
	mciSendCommand(m_DeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)&mcipalyparms);
}


////////////////////////////////////////////////////
////暂停/继续
void C音乐播放器Dlg::OnBnClickedPause()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_PAUSE, str);
	if (str == L"暂停")
	{
		mciSendCommand(m_DeviceID, MCI_PAUSE, 0, 0);
		SetDlgItemText(IDC_PAUSE, L"继续");
	}
	else if (str == L"继续")
	{
		mciSendCommand(m_DeviceID, MCI_RESUME, 0, 0);
		SetDlgItemText(IDC_PAUSE, L"暂停");
	}
}


////////////////////////////////////////////////////
////停止
void C音乐播放器Dlg::OnBnClickedStop()
{
	// TODO:  在此添加控件通知处理程序代码
	mciSendCommand(m_DeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
}



void C音乐播放器Dlg::OnDropFiles(HDROP hDropInfo)
{
	// 获取拖拽文件的路径
	wchar_t szMusicPath[256];
	DragQueryFile(hDropInfo, 0, szMusicPath, 256);
	//AfxMessageBox(szMusicPath);


	//1. 关闭上一个音乐
	//多媒体设备接口（MCI）
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);


	//2. 打开音乐文件
	MCI_OPEN_PARMS mciopenparms;
	mciopenparms.lpstrElementName = szMusicPath;
	MCIERROR mciError;
	mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&mciopenparms);
	if (mciError)//mciError为真时，说明打开失败
	{
		wchar_t szErrorMsg[256];
		mciGetErrorString(mciError, szErrorMsg, 256);//获取错误信息
		AfxMessageBox(szErrorMsg);//弹出错误信息
		return;
	}
	m_DeviceID = mciopenparms.wDeviceID;//

	//播放
	OnBnClickedPlay();

	CDialogEx::OnDropFiles(hDropInfo);
}




void C音乐播放器Dlg::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	//获取滑动空间当前值
	m_nVolume = m_slider.GetPos();
	UpdateData(FALSE);
	
	MCI_DGV_SETAUDIO_PARMS mciSetvolume;
	mciSetvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetvolume.dwValue = m_nVolume;

	mciSendCommand(m_DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)&mciSetvolume);

	*pResult = 0;
}
