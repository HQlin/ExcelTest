//
// 软件主界面类

// Test0Dlg.h : 头文件
//

#pragma once
#include "Resource.h"
#include "BasicExcel.h"
#include "BtnST.h"
#include "PublicTool.h"
#include "actfx485bd1.h"
#include "actsupport1.h"
#include "afxwin.h"

using namespace YExcel;

// CTest0Dlg 对话框
class CTest0Dlg : public CDialogEx
{
// 构造
public:
	CTest0Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PLCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CActfx485bd1 m_actfx485bd;
	CActsupport1 m_actfxsupport;

	BasicExcel e;
	vector<const char*> m_plc;				//PLC位号   
	vector<const wchar_t*> m_plcCStr;		//PLC功能说明
	vector<int> m_plcType;					//PLC信号类型 0：高低电平，1：上升沿，-1：下降沿
	bool m_isLoadOk;						//加载是否完成

	/************************************************
	*   功能：加载plc位号
	*	参数：
		fileNameTrans：Excel文件路径

	*	返回值：是否加载成功
	* 	修改日期：2017年7月5日
	************************************************/
	bool LoadPlc(CString fileNameTrans);

	CButtonST* m_pBtns;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);


	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void TurnOff(CButtonST* btn);					//绿，表示1
	void TurnOn(CButtonST* btn);					//红，表示0
	void TurnNormal(CButtonST* btn);				//黄，正常
	
	virtual void OnCancel();
	void UpdatePlc(int i);
	short m_invalue;
	CButtonST m_pBtnUpdate;
	afx_msg void OnBnClickedButton1();
};

	
