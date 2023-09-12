#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstance = 0;

INT_PTR DlgProc(HWND hwndlg, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_INITDIALOG:
		MessageBox(hwndlg, "WM_INITDIALOG", "Infor", MB_OK);
		break;
	case WM_CREATE:
		MessageBox(hwndlg, "WM_INITDIALOG", "Infor", MB_OK);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			//销毁无模式对话框
			DestroyWindow(hwndlg);
		}
		break;
	default:
		break;
	}
	return FALSE;//将消息交给真正的对话框窗口处理函数的后续代码帮我们处理
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NOMODEL:
	{
		//创建无模式对话框
		HWND hDlg = CreateDialog(g_hInstance, (char*)IDD_DIALOG1, hWnd, DlgProc);
		ShowWindow(hDlg, SW_SHOW); //显示
		//UpdateWindow(hDlg);
	}
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
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
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
	g_hInstance = hIns;

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
	wc.lpszMenuName = (char*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将以上所有赋值全部写入操作系统。

	//2.在内存创建窗口
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