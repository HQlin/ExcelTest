#include "StdAfx.h"
#include "PublicTool.h"


CPublicTool::CPublicTool(void)
{
}


CPublicTool::~CPublicTool(void)
{
}

char* CPublicTool::MyW2A(const CString& str){
	int n = str.GetLength();
	int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL);
	char * strchar = new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, str, n+1, strchar, len+1, NULL, NULL);
	strchar[len] = '\0';
	return strchar;
}

CString CPublicTool::GetFilePath(CString name)
{
	WCHAR filepath[512];
	GetModuleFileName(NULL,filepath,512);
	CString fileroot(filepath);
	fileroot = fileroot.Left(fileroot.ReverseFind('\\')+1);
	fileroot += name;
	return fileroot;
}
