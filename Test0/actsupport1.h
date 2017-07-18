#pragma once

// PLC�ؼ��ࣨMITSUBISHI ActSupport Control��

// ������������� Microsoft Visual C++ ������ IDispatch ��װ��

// ע��: ��Ҫ�޸Ĵ��ļ������ݡ����������
//  Microsoft Visual C++ �������ɣ������޸Ľ������ǡ�

/////////////////////////////////////////////////////////////////////////////
// CActsupport1 ��װ��

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

// ����
public:


// ����
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
