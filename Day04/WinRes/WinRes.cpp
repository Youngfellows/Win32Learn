#include <windows.h>
#include "resource.h"

HANDLE g_hOutput = 0;
HINSTANCE g_hInstance = 0;

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEW:
		if (HIWORD(wParam) == 0)
		{
			MessageBox(hWnd, "�½��˵�����", "Info", MB_OK);
		}
		else if (HIWORD(wParam) == 1)
		{
			MessageBox(hWnd, "Ctrl+N�����", "Info", MB_OK);
		}

		break;
	case ID_OPEN:
		if (HIWORD(wParam) == 0)
		{
			MessageBox(hWnd, "�򿪲˵�����", "Info", MB_OK);
		}
		else if (HIWORD(wParam) == 1)
		{
			MessageBox(hWnd, "Shift+O���", "Info", MB_OK);
		}

		break;
	case ID_EXIT:
		if (HIWORD(wParam) == 0)
		{
			MessageBox(hWnd, "�˳��˵�����", "Info", MB_OK);
		}
		else if (HIWORD(wParam) == 1)
		{
			MessageBox(hWnd, "Alt+E���", "Info", MB_OK);
		}

		break;
	case ID_ABOUT:
		if (HIWORD(wParam) == 0)
		{
			MessageBox(hWnd, "���ڲ˵�����", "Info", MB_OK);
		}
		else if (HIWORD(wParam) == 1)
		{
			MessageBox(hWnd, "Ctrl+Shift+A�����", "Info", MB_OK);
		}
		break;
	case ID_SET:
		if (HIWORD(wParam) == 1)
		{
			MessageBox(hWnd, "Ctrl+S�����", "Info", MB_OK);
		}
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
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_SETCURSOR:
	{
		//WriteConsole(g_hOutput, "WM_SETCURSOR", strlen("WM_SETCURSOR"), NULL, NULL);
		HCURSOR hCur = LoadCursor(g_hInstance, (CHAR*)IDC_CURSOR2);
		if (LOWORD(lParam) == HTCLIENT)
		{
			WriteConsole(g_hOutput, "WM_SETCURSOR\n", strlen("WM_SETCURSOR\n"), NULL, NULL);
			SetCursor(hCur);
			return 0;
		}
		else
		{
			//�ǿͻ����
		}
	}
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
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	g_hInstance = hIns;

	//1.ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(hIns, (CHAR*)IDC_CURSOR1);
	wc.hIcon = LoadIcon(hIns, (CHAR*)IDI_ICON1);//����ICON
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = (CHAR*)IDR_MENU1;//���ز˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//���������и�ֵȫ��д�����ϵͳ��

	//2.���ڴ洴������
	char szTitle[256] = { 0 };
	LoadString(hIns, IDS_WND, szTitle, 256);
	HWND hWnd = CreateWindowEx(0, "Main", szTitle, WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	//3.��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	HACCEL hAccel = LoadAccelerators(hIns, (CHAR*)IDR_ACCELERATOR1);

	//4.��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &nMsg))
		{
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg); // ����Ϣ�������ڴ�����������
		}
	}
	return 0;
}