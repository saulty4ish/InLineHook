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
	//��ȡ���õ�dll�к������ڴ��еĵ�ַ
	m_pfnOrig = (PROC)GetProcAddress(GetModuleHandleA(pszModuleName), pszFunName);
	if (m_pfnOrig != 0)
	{
		DWORD n = 0;
		//��ȡ�ڴ��е�ַ��ǰ����ֽڣ�������oldbyte�У�����ֹͣ����
		ReadProcessMemory(GetCurrentProcess(),m_pfnOrig,m_bOldBytes,5,&n);
		//�޸�ǰ����ֽ�Ϊjmp����ָ��
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