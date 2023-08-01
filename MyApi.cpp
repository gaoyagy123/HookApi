// MyApi.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include "MyApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//
//#pragma data_seg(".MyShare")
//#pragma data_seg()
//#pragma comment(linker,"/SECTION:.MyShare,rws")

BEGIN_MESSAGE_MAP(CMyApiApp, CWinApp)

END_MESSAGE_MAP()

CMyApiApp::CMyApiApp() {}

CMyApiApp theApp;

BOOL WINAPI GetCursorPosProxy(LPPOINT lpPoint);
void WINAPI ChangeHook();
void WINAPI RemoveHook();
LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam);

extern "C" HHOOK __stdcall InitHook(DWORD hookThreadID);

#define WM_USERMOUSE WM_USER+200
#define WM_USERDESTROY WM_USER+201

PROC addr = GetProcAddress(GetModuleHandle("user32.dll"), "GetCursorPos");//保存函数的入口地址
DWORD *myaddr = (DWORD *)GetCursorPosProxy;
HHOOK myHook = NULL;
int mpx = 800;
int mpy = 600;
BYTE OLD[8];
bool mHasChanged = false;
HWND hWndMain;

void WINAPI ChangeHook()
{
	if (mHasChanged)
		return;
	mHasChanged = true;

	BYTE newCode[8];

	newCode[0] = 0xB8;
	CopyMemory(&newCode[1], &myaddr, 4);   //call 0x00000000
	newCode[5] = 0xFF;
	newCode[6] = 0xE0;
	newCode[7] = 0x90;
	
	CopyMemory(OLD, addr, sizeof(OLD));
	int ret = ::WriteProcessMemory(GetCurrentProcess(), addr, &newCode, sizeof(newCode), NULL);
}
void WINAPI RemoveHook()
{
	int ret = ::WriteProcessMemory(GetCurrentProcess(), addr, &OLD, sizeof(OLD), NULL);
}
BOOL WINAPI GetCursorPosProxy(LPPOINT lpPoint)
{
	lpPoint->x = mpx;
	lpPoint->y = mpy;
	return TRUE;
}

extern "C" HHOOK __stdcall InitHook(DWORD hookThreadID)
{
	myHook = ::SetWindowsHookEx(WH_CBT, GetMsgProc, ::GetModuleHandle("MyApi.dll"), 0);
	hWndMain = (HWND)hookThreadID;
	return myHook;
}
LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	CString mStr;
	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		mStr.Format("%x,WM_LBUTTONDOWN,%x\r\n", code, lParam);
		break;
	case WM_LBUTTONUP:
		mStr.Format("%x,WM_LBUTTONUP,%x\r\n", code, lParam);
		break;
	case WM_LBUTTONDBLCLK:
		mStr.Format("%x,WM_LBUTTONDBLCLK,%x\r\n", code, lParam);
		break;
	case WM_RBUTTONDOWN:
		mStr.Format("%x,WM_RBUTTONDOWN,%x\r\n", code, lParam);
		break;
	case WM_RBUTTONUP:
		mStr.Format("%x,WM_RBUTTONUP,%x\r\n", code, lParam);
		break;
	case WM_RBUTTONDBLCLK:
		mStr.Format("%x,WM_RBUTTONDBLCLK,%x\r\n", code, lParam);
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		mStr.Format("%x,%x,%x\r\n", code, wParam, lParam);
		break;
	}
	if (!mStr.IsEmpty())
		SetWindowText(hWndMain, mStr);
	//CString Str;
	//Str.Format("%x,%x,%x\r\n", code, wParam, lParam);
	//char pstr[256] = { 0 };
	//CString mStr;
	//GetWindowText(hWndMain, pstr, 256);
	//mStr = pstr;
	//mStr = Str + "\r\n" + mStr;
	//if (mStr.GetLength() > 10000)
	//	mStr = mStr.Left(10000);
	//PostMessage(hWndMain, wParam, MK_CONTROL, MAKELPARAM(pt.x, pt.y));
	
	return ::CallNextHookEx(myHook, code, wParam, lParam);
}


