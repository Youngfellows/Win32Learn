#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstanc = 0;

/*
* 在主窗口WM_CREATE消息中利用 SetMenu函数设置菜单
*/
void OnCreate(HWND hWnd)
{
	HMENU hMenu = LoadMenu(g_hInstanc, (char*)IDR_MENU1);
	SetMenu(hWnd, hMenu);
}

void OnContextMenu(HWND hWnd, LPARAM lParam)
{
	HMENU hMain = LoadMenu(g_hInstanc, (CHAR*)IDR_MENU1);
	HMENU hPopup = GetSubMenu(hMain, 0);
	TrackPopupMenu(hPopup, TPM_LEFTALIGN | TPM_TOPALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEW:
		MessageBox(hWnd, "新建被点击", "Infor", MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hWnd, "退出被点击", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, "关于被点击", "Infor", MB_OK);
		break;
	default:
		break;
	}
}

/*
* 窗口处理函数( 自定义，处理消息)
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		OnCreate(hWnd);
		break;
	case WM_COMMAND://处理菜单项点击事件
		OnCommand(hWnd, wParam);
		break;
	case WM_CONTEXTMENU://创建右键菜单
		OnContextMenu(hWnd, lParam);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

/*
* 入口函数
*/
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstanc = hIns;

	//1.注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	//wc.lpszMenuName = (char*)IDR_MENU1;// 注册窗口类时设置菜单
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将以上所有赋值全部写入操作系统。

	//2.在内存创建窗口
	//HMENU hMenu = LoadMenu(hIns, (char*)IDR_MENU1);
	//HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
	//	100, 100, 500, 500, NULL, hMenu, hIns, NULL);//创建窗口传参设置菜单

	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	//3.显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//4.消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg); // 将消息交给窗口处理函数来处理。
	}
	return 0;
}