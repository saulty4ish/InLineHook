#include "stdafx.h"
#include "InLine.h"


InLine::InLine()
{
	Unhook();
	m_pfnOrig = NULL;
	ZeroMemory(m_bOldBytes, 5);
	ZeroMemory(m_bNewBytes, 5);
}


InLine::~InLine()
{
	m_pfnOrig = NULL;
	ZeroMemory(m_bOldBytes, 5);
	ZeroMemory(m_bNewBytes, 5);
}

BOOL InLine::hook(LPSTR pszModuleName, LPSTR pszFunName, PROC pfnHookFunc)
{
	BOOL bRet = FALSE;
	//获取调用的dll中函数在内存中的地址
	m_pfnOrig = (PROC)GetProcAddress(GetModuleHandleA(pszModuleName), pszFunName);
	if (m_pfnOrig != 0)
	{
		DWORD n = 0;
		//读取内存中地址的前五个字节，储存在oldbyte中，方便停止调用
		ReadProcessMemory(GetCurrentProcess(),m_pfnOrig,m_bOldBytes,5,&n);
		//修改前五个字节为jmp机器指令
		m_bNewBytes[0] = '\xe9';
		*(DWORD*)(m_bNewBytes + 1) = (DWORD)pfnHookFunc - (DWORD)m_pfnOrig - 5;
		WriteProcessMemory(GetCurrentProcess(), m_pfnOrig, m_bNewBytes, 5, &n);
		bRet = TRUE;
	}
	return bRet;
}

VOID InLine::Unhook()
{
	if (m_pfnOrig != 0)
	{
		DWORD n = 0;
		WriteProcessMemory(GetCurrentProcess(), m_pfnOrig, m_bOldBytes, 5, &n);
	}
}

BOOL InLine::ReHook()
{
	BOOL bRet = FALSE;
	if (m_pfnOrig != 0)
	{
		DWORD n = 0;
		WriteProcessMemory(GetCurrentProcess(),m_pfnOrig,m_bNewBytes,5,&n);
		bRet = 1;
	}
	return bRet;
}