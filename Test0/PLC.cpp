#include "stdafx.h"
#include "PLC.h"
#include "afxdialogex.h"
#include "actfx485bd1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPLC::CPLC(void)
{
	InitializeCriticalSection(&m_PlcReadWriteCriticalSection);
	InitializeCriticalSection(&m_PlcLinkingCriticalSection);
	InitializeCriticalSection(&m_PlcSingreadCriticalSection);
}

CPLC::CPLC(CActsupport1 *actfxsupport, CActfx485bd1 *actfx485bd)
	:m_actfxsupport(actfxsupport)
	,m_actfx485bd(actfx485bd)
{
	InitializeCriticalSection(&m_PlcReadWriteCriticalSection);
	InitializeCriticalSection(&m_PlcLinkingCriticalSection);
	InitializeCriticalSection(&m_PlcSingreadCriticalSection);
}

CPLC::~CPLC(void)
{
	DeleteCriticalSection(&m_PlcReadWriteCriticalSection);
	DeleteCriticalSection(&m_PlcLinkingCriticalSection);
	DeleteCriticalSection(&m_PlcSingreadCriticalSection);
}

bool CPLC::SetLinkStatus(long ActPortNumber,        //通讯端口号(COM号)
						   long ActSumCheck,		  //和校验(0,1)
						   long ActDataBits,		  //传输位数(7,8)
						   long ActParity,			  //奇偶校验位(0-wu,1-ji,2-ou)
						   long ActStopBit,			  //停止位(0-1,2-2)
						   long ActBaudRate,          //传输波特率
						   long ActCpuType,           //PLC的CPU类型
						   long ActTimeOut,			  //连接超时时间
						   long ActUnitNumber,		  //站点号
						   long ActControl,			  //信号线控制(1,2,7,8)
						   long ActCpuTimeOut)        //传输等待时间*10ms 
{
	//需要先关闭连接,然后再设置，设置完后再打开
	m_actfx485bd->put_ActPortNumber(ActPortNumber);
	m_actfx485bd->put_ActSumCheck(ActSumCheck);
	m_actfx485bd->put_ActDataBits(ActDataBits);
	m_actfx485bd->put_ActParity(ActParity);
	m_actfx485bd->put_ActStopBits(ActStopBit);
	m_actfx485bd->put_ActBaudRate(ActBaudRate);
	m_actfx485bd->put_ActCpuType(ActCpuType);
	m_actfx485bd->put_ActTimeOut(ActTimeOut);
	m_actfx485bd->put_ActUnitNumber(ActUnitNumber);
	m_actfx485bd->put_ActControl(ActControl);
	m_actfx485bd->put_ActCpuTimeOut(ActCpuTimeOut);
	//判断是否所有的设置都成功
	return true;
}

bool CPLC::init(long ActPortNumber,     //通讯端口号(COM号)
				  long ActSumCheck,		  //和校验
				  long ActDataBits,		  //传输位数
				  long ActParity,		  //奇偶校验位
				  long ActStopBit,		  //停止位
				  long ActBaudRate,       //传输波特率
				  long ActCpuType,        //PLC的CPU类型
				  long ActTimeOut,		  //连接超时时间
				  long ActUnitNumber,	  //站点号
				  long ActControl,		  //信号线控制
				  long ActCpuTimeOut)     //传输等待时间 
{
	//设置通信参数
	if( CheckLinkingState() ){
		return true;
	}

	if(!SetLinkStatus(ActPortNumber,ActSumCheck,ActDataBits,ActParity,ActStopBit,ActBaudRate,ActCpuType,ActTimeOut,ActUnitNumber,ActControl,ActCpuTimeOut))
	{
		ResetLinkingState();
		return false;
	}
	//关闭通讯
	close();
	//打开通信
	long result=Open();
	if(0 == result)//连接成功
	{ 
		SetLinkingState();
	}
	else//连接失败
	{
		GetErrorMsg(result);
		ResetLinkingState();
		return false;
	}
	return true;
}

long CPLC::Open()
{
	long lRet=-1;
	CString	MsgStr;
	EnterCriticalSection(&m_PlcReadWriteCriticalSection);
	try
	{
		lRet=m_actfx485bd->Open();
	}
	catch(COleDispatchException *Exception){
		// OLE IDispatch Interface Error
		MsgStr = L"连接PLC失败：" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	LeaveCriticalSection(&m_PlcReadWriteCriticalSection);
	return lRet;
}

long CPLC::close(void)
{
	if( !CheckLinkingState() ){
		return true;
	}
	else{
		long lRet=-1;
		CString	MsgStr;
		EnterCriticalSection(&m_PlcReadWriteCriticalSection);
		try
		{
			lRet=m_actfx485bd->Close();
			ResetLinkingState();//m_bLink = false;
		}
		catch(COleDispatchException *Exception){
			// OLE IDispatch Interface Error
			MsgStr = L"断开PLC失败：" + MsgStr;
			AfxMessageBox(MsgStr, MB_ICONINFORMATION);
			Exception->Delete();
		}
		LeaveCriticalSection(&m_PlcReadWriteCriticalSection);
		return lRet;
	}
}

void CPLC::GetErrorMsg(long lErrorCode)
{
	CString ErrorMsg;
	long lRet;
	BSTR bstrErrorMessage=0;	//Error message
	if(-1==lErrorCode)
	{
		ErrorMsg.Format(L"COleDispatchException! \r\n<ErrorCode:0xFFFFFFFF[Hex]>");
		ErrorMsg = L"OLE错误：" + ErrorMsg;
		AfxMessageBox(ErrorMsg);
		return;
	}
	//[The GetErrorMessage method is executed. ]
	lRet = m_actfxsupport->GetErrorMessage(lErrorCode,&bstrErrorMessage);
	//[Whether GetErrorMessage succeeded is checked. ]
	if (lRet == 0){
		//[When GetErrorMessage succeeds]
		//[The acquired message is displayed in the editing box. ]
		ErrorMsg = bstrErrorMessage;
	}else{
		//[When GetErrorMessage fails ]
		//[The message in which GetErrorMesssage fails is displayed. ]
		ErrorMsg.Format(L"The GetErrorMessage method failed and the message was not able to be acquired. \r\n<ErrorCode:%08x[Hex]>",lRet);
	}
	//[If the Method has Output value of BSTR type, you have to free the allocated BSTR area.]
	::SysFreeString(bstrErrorMessage);
	ErrorMsg = L"PLC通讯错误：" + ErrorMsg;
	AfxMessageBox(ErrorMsg);;
}

long CPLC::ReadBatchData(const CString& szDevice, long lSize,short *lplData)
{
	long lRet=-1;
	CString	MsgStr;
	try{
		lRet = m_actfx485bd->ReadDeviceBlock2(szDevice,lSize,lplData);
	}
	catch(COleDispatchException *Exception){
		// OLE IDispatch Interface Error
		MsgStr = L"读PLC失败：" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRet为零表示成功
}

long CPLC::ReadBatchData1(const CString& szDevice, long lSize,short *lplData)
{
	long lRet=-1;
	CString	MsgStr;
	try{
		lRet = m_actfx485bd->ReadDeviceRandom2(szDevice,lSize,lplData);
	}
	catch(COleDispatchException *Exception){
		// OLE IDispatch Interface Error
		MsgStr = L"读PLC失败：" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRet为零表示成功
}

long CPLC::WriteBatchData(const CString& szDevice, long lSize,short *lpsData)
{
	long lRet=-1;
	CString	MsgStr;
	try{
		lRet = m_actfx485bd->WriteDeviceBlock2(szDevice,lSize,lpsData);
	}
	catch(COleDispatchException *Exception){
		// OLE IDispatch Interface Error
		MsgStr = L"写PLC失败：" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRet为零表示成功
}


long CPLC::WriteBatchData1(const CString& szDevice, long lSize,short *lpsData)
{
	long lRet=-1;
	CString	MsgStr;
	try{
		lRet = m_actfx485bd->WriteDeviceRandom2(szDevice,lSize,lpsData);
	}
	catch(COleDispatchException *Exception){
		// OLE IDispatch Interface Error
		MsgStr = L"写PLC失败：" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRet为零表示成功
}

short CPLC::Write( const CString& szDevice)
{   
	long result = -1;
	long lSize=1;
	short lpsData = 1;
	if( CheckLinkingState() ){
		EnterCriticalSection(&m_PlcSingreadCriticalSection);
		if( !CheckLinkingState() ){
			LeaveCriticalSection(&m_PlcSingreadCriticalSection);
			return 0;
		}
		{
			result = WriteBatchData1(szDevice,lSize,&lpsData);
		}
		if(result!=0)
		{
			GetErrorMsg(result);
		}
		LeaveCriticalSection(&m_PlcSingreadCriticalSection);
	}
	return lpsData;
}
short CPLC::nWrite( const CString& szDevice)
{   
	long result = -1;
	long lSize=1;
	short lpsData = 0;
	if( CheckLinkingState() ){
		EnterCriticalSection(&m_PlcSingreadCriticalSection);
		if( !CheckLinkingState() ){
			LeaveCriticalSection(&m_PlcSingreadCriticalSection);
			return 0;
		}
		{
			result = WriteBatchData1(szDevice,lSize,&lpsData);
		}
		if(result!=0)
		{
			GetErrorMsg(result);
		}
		LeaveCriticalSection(&m_PlcSingreadCriticalSection);
	}
	return lpsData;
}

short CPLC::Read( const CString& szDevice)
{   
	long result = -1;
	long lSize=1;
	short lpsData = 0;
	if( CheckLinkingState() ){
		EnterCriticalSection(&m_PlcSingreadCriticalSection);
		if( !CheckLinkingState() ){
			LeaveCriticalSection(&m_PlcSingreadCriticalSection);
			return 0;
		}
		{
			result = ReadBatchData1(szDevice,lSize,&lpsData);
		}
		if(result!=0)
		{
			GetErrorMsg(result);
		}
		LeaveCriticalSection(&m_PlcSingreadCriticalSection);
	}
	return lpsData;
}

void CPLC::ActiveXinit(CActsupport1 * actfxsupport, CActfx485bd1 * actfx485bd){
	m_actfxsupport = actfxsupport;
	m_actfx485bd = actfx485bd;
}

bool CPLC::init() //传输等待时间
{
	bool connect = init(m_ActPortNumber,     //通讯端口号(COM号)
				  0,		  //和校验
				  7,		  //传输位数
				  1,		  //奇偶校验位
				  0,		  //停止位
				  9600,       //传输波特率
				  517,        //PLC的CPU类型
				  1000,		  //连接超时时间
				  0,	  //站点号
				  8,		  //信号线控制
				  4);    //传输等待时间 


	return connect;  // 除非将焦点设置到控件，否则返回 TRUE

}
