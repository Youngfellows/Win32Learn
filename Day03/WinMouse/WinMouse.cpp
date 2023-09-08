#include <windows.h>
#include <stdio.h>

HANDLE g_hOutput = 0;

void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_LBUTTONDOWN,其他按键状态:%d,鼠标的位置:X=%d,Y=%d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_LBUTTONUP,其他按键状态:%d,鼠标的位置:X=%d,Y=%d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnRButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_RBUTTONDOWN,其他按键状态:%d,鼠标的位置:X=%d,Y=%d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnRButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_RBUTTONUP,其他按键状态:%d,鼠标的位置:X=%d,Y=%d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnLButtonDblClk(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_LBUTTONDBLCLK,其他按键状态:%d,鼠标的位置:X=%d,Y=%d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnRButtonDblClk(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_RBUTTONDBLCLK,其他按键状态:%d,鼠标的位置:X=%d,Y=%d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_MOUSEMOVE,其他按键状态:%d,鼠标的位置:X=%d,Y=%d\n", wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_MOUSEWHEEL,其他按键状态:%d,滚轮的偏移量:%d,鼠标的位置:X=%d,Y=%d\n", LOWORD(wParam), HIWORD(wParam), LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
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
	case WM_LBUTTONDOWN://鼠标左键按下
		OnLButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP://鼠标左键抬起
		OnLButtonUp(hWnd, wParam, lParam);
		break;
	case WM_RBUTTONDOWN://鼠标右键按下
		OnRButtonDown(hWnd, wParam, lParam);
		break;
	case WM_RBUTTONUP://鼠标右键抬起
		OnRButtonUp(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDBLCLK://鼠标左键双击
		OnLButtonDblClk(hWnd, wParam, lParam);
		break;
	case WM_RBUTTONDBLCLK://鼠标右键双击
		OnRButtonDblClk(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE://鼠标移动消息
		OnMouseMove(hWnd, wParam, lParam);
		break;
	case WM_MOUSEWHEEL://鼠标滚轮消息
		OnMouseWheel(hWnd, wParam, lParam);
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
	AllocConsole();//获取DOS
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

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
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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