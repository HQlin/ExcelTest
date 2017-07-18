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
											

			BOOL	Open(CString lpszPortNum	= _T("com1"),			//默认打开COM1
						 DWORD  dwBaudRate  = CBR_9600,					//波特率9600
						 BYTE   byParity    = NOPARITY,					//没有奇偶检验
						 BYTE   byStopBits  = ONESTOPBIT,				//一位停止位
						 BYTE   byByteSize  = 8);						//8位数据长度

			VOID	Close(VOID);
	
			DWORD	WriteData(LPCVOID pdata, DWORD len);							//向串口写数据
			DWORD	ReadData(LPVOID  pdest, DWORD len, DWORD dwMaxWait = 500);		//从串口读数据

			wchar_t *GetErrorMessage(VOID) { return m_lpszErrorMessage; }

		private:

			VOID	ErrorToString(const char *lpszMessage);

			BOOL	IsNT(VOID);
	};
}