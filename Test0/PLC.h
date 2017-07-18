//
//  PLCͨѶ������

#pragma once
#include "Test0Dlg.h"
#include "afxwin.h"

#ifndef ANIMAL_H_H
#define ANIMAL_H_H
class CPLC : public CDialogEx
{
// ����
	
public:
	CPLC (void);	// ��׼���캯��
	CPLC (CActsupport1 * actfxsupport, CActfx485bd1 * actfx485bd);
	~CPLC (void);

public:
	CRITICAL_SECTION   m_PlcReadWriteCriticalSection;
	CRITICAL_SECTION   m_PlcLinkingCriticalSection;
	CRITICAL_SECTION   m_PlcSingreadCriticalSection;
	/**��PC��PLC֮������,����ֵΪ��ʱ��ʾ�ɹ����������GetErrorMsg��ȡ������Ϣ*/
	long Open();
	/**�ر�PC��PLC֮�������,����ֵΪ��ʱ��ʾ�ɹ����������GetErrorMsg��ȡ������Ϣ*/
	long close(void);


	/**��ȡ�����ֵlErrorCode��Ӧ�Ĵ�����Ϣ*/
	void GetErrorMsg(long lErrorCode);

	/**��ʼ��ͨѶ����*/
	/**����PC��PLCͨѶ�Ĳ���(ͨѶ�˿ڡ�ͨѶ���ʵȵ�),���ú���Ҫ���´����ӣ����ò���Ч*/
	bool init(long ActPortNumber,		  //ͨѶ�˿ں�(COM��)
				  long ActSumCheck,		  //��У��
				  long ActDataBits,		  //����λ��
				  long ActParity,		  //��żУ��λ
				  long ActStopBit,		  //ֹͣλ
				  long ActBaudRate,       //���䲨����
				  long ActCpuType,        //PLC��CPU����
				  long ActTimeOut,		  //���ӳ�ʱʱ��
				  long ActUnitNumber,	  //վ���
				  long ActControl,		  //�ź��߿���
				  long ActCpuTimeOut);    //����ȴ�ʱ�� 

	/**����PC��PLCͨѶ�Ĳ���(ͨѶ�˿ڡ�ͨѶ���ʵȵ�),���ú���Ҫ���´����ӣ����ò���Ч*/
	bool SetLinkStatus(long ActPortNumber,        //ͨѶ�˿ں�(COM��)
		long ActSumCheck,		  //��У��
		long ActDataBits,		  //����λ��
		long ActParity,			  //��żУ��λ
		long ActStopBit,			  //ֹͣλ
		long ActBaudRate,          //���䲨����
		long ActCpuType,           //PLC��CPU����
		long ActTimeOut,			  //���ӳ�ʱʱ��
		long ActUnitNumber,		  //վ���
		long ActControl,			  //�ź��߿���
		long ActCpuTimeOut);        //����ȴ�ʱ��

	// ��ͨ��־���ж��Ƿ��Ѿ���PLC��ͨ��Ϊtrue����ͨ
	bool m_bLink;

	// ������ͨѶ�������ĸ�ϵͳ�ģ�����Ϊ��ҩ��ϵͳ������Сҩ��ϵͳ
	bool init();

	long ReadBatchData(const CString& szDevice, long lSize,short *lplData);   //������
	long ReadBatchData1(const CString& szDevice, long lSize,short *lplData);   //�����

	long WriteBatchData(const CString& szDevice, long lSize,short *lplData);  //����д
	long WriteBatchData1(const CString& szDevice, long lSize,short *lplData);  //���д

public:
	short Write(const CString& szDevice);//ָ��λ������1�����д
	short nWrite(const CString& szDevice);//ָ��λ������0�����д
	short Read(const CString& szDevice);//ָ��λ�����룬�����

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
	//�洢����ѧϰ�����ʵ������PLCͨѶ��ActiveX�ؼ�����
	CActsupport1 * m_actfxsupport;
	CActfx485bd1 * m_actfx485bd;
	
};

#endif