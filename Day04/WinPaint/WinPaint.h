#pragma once
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam);

void OnPaint(HWND hWnd);//��ͼ

void DrawPit(HDC hdc);//���Ƶ�

void DrawLine(HDC hdc);//����ֱ��

void DrawRect(HDC hdc);//���ƾ���

void DrawEll(HDC hdc);//����Բ��

void DrawBmp(HDC hdc);//����λͼ