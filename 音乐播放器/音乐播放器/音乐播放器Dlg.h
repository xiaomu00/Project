
// 音乐播放器Dlg.h : 头文件
//

#pragma once
#include<mmsystem.h>//多媒体设备接口
#include<Digitalv.h>//处理音量
#include "afxcmn.h"
#pragma comment(lib,"Winmm.lib")//链接静态库文件


// C音乐播放器Dlg 对话框
class C音乐播放器Dlg : public CDialogEx
{
// 构造
public:
	C音乐播放器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	MCIDEVICEID m_DeviceID;//记录音乐

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	CSliderCtrl m_slider;
	int m_nVolume;
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
