#pragma once
/************************************************ 
*   版权：
* 	许可证：

* 	文件名称：PublicTool.h  
* 	作 者：lin（邮箱：283836490@QQ.com）  
* 	修改日期：2017年04月05日   
* 	功能：这是个全局方法及全局（常量）变量管理类
************************************************/

class CPublicTool
{
public:
	CPublicTool(void);
	~CPublicTool(void);

	//转换宽字节CString类型为char类型，解决W2A()在try语句段中无法使用的问题
	//注意使用完char*需要释放内存
	static char* MyW2A(const CString& str);

	//获取工程文件的绝对路径
	static CString GetFilePath(CString name);	
};

