#include "stdafx.h"

namespace myComAccess
{
	class ComAccess
	{
		private:

			HANDLE      m_hCom; // Device handle 

			OVERLAPPED  m_ov;   // A structure that contains informations which are
								// used for asynchronous input and output operations

			wchar_t     m_lpszErrorMessage[256];

		public:

			ComAccess(VOID);
			ComAccess(CString lpszPortNum);

			~ComAccess() { Close(); }
											

			BOOL	Open(CString lpszPortNum	= _T("com1"),			//Ĭ�ϴ�COM1
						 DWORD  dwBaudRate  = CBR_9600,					//������9600
						 BYTE   byParity    = NOPARITY,					//û����ż����
						 BYTE   byStopBits  = ONESTOPBIT,				//һλֹͣλ
						 BYTE   byByteSize  = 8);						//8λ���ݳ���

			VOID	Close(VOID);
	
			DWORD	WriteData(LPCVOID pdata, DWORD len);							//�򴮿�д����
			DWORD	ReadData(LPVOID  pdest, DWORD len, DWORD dwMaxWait = 500);		//�Ӵ��ڶ�����

			wchar_t *GetErrorMessage(VOID) { return m_lpszErrorMessage; }

		private:

			VOID	ErrorToString(const char *lpszMessage);

			BOOL	IsNT(VOID);
	};
}