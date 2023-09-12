#include <windows.h>

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);
	SetTextColor(hdc, RGB(255, 0, 0));//����������ɫ
	SetBkColor(hdc, RGB(0, 255, 0));//�������ֱ���ɫ
	SetBkMode(hdc, OPAQUE);//�������ֱ���ģʽ:OPAQUE / TRANSPARENT
	HFONT hFont = CreateFont(30, 0, 45, 0, 900, 1, 1, 1, GB2312_CHARSET, 0, 0, 0, 0, "����");
	HGDIOBJ nOldFont = SelectObject(hdc, hFont);
	char szText[] = "Hello Visual Studio";
	TextOut(hdc, 100, 100, szText, strlen(szText));

	RECT rc;
	rc.left = 100;
	rc.top = 150;
	rc.right = 200;
	rc.bottom = 200;
	DrawText(hdc, szText, strlen(szText), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);

	SelectObject(hdc, nOldFont);
	DeleteObject(hFont);
	EndPaint(hWnd, &ps);
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
	case WM_PAINT:
		OnPaint(hWnd);
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
	//1.ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
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