//
//  PLC通讯控制类

#pragma once
#include "Test0Dlg.h"
#include "afxwin.h"

#ifndef ANIMAL_H_H
#define ANIMAL_H_H
class CPLC : public CDialogEx
{
// 构造
	
public:
	CPLC (void);	// 标准构造函数
	CPLC (CActsupport1 * actfxsupport, CActfx485bd1 * actfx485bd);
	~CPLC (void);

public:
	CRITICAL_SECTION   m_PlcReadWriteCriticalSection;
	CRITICAL_SECTION   m_PlcLinkingCriticalSection;
	CRITICAL_SECTION   m_PlcSingreadCriticalSection;
	/**打开PC与PLC之间连接,返回值为零时表示成功，否则调用GetErrorMsg获取错误信息*/
	long Open();
	/**关闭PC与PLC之间的连接,返回值为零时表示成功，否则调用GetErrorMsg获取错误信息*/
	long close(void);


	/**获取与错误值lErrorCode对应的错误信息*/
	void GetErrorMsg(long lErrorCode);

	/**初始化通讯参数*/
	/**设置PC与PLC通讯的参数(通讯端口、通讯速率等等),设置后需要重新打开连接，设置才生效*/
	bool init(long ActPortNumber,		  //通讯端口号(COM号)
				  long ActSumCheck,		  //和校验
				  long ActDataBits,		  //传输位数
				  long ActParity,		  //奇偶校验位
				  long ActStopBit,		  //停止位
				  long ActBaudRate,       //传输波特率
				  long ActCpuType,        //PLC的CPU类型
				  long ActTimeOut,		  //连接超时时间
				  long ActUnitNumber,	  //站点号
				  long ActControl,		  //信号线控制
				  long ActCpuTimeOut);    //传输等待时间 

	/**设置PC与PLC通讯的参数(通讯端口、通讯速率等等),设置后需要重新打开连接，设置才生效*/
	bool SetLinkStatus(long ActPortNumber,        //通讯端口号(COM号)
		long ActSumCheck,		  //和校验
		long ActDataBits,		  //传输位数
		long ActParity,			  //奇偶校验位
		long ActStopBit,			  //停止位
		long ActBaudRate,          //传输波特率
		long ActCpuType,           //PLC的CPU类型
		long ActTimeOut,			  //连接超时时间
		long ActUnitNumber,		  //站点号
		long ActControl,			  //信号线控制
		long ActCpuTimeOut);        //传输等待时间

	// 连通标志，判断是否已经与PLC连通，为true则连通
	bool m_bLink;

	// 表明该通讯是属于哪个系统的，或者为大药卷系统，或者小药卷系统
	bool init();

	long ReadBatchData(const CString& szDevice, long lSize,short *lplData);   //批量读
	long ReadBatchData1(const CString& szDevice, long lSize,short *lplData);   //随机读

	long WriteBatchData(const CString& szDevice, long lSize,short *lplData);  //批量写
	long WriteBatchData1(const CString& szDevice, long lSize,short *lplData);  //随机写

public:
	short Write(const CString& szDevice);//指定位号输入1，随机写
	short nWrite(const CString& szDevice);//指定位号输入0，随机写
	short Read(const CString& szDevice);//指定位号输入，随机读

	void ActiveXinit(CActsupport1 * actfxsupport, CActfx485bd1 * actfx485bd);
	
	bool CheckLinkingState(){
		bool result = false;
		EnterCriticalSection(&m_PlcLinkingCriticalSection);
		result = ( true == m_bLink );
		LeaveCriticalSection(&m_PlcLinkingCriticalSection);
		return result;
	}
	void SetLinkingState(){
		EnterCriticalSection(&m_PlcLinkingCriticalSection);
		m_bLink = true;
		LeaveCriticalSection(&m_PlcLinkingCriticalSection);
	}
	void ResetLinkingState(){
		EnterCriticalSection(&m_PlcLinkingCriticalSection);
		m_bLink = false;
		LeaveCriticalSection(&m_PlcLinkingCriticalSection);
	}
	
	long m_ActPortNumber;
private:
	//存储检测或学习界面的实际用于PLC通讯的ActiveX控件变量
	CActsupport1 * m_actfxsupport;
	CActfx485bd1 * m_actfx485bd;
	
};

#endif