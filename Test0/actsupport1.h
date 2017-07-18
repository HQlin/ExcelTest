#pragma once

// PLC控件类（MITSUBISHI ActSupport Control）

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CActsupport1 包装类

class CActsupport1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CActsupport1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x5713F0A5, 0x6F4A, 0x11D5, { 0x93, 0x15, 0x0, 0x90, 0x99, 0x24, 0x4E, 0xFD } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:


// 操作
public:

// IActSupport3

// Functions
//

	long GetErrorMessage(long lErrorCode, BSTR * lpszErrorMessage)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lErrorCode, lpszErrorMessage);
		return result;
	}

// Properties
//



};
