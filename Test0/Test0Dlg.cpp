
// Test0Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test0.h"
#include "Test0Dlg.h"
#include "afxdialogex.h"
#include "PLC.h"

extern CPLC g_plc(NULL,NULL);
DWORD WINAPI ThrdLoad(LPVOID pthread);
struct ThrdData
{
	CTest0Dlg* dlg;
	int i;
};

// CTest0Dlg 对话框

CTest0Dlg::CTest0Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTest0Dlg::IDD, pParent)
	, m_invalue(0)
	, m_pBtns(NULL)
	, m_isLoadOk(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetPriorityClass(GetCurrentProcess(),ABOVE_NORMAL_PRIORITY_CLASS);  //设置进程优先级
}

void CTest0Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACTFX485BD1, m_actfx485bd);
	DDX_Control(pDX, IDC_ACTSUPPORT1, m_actfxsupport);
	DDX_Text(pDX, IDC_EDIT1, m_invalue);
	DDX_Control(pDX, IDC_BUTTON1, m_pBtnUpdate);
}

BEGIN_MESSAGE_MAP(CTest0Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTest0Dlg::OnBnClickedButton1)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CTest0Dlg 消息处理程序

BOOL CTest0Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//屏蔽默认菜单栏
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	LoadPlc(CPublicTool::GetFilePath(L"PLC位号模板.xls"));
	TurnNormal(&m_pBtnUpdate);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CTest0Dlg::OnBnClickedButton1()
{
	LoadPlc(CPublicTool::GetFilePath(L"PLC位号模板.xls"));
}

bool CTest0Dlg::LoadPlc(CString fileNameTrans)
{
	SetWindowText(L"PLC通信测试软件");
	m_plc.clear();
	m_plcCStr.clear();

	// Load a workbook with one sheet, display its contents and
	// save into another file.	
	char* path = CPublicTool::MyW2A(fileNameTrans);
	bool b = e.Load(path);
	BasicExcelWorksheet* sheet1 = e.GetWorksheet("Sheet1");
	if (sheet1)
	{
		//PLC com
		BasicExcelCell* cell = sheet1->Cell(1,0);
		g_plc.m_ActPortNumber = cell->GetInteger();

		//行数
		size_t maxRows = sheet1->GetTotalRows();
		//列数
		size_t maxCols = sheet1->GetTotalCols();

		for (size_t c=1; c<maxCols; ++c)
		{
			for (size_t r=0; r<maxRows; ++r)
			{
				BasicExcelCell* cell = sheet1->Cell(r,c);
				switch (cell->Type())
				{
				case BasicExcelCell::UNDEFINED:
					printf(" ");
					break;
				case BasicExcelCell::INT:
					printf("%10d", cell->GetInteger());
					break;
				case BasicExcelCell::DOUBLE:
					printf("%10.6lf", cell->GetDouble());
					break;
				case BasicExcelCell::STRING:
					//PLC位号
					m_plc.push_back(cell->GetString());
					break;
				case BasicExcelCell::WSTRING:
					//PLC位号功能
					m_plcCStr.push_back(cell->GetWString());
					break;
				}
			}
		}
	}
	//path = CPublicTool::MyW2A(CPublicTool::GetFilePath(L"上次PLC位号.xls"));
	//e.SaveAs(path);
	delete path;

	//加载按钮
	if(NULL != m_pBtns)
	{
		delete[] m_pBtns;		
		m_pBtns = NULL;
	}

	if(NULL == m_pBtns)
	{
		int iBtnNum = m_plc.size(), iMax = 0;
		m_pBtns = new CButtonST[iBtnNum];
		CString strBtnText = _T("");
		for (int i = 0 ; i < iBtnNum ; i = i + 3)
		{
			CString s0(m_plc[i]);
			strBtnText.Format(L"(%s)%s", s0, m_plcCStr[i]);
			m_pBtns[i].Create(strBtnText, WS_VISIBLE|WS_CHILD, CRect(25, 50 + 30*i, 225, 130 + 30*i), this, 3000 + i);
			m_pBtns[i].ShowWindow(SW_SHOW);

			if(i+1 < iBtnNum)
			{
				CString s1(m_plc[i+1]);
				strBtnText.Format(L"(%s)%s", s1, m_plcCStr[i+1]);
				m_pBtns[i+1].Create(strBtnText, WS_VISIBLE|WS_CHILD, CRect(250, 50 + 30*i, 475, 130 + 30*i), this, 3000 + i+1);
				m_pBtns[i+1].ShowWindow(SW_SHOW);
			}

			if(i+2 < iBtnNum)
			{
				CString s2(m_plc[i+2]);
				strBtnText.Format(L"(%s)%s", s2, m_plcCStr[i+2]);
				m_pBtns[i+2].Create(strBtnText, WS_VISIBLE|WS_CHILD, CRect(500, 50 + 30*i, 725, 130 + 30*i), this, 3000 + i+2);
				m_pBtns[i+2].ShowWindow(SW_SHOW);
			}
			//滑动窗口高度
			iMax = 230 + 30*i;
		}

		SCROLLINFO info;
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_ALL;
		info.nMin = 0;
		info.nMax = iMax;
		info.nPage = 500;//每页的高度也就是窗口高度，滚动条的长度=nPage/nMax
		info.nPos = 0;
		SetScrollInfo(SB_VERT, &info, TRUE);
	}
	//PLC控制部分
	g_plc.ActiveXinit(&m_actfxsupport, &m_actfx485bd);
	if(!g_plc.init())
	{	   
		AfxMessageBox(L"PLC初始化错误", MB_ICONINFORMATION);
	}
	else
	{
		//for (int i = 0 ; i < m_plc.size() ; i ++)
		//{
		//	ThrdData* _ThrdData = new ThrdData();
		//	_ThrdData->dlg = this;
		//	_ThrdData->i = i;
		//	CreateThread(NULL, 0, ThrdLoad, _ThrdData, 0, NULL);
		//}
		ThrdData* _ThrdData = new ThrdData();
		_ThrdData->dlg = this;
		_ThrdData->i = 0;
		CreateThread(NULL, 0, ThrdLoad, _ThrdData, 0, NULL);
	}
	return true;
}

void CTest0Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	switch(nSBCode) {
	case SB_BOTTOM:
		{
			ScrollWindow(0, scrollinfo.nPos - scrollinfo.nMax + scrollinfo.nPage);
			scrollinfo.nPos = scrollinfo.nMax - scrollinfo.nPage;
			SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
		}
		break;
	case SB_TOP:
		{
			ScrollWindow(0, scrollinfo.nPos);
			scrollinfo.nPos = 0;
			SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
		}
		break;
	case SB_LINEUP://上箭头
		{
			int iLeft = scrollinfo.nPos, iJump = (iLeft > m_plc.size())?m_plc.size():iLeft;
			scrollinfo.nPos -= iJump;
			SetScrollInfo(SB_VERT, &scrollinfo, TRUE);
			ScrollWindow(0, iJump);
		}
		break;
	case SB_LINEDOWN://下箭头
		{
			int iLeft = scrollinfo.nMax - scrollinfo.nPage - scrollinfo.nPos, iJump = (iLeft > m_plc.size())?m_plc.size():iLeft;
			scrollinfo.nPos += iJump;
			SetScrollInfo(SB_VERT, &scrollinfo, TRUE);
			ScrollWindow(0, 0 - iJump);
		}
		break;
	case SB_PAGEUP://上空白
		{
			int iLeft = scrollinfo.nPos, iJump = (iLeft > m_plc.size()*m_plc.size())?(m_plc.size()*m_plc.size()):iLeft;
			scrollinfo.nPos -= iJump;
			SetScrollInfo(SB_VERT, &scrollinfo, TRUE);
			ScrollWindow(0, iJump);
		}
		break;
	case SB_PAGEDOWN://下空白
		{
			int iLeft = scrollinfo.nMax - scrollinfo.nPage - scrollinfo.nPos, iJump = (iLeft > m_plc.size()*m_plc.size())?(m_plc.size()*m_plc.size()):iLeft;
			scrollinfo.nPos += iJump;
			SetScrollInfo(SB_VERT, &scrollinfo, TRUE);
			ScrollWindow(0, 0 - iJump);
		}
		break;
	case SB_ENDSCROLL://结束
		// MessageBox("SB_ENDSCROLL");
		break;
	case SB_THUMBPOSITION://拖拽的最终位置
		// ScrollWindow(0,(scrollinfo.nPos-nPos)*SCROLLBAR_STEP);
		// scrollinfo.nPos = nPos;
		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		break;
	case SB_THUMBTRACK://拖拽过程中的位置
		{
			ScrollWindow(0, scrollinfo.nPos - nPos);
			scrollinfo.nPos = nPos;
			SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
		}
		break;
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CTest0Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	if(zDelta > 0) { // 向上滚
		int iMulti = zDelta/WHEEL_DELTA;//倍数
		int iLeft = scrollinfo.nPos, iJump = (iLeft > m_plc.size()*m_plc.size()*iMulti)?(m_plc.size()*m_plc.size()*iMulti):iLeft;
		scrollinfo.nPos -= iJump;
		SetScrollInfo(SB_VERT, &scrollinfo, TRUE);
		ScrollWindow(0, iJump);
	}
	else { // 向下滚
		int iMulti = zDelta/(0 - WHEEL_DELTA);//倍数
		int iLeft = scrollinfo.nMax - scrollinfo.nPage - scrollinfo.nPos, iJump = (iLeft > m_plc.size()*m_plc.size()*iMulti)?(m_plc.size()*m_plc.size()*iMulti):iLeft;
		scrollinfo.nPos += iJump;
		SetScrollInfo(SB_VERT, &scrollinfo, TRUE);
		ScrollWindow(0, 0 - iJump);
	}
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CTest0Dlg::PreTranslateMessage(MSG* pMsg)
{
	// 按钮按下
	//if(pMsg->message == WM_LBUTTONDOWN)
	//{
	//	for (int i = 0 ; i < m_plc.size() ; i ++)
	//	{
	//		if(pMsg->hwnd == GetDlgItem(3000 + i)->m_hWnd)
	//		{				
	//			CString s(m_plc[i]);				
	//			if (0 <= s.Find(L"D"))
	//			{

	//			}
	//			else
	//			{
	//						
	//			}
	//		}
	//	}
	//}
	//else 
	// 按钮抬起
	if(pMsg->message == WM_LBUTTONUP)
	{
		if(pMsg->hwnd == GetDlgItem(IDC_BUTTON1)->m_hWnd)
			return CDialogEx::PreTranslateMessage(pMsg);
		for (int i = 0 ; i < m_plc.size() ; i ++)
		{
			if(pMsg->hwnd == GetDlgItem(3000 + i)->m_hWnd)
			{			
				short value;
				CString s(m_plc[i]);
				if (0 <= s.Find(L"D"))
				{
					UpdateData();
					g_plc.WriteBatchData(s,1,&m_invalue);
				}
				else
				{
					g_plc.ReadBatchData1(s,1,&value);
					if(value)
						g_plc.nWrite(s);
					else
						g_plc.Write(s);		
				}
				UpdatePlc(i);
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTest0Dlg::TurnOn(CButtonST* btn)
{
	btn->SetColor( CButtonST::BTNST_COLOR_FG_OUT, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_FG_FOCUS, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_FG_IN, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_OUT, RGB(181,230,29));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_FOCUS, RGB(181,230,29));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_IN, RGB(181,230,29));
}


void CTest0Dlg::TurnOff(CButtonST* btn)
{
	btn->SetColor( CButtonST::BTNST_COLOR_FG_OUT, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_FG_FOCUS, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_FG_IN, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_OUT, RGB(240,66,74));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_FOCUS, RGB(240,66,74));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_IN, RGB(240,66,74));
}

void CTest0Dlg::TurnNormal(CButtonST* btn)
{
	btn->SetColor( CButtonST::BTNST_COLOR_FG_OUT, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_FG_FOCUS, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_FG_IN, RGB(89,89,89));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_OUT, RGB(200,200,0));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_FOCUS, RGB(200,200,0));
	btn->SetColor( CButtonST::BTNST_COLOR_BK_IN, RGB(200,200,0));
}


void CTest0Dlg::OnCancel()
{
	if(m_isLoadOk || !g_plc.CheckLinkingState())
	{
		g_plc.close();
		CDialogEx::OnCancel();
	}
	else
	{
		AfxMessageBox(L"PCL正在加载中", MB_ICONINFORMATION);
	}
}

void CTest0Dlg::UpdatePlc(int i)
{
	short value;
	CString s(m_plc[i]);
	if (0 <= s.Find(L"D"))
	{
		g_plc.ReadBatchData(s,1,&value);
		TurnNormal(&m_pBtns[i]);
		CString temp;
		temp.Format(L"%d(%s)%s", value, s, m_plcCStr[i]);
		SetDlgItemTextW(3000+i, temp);
	}
	else
	{
		g_plc.ReadBatchData1(s,1,&value);
		if(value)
			TurnOn(&m_pBtns[i]);
		else
			TurnOff(&m_pBtns[i]);		
	}
}

DWORD WINAPI ThrdLoad(LPVOID pthread)
{
	ThrdData * data = (ThrdData*)pthread;
	//while(1)
	//{
	//	data->dlg->UpdatePlc(data->i);
	//}
	for (int i = 0 ; i < data->dlg->m_plc.size() ; i ++)
	{
		data->dlg->UpdatePlc(i);
	}
	data->dlg->m_isLoadOk = true;
	delete data;
	return 0;
}
