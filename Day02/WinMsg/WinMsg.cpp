#include <windows.h>
#include<stdio.h>


#define WM_MYMESSAGE WM_USER+10086

HANDLE g_hOutput = 0;//接收标准输出句柄

void OnCreate(HWND hWnd, LPARAM lParam)
{
	CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	char* pszText = (char*)pcs->lpCreateParams;
	MessageBox(hWnd, pszText, "Info", MB_OK);

	//发送自定义消息
	SendMessage(hWnd, WM_MYMESSAGE, 1, 2);

	//创建子窗口
	CreateWindowEx(0, "EDIT", "Hello World", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 200, 200, hWnd, NULL, 0, NULL);
}


void OnSize(HWND hWnd, LPARAM lParam)
{
	short nWidth = LOWORD(lParam);
	short nHight = HIWORD(lParam);
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_SIZE,宽:%d,高:%d\n", nWidth, nHight);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnMyMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "自定义消息被处理: wParam=%d,lParam=%d\n", wParam, lParam);
	MessageBox(hWnd, szText, "Infor", MB_OK);
}

/*
* 窗口处理函数( 自定义，处理消息)
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		//PostQuitMessage(0);//可以使GetMessage函数返回0
		PostMessage(hWnd, WM_QUIT, 0, 0);
		//SendMessage(hWnd, WM_QUIT, 0, 0);

		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			int nRet = MessageBox(hWnd, "是否退出", "infor", MB_YESNO);
			if (nRet == IDYES)
			{
				//什么都不写
			}
			else
			{
				return 0;
			}
		}
		break;
	case WM_CREATE:
		OnCreate(hWnd, lParam);
		break;

	case WM_SIZE:
		OnSize(hWnd, lParam);
		break;
	case WM_MYMESSAGE:
		OnMyMessage(hWnd, wParam, lParam);
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
	AllocConsole();//增加DOS
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(g_hOutput, "WinMain", strlen("WinMain"), NULL, NULL);

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
	const char* pszText = "Hello Visual Studio";
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, (LPVOID)pszText);

	//3.显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//4.消息循环
	MSG nMsg = { 0 };
	/*while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg); // 将消息交给窗口处理函数来处理。
	}*/
	while (true)
	{
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE))
		{
			//有消息
			if (GetMessage(&nMsg, NULL, 0, 0))
			{
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			//空闲处理
			WriteConsole(g_hOutput, "OnIdle", strlen("OnIdle"), NULL, NULL);
		}
	}

	return 0;
}