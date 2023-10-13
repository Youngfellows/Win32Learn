#include <windows.h>
#include <stdio.h>

#define IDEVENT_VK_SCROLL 1

HANDLE g_hOutput = 0;

/*
*  Windows����ģ�ⰴ���¼�
*  ScrollLock ������: VK_SCROLL
*  NumLock ������: VK_NUMLOCK
*  CapsLock ��д��: VK_CAPITAL
*/
void SendInput()
{
	INPUT inputs[2] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_NUMLOCK;

	inputs[1].type = INPUT_KEYBOARD;
	//inputs[1].ki.wVk = VK_NUMLOCK/*VK_SCROLL*/;
	inputs[1].ki.wVk = VK_SCROLL/*VK_SCROLL*/;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	int nSize = ARRAYSIZE(inputs);
	UINT uSent;
	uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs))
	{
		const char *szText = "SendInput VK_SCROLL error";
		WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
	}
}


void OnPaint(HWND hWnd)
{
	const char *pszText = "WM_PAINT\n";
	WriteConsole(g_hOutput, pszText, strlen(pszText), NULL, NULL);

	//�����ı�
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);
	const char *pText = "��Ҫ����ѽ";
	TextOut(hdc, 100, 100, pText, strlen(pText));
	EndPaint(hWnd, &ps);
}

void OnTimer(HWND hWnd, WPARAM wParam)
{
	char szText[256] = { 0 };
	sprintf_s(szText, "WM_TIME: ��ʱ��ID=%d,", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
	switch (wParam)
	{
	case IDEVENT_VK_SCROLL:
		sprintf_s(szText, "%s\n", "IDEVENT_VK_SCROLL");
		WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
		SendInput();
		break;
	default:
		break;
	}
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
	case WM_CREATE:
		SetTimer(hWnd, IDEVENT_VK_SCROLL, 2000, NULL);
		break;
	case WM_TIMER:
		OnTimer(hWnd, wParam);
		break;
	case WM_PAINT:
		OnPaint(hWnd);
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
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, hIns, NULL);

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