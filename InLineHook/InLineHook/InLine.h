#pragma once
#include <windows.h>
#include <iostream>
using namespace std;
class InLine
{
public:
	InLine();
	~InLine();
	//参数为：hook的模块名称，hook的API函数地址，要替换的函数地址
	BOOL hook(LPSTR pszModuleName, LPSTR pszFunName, PROC pfnHookFunc);
	VOID Unhook();
	BOOL ReHook();
private:
	PROC m_pfnOrig;   //函数地址
	BYTE m_bOldBytes[5];   //函数入口代码
	BYTE m_bNewBytes[5];   //InLine代码
};

