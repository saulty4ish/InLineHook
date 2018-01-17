// InLineHook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "InLine.h"

InLine HOOK;

//此函数的参数已经被MessageBox压入
int WINAPI MyMessageBox(HWND hWnd,LPCSTR lptext,LPCSTR lpCaption,UINT uType)
{
	HOOK.Unhook();
	MessageBoxA(hWnd, "HOOK流程", lpCaption, uType);
	MessageBoxA(hWnd, lptext, lpCaption, uType);
	HOOK.ReHook();
	return 0;
}


int main()
{
	MessageBoxA(NULL, "正常流程1", "test", MB_OK);
	HOOK.hook("User32.dll", "MessageBoxA", (PROC)MyMessageBox);
	//hook成功应该弹框“hook流程”，通过MyMessage函数输出的“被hook了”
	MessageBoxA(NULL, "被hook了1","test", MB_OK);
	MessageBoxA(NULL, "被hook了2","test", MB_OK);
	HOOK.Unhook();
	//取消了hook，那么就不会输出“hook流程”
	MessageBoxA(NULL, "正常流程2", "test", MB_OK);
}

