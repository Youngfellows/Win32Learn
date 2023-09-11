#pragma once
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam);

void OnPaint(HWND hWnd);//绘图

void DrawPit(HDC hdc);//绘制点

void DrawLine(HDC hdc);//绘制直线

void DrawRect(HDC hdc);//绘制矩形

void DrawEll(HDC hdc);//绘制圆形

void DrawBmp(HDC hdc);//绘制位图