#pragma once

// PLC控件类（MITSUBISHI ActFX485BD Control）

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CActfx485bd1 包装类

class CActfx485bd1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CActfx485bd1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x39B2DB55, 0x51B4, 0x4366, { 0xB6, 0x47, 0x85, 0x29, 0x84, 0xD0, 0x6, 0x15 } };
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

// IActFX485BD3

// Functions
//

	long Open()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Close()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long ReadDeviceBlock(LPCTSTR szDevice, long lSize, long * lplData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lSize, lplData);
		return result;
	}
	long WriteDeviceBlock(LPCTSTR szDevice, long lSize, long * lplData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lSize, lplData);
		return result;
	}
	long ReadDeviceRandom(LPCTSTR szDeviceList, long lSize, long * lplData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDeviceList, lSize, lplData);
		return result;
	}
	long WriteDeviceRandom(LPCTSTR szDeviceList, long lSize, long * lplData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDeviceList, lSize, lplData);
		return result;
	}
	long GetClockData(short * lpsYear, short * lpsMonth, short * lpsDay, short * lpsDayOfWeek, short * lpsHour, short * lpsMinute, short * lpsSecond)
	{
		long result;
		static BYTE parms[] = VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lpsYear, lpsMonth, lpsDay, lpsDayOfWeek, lpsHour, lpsMinute, lpsSecond);
		return result;
	}
	long SetClockData(short sYear, short sMonth, short sDay, short sDayOfWeek, short sHour, short sMinute, short sSecond)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sYear, sMonth, sDay, sDayOfWeek, sHour, sMinute, sSecond);
		return result;
	}
	long SetDevice(LPCTSTR szDevice, long lData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lData);
		return result;
	}
	long SetCpuStatus(long lOperation)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lOperation);
		return result;
	}
	long GetCpuType(BSTR * szCpuName, long * lplCpuCode)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_PI4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szCpuName, lplCpuCode);
		return result;
	}
	long get_ActCpuTimeOut()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActCpuTimeOut(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActUnitNumber()
	{
		long result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActUnitNumber(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActCpuType()
	{
		long result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActCpuType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActPortNumber()
	{
		long result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActPortNumber(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActBaudRate()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActBaudRate(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActDataBits()
	{
		long result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActDataBits(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActParity()
	{
		long result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActParity(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActStopBits()
	{
		long result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActStopBits(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActControl()
	{
		long result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActControl(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActTimeOut()
	{
		long result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActTimeOut(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ActSumCheck()
	{
		long result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ActSumCheck(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long GetDevice(LPCTSTR szDevice, long * lplData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PI4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lplData);
		return result;
	}
	long CheckDeviceString(LPCTSTR szDevice, long lCheckType, long lSize, long * lplDeviceType, BSTR * lpszDeviceName, long * lplDeviceNumber, long * lplDeviceRadix)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lCheckType, lSize, lplDeviceType, lpszDeviceName, lplDeviceNumber, lplDeviceRadix);
		return result;
	}
	long EntryDeviceStatus(LPCTSTR szDeviceList, long lSize, long lMonitorCycle, long * lplData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDeviceList, lSize, lMonitorCycle, lplData);
		return result;
	}
	long FreeDeviceStatus()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long ReadDeviceBlock2(LPCTSTR szDevice, long lSize, short * lpsData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI2 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lSize, lpsData);
		return result;
	}
	long WriteDeviceBlock2(LPCTSTR szDevice, long lSize, short * lpsData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI2 ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lSize, lpsData);
		return result;
	}
	long ReadDeviceRandom2(LPCTSTR szDeviceList, long lSize, short * lpsData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI2 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDeviceList, lSize, lpsData);
		return result;
	}
	long WriteDeviceRandom2(LPCTSTR szDeviceList, long lSize, short * lpsData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI2 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDeviceList, lSize, lpsData);
		return result;
	}
	long GetDevice2(LPCTSTR szDevice, short * lpsData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PI2 ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, lpsData);
		return result;
	}
	long SetDevice2(LPCTSTR szDevice, short sData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, parms, szDevice, sData);
		return result;
	}

// Properties
//



};
