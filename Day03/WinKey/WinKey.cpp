#include <windows.h>
#include <stdio.h>

HANDLE g_hOutput = 0;

void OnKeyDown(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_KEYDOWN: ����ֵ=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnKeyUp(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_KEYUP: ����ֵ=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

void OnChar(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_CHAR: ����ֵ=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}

/*
* ���ڴ�����( �Զ��壬������Ϣ)
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		OnKeyDown(hWnd, wParam);
		break;
	case WM_KEYUP:
		OnKeyUp(hWnd, wParam);
		break;
	case WM_CHAR:
		OnChar(hWnd, wParam);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

/*
* ��ں���
*/
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();//��ȡDOS
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);


	//1.ע�ᴰ����
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
	RegisterClass(&wc);//���������и�ֵȫ��д�����ϵͳ��

	//2.���ڴ洴������
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	//3.��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//4.��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg); // ����Ϣ�������ڴ�����������
	}
	return 0;
}