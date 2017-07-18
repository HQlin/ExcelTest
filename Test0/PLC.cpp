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

bool CPLC::SetLinkStatus(long ActPortNumber,        //ͨѶ�˿ں�(COM��)
						   long ActSumCheck,		  //��У��(0,1)
						   long ActDataBits,		  //����λ��(7,8)
						   long ActParity,			  //��żУ��λ(0-wu,1-ji,2-ou)
						   long ActStopBit,			  //ֹͣλ(0-1,2-2)
						   long ActBaudRate,          //���䲨����
						   long ActCpuType,           //PLC��CPU����
						   long ActTimeOut,			  //���ӳ�ʱʱ��
						   long ActUnitNumber,		  //վ���
						   long ActControl,			  //�ź��߿���(1,2,7,8)
						   long ActCpuTimeOut)        //����ȴ�ʱ��*10ms 
{
	//��Ҫ�ȹر�����,Ȼ�������ã���������ٴ�
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
	//�ж��Ƿ����е����ö��ɹ�
	return true;
}

bool CPLC::init(long ActPortNumber,     //ͨѶ�˿ں�(COM��)
				  long ActSumCheck,		  //��У��
				  long ActDataBits,		  //����λ��
				  long ActParity,		  //��żУ��λ
				  long ActStopBit,		  //ֹͣλ
				  long ActBaudRate,       //���䲨����
				  long ActCpuType,        //PLC��CPU����
				  long ActTimeOut,		  //���ӳ�ʱʱ��
				  long ActUnitNumber,	  //վ���
				  long ActControl,		  //�ź��߿���
				  long ActCpuTimeOut)     //����ȴ�ʱ�� 
{
	//����ͨ�Ų���
	if( CheckLinkingState() ){
		return true;
	}

	if(!SetLinkStatus(ActPortNumber,ActSumCheck,ActDataBits,ActParity,ActStopBit,ActBaudRate,ActCpuType,ActTimeOut,ActUnitNumber,ActControl,ActCpuTimeOut))
	{
		ResetLinkingState();
		return false;
	}
	//�ر�ͨѶ
	close();
	//��ͨ��
	long result=Open();
	if(0 == result)//���ӳɹ�
	{ 
		SetLinkingState();
	}
	else//����ʧ��
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
		MsgStr = L"����PLCʧ�ܣ�" + MsgStr;
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
			MsgStr = L"�Ͽ�PLCʧ�ܣ�" + MsgStr;
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
		ErrorMsg = L"OLE����" + ErrorMsg;
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
	ErrorMsg = L"PLCͨѶ����" + ErrorMsg;
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
		MsgStr = L"��PLCʧ�ܣ�" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRetΪ���ʾ�ɹ�
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
		MsgStr = L"��PLCʧ�ܣ�" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRetΪ���ʾ�ɹ�
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
		MsgStr = L"дPLCʧ�ܣ�" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRetΪ���ʾ�ɹ�
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
		MsgStr = L"дPLCʧ�ܣ�" + MsgStr;
		AfxMessageBox(MsgStr, MB_ICONINFORMATION);
		Exception->Delete();
	}
	return lRet;//lRetΪ���ʾ�ɹ�
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

bool CPLC::init() //����ȴ�ʱ��
{
	bool connect = init(m_ActPortNumber,     //ͨѶ�˿ں�(COM��)
				  0,		  //��У��
				  7,		  //����λ��
				  1,		  //��żУ��λ
				  0,		  //ֹͣλ
				  9600,       //���䲨����
				  517,        //PLC��CPU����
				  1000,		  //���ӳ�ʱʱ��
				  0,	  //վ���
				  8,		  //�ź��߿���
				  4);    //����ȴ�ʱ�� 


	return connect;  // ���ǽ��������õ��ؼ������򷵻� TRUE

}
