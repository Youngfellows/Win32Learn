#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstanc = 0;

/*
* ��������WM_CREATE��Ϣ������ SetMenu�������ò˵�
*/
void OnCreate(HWND hWnd)
{
	HMENU hMenu = LoadMenu(g_hInstanc, (char*)IDR_MENU1);
	SetMenu(hWnd, hMenu);
}

void OnContextMenu(HWND hWnd, LPARAM lParam)
{
	HMENU hMain = LoadMenu(g_hInstanc, (CHAR*)IDR_MENU1);
	HMENU hPopup = GetSubMenu(hMain, 0);
	TrackPopupMenu(hPopup, TPM_LEFTALIGN | TPM_TOPALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEW:
		MessageBox(hWnd, "�½������", "Infor", MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hWnd, "�˳������", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, "���ڱ����", "Infor", MB_OK);
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
		OnCreate(hWnd);
		break;
	case WM_COMMAND://����˵������¼�
		OnCommand(hWnd, wParam);
		break;
	case WM_CONTEXTMENU://�����Ҽ��˵�
		OnContextMenu(hWnd, lParam);
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
	g_hInstanc = hIns;

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
	//wc.lpszMenuName = (char*)IDR_MENU1;// ע�ᴰ����ʱ���ò˵�
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//���������и�ֵȫ��д�����ϵͳ��

	//2.���ڴ洴������
	//HMENU hMenu = LoadMenu(hIns, (char*)IDR_MENU1);
	//HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
	//	100, 100, 500, 500, NULL, hMenu, hIns, NULL);//�������ڴ������ò˵�

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