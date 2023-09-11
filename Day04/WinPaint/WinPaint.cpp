#include <windows.h>
#include "WinPaint.h"
#include "resource.h"

HINSTANCE g_hInstance = 0;

/*
* ��ں���
*/
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hIns;

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
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 1500, 800, NULL, NULL, hIns, NULL);

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
* ��ͼ
*/
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);

	HPEN hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));//PS_SOLID
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);

	//HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hBrush = CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
	//HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
	HGDIOBJ nOldBrush = SelectObject(hdc, hBrush);

	DrawPit(hdc);
	DrawLine(hdc);
	DrawRect(hdc);
	DrawEll(hdc);
	DrawBmp(hdc);

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);

	SelectObject(hdc, nOldBrush);
	DeleteObject(hBrush);

	EndPaint(hWnd, &ps);
}

/*
* ���Ƶ�
*/
void DrawPit(HDC hdc)
{
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			SetPixel(hdc, i, j, RGB(i, j, 0));
		}
	}
}

/*
* ����ֱ��
*/
void DrawLine(HDC hdc)
{
	MoveToEx(hdc, 370, 50, NULL);
	LineTo(hdc, 500, 50);
	LineTo(hdc, 500, 100);
	LineTo(hdc, 370, 100);
	LineTo(hdc, 370, 50);
}

/*
* ���ƾ���
*/
void DrawRect(HDC hdc)
{
	Rectangle(hdc, 370, 110, 500, 210);
}

/*
* ����Բ��
*/
void DrawEll(HDC hdc)
{
	Ellipse(hdc, 510, 50, 700, 150);
}

/*
* ����λͼ
*/
void DrawBmp(HDC hdc)
{
	//���λͼ��Դ������Ҫ���룩
	HBITMAP hBmp = LoadBitmap(g_hInstance, (CHAR*)IDB_BITMAP2);
	HDC hMemdc = CreateCompatibleDC(hdc);
	//����һ���ڴ�DC��������һ���������򣬲����ڴ�DC�����������л�ͼ
	HGDIOBJ nOldBmp = SelectObject(hMemdc, hBmp);
	//��λͼ�����͸��ڴ�DC���ڴ�DC�����������н�λͼ���Ƴ�����
	BitBlt(hdc, 100, 300, 48, 48, hMemdc, 0, 0, SRCCOPY);

	//�����������л��ƺõ�ͼ����񵽴�����
	StretchBlt(hdc, 300, 300, 96, 96, hMemdc, 0, 0, 48, 48, SRCCOPY);
	//���ų���
	SelectObject(hMemdc, nOldBmp);
	DeleteObject(hBmp);
	DeleteDC(hMemdc);
}