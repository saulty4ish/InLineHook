// InLineHook.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "InLine.h"

InLine HOOK;

//�˺����Ĳ����Ѿ���MessageBoxѹ��
int WINAPI MyMessageBox(HWND hWnd,LPCSTR lptext,LPCSTR lpCaption,UINT uType)
{
	HOOK.Unhook();
	MessageBoxA(hWnd, "HOOK����", lpCaption, uType);
	MessageBoxA(hWnd, lptext, lpCaption, uType);
	HOOK.ReHook();
	return 0;
}


int main()
{
	MessageBoxA(NULL, "��������1", "test", MB_OK);
	HOOK.hook("User32.dll", "MessageBoxA", (PROC)MyMessageBox);
	//hook�ɹ�Ӧ�õ���hook���̡���ͨ��MyMessage��������ġ���hook�ˡ�
	MessageBoxA(NULL, "��hook��1","test", MB_OK);
	MessageBoxA(NULL, "��hook��2","test", MB_OK);
	HOOK.Unhook();
	//ȡ����hook����ô�Ͳ��������hook���̡�
	MessageBoxA(NULL, "��������2", "test", MB_OK);
}

