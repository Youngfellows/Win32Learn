#include <windows.h>
#include "WinPaint.h"
#include "resource.h"

HINSTANCE g_hInstance = 0;

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
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将以上所有赋值全部写入操作系统。

	//2.在内存创建窗口
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 1500, 800, NULL, NULL, hIns, NULL);

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
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

/*
* 绘图
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
* 绘制点
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
* 绘制直线
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
* 绘制矩形
*/
void DrawRect(HDC hdc)
{
	Rectangle(hdc, 370, 110, 500, 210);
}

/*
* 绘制圆形
*/
void DrawEll(HDC hdc)
{
	Ellipse(hdc, 510, 50, 700, 150);
}

/*
* 绘制位图
*/
void DrawBmp(HDC hdc)
{
	//添加位图资源（不需要代码）
	HBITMAP hBmp = LoadBitmap(g_hInstance, (CHAR*)IDB_BITMAP2);
	HDC hMemdc = CreateCompatibleDC(hdc);
	//创建一个内存DC，并构建一个虚拟区域，并且内存DC在虚拟区域中绘图
	HGDIOBJ nOldBmp = SelectObject(hMemdc, hBmp);
	//将位图数据送给内存DC，内存DC在虚拟区域中将位图绘制出来。
	BitBlt(hdc, 100, 300, 48, 48, hMemdc, 0, 0, SRCCOPY);

	//将虚拟区域中绘制好的图像成像到窗口中
	StretchBlt(hdc, 300, 300, 96, 96, hMemdc, 0, 0, 48, 48, SRCCOPY);
	//缩放成像
	SelectObject(hMemdc, nOldBmp);
	DeleteObject(hBmp);
	DeleteDC(hMemdc);
}