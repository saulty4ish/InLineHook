#pragma once
#include <windows.h>
#include <iostream>
using namespace std;
class InLine
{
public:
	InLine();
	~InLine();
	//����Ϊ��hook��ģ�����ƣ�hook��API������ַ��Ҫ�滻�ĺ�����ַ
	BOOL hook(LPSTR pszModuleName, LPSTR pszFunName, PROC pfnHookFunc);
	VOID Unhook();
	BOOL ReHook();
private:
	PROC m_pfnOrig;   //������ַ
	BYTE m_bOldBytes[5];   //������ڴ���
	BYTE m_bNewBytes[5];   //InLine����
};

