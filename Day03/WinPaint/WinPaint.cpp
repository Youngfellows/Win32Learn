#include <windows.h>

HANDLE g_hOutput = 0;

void OnPaint(HWND hWnd)
{
	const char* pszText = "WM_PAINT\n";
	WriteConsole(g_hOutput, pszText, strlen(pszText), NULL, NULL);

	//绘制文本
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);
	const char* pText = "Hello Visual Studio";
	TextOut(hdc, 100, 100, pText, strlen(pText));
	EndPaint(hWnd, &ps);
	//以上绘制图的代码，必须放在处理WM_PAINT消息时调用。
}


/*
* 窗口处理函数( 自定义，处理消息)
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY://窗口销毁事件
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN://单击鼠标左键事件
		InvalidateRect(hWnd, NULL, TRUE);//触发WM_PAINT事件
		break;
	case WM_PAINT:
		OnPaint(hWnd);
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