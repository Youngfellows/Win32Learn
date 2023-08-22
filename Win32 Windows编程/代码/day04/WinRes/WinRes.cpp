#include <windows.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;
void OnCommand( HWND hWnd, WPARAM wParam ){
	switch(LOWORD(wParam)){
	case ID_NEW:
		if(HIWORD(wParam)==0)
			MessageBox( hWnd, "�½��˵�����", "Infor", MB_OK );
		else if(HIWORD(wParam)==1)
			MessageBox( hWnd, "CTRL+M�����", "Infor", MB_OK );
		break;
	}
}
//���ڴ�����( �Զ��壬������Ϣ)
LRESULT CALLBACK WndProc( HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam ){
	switch(msgID){
	case WM_COMMAND:
		OnCommand( hWnd, wParam );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_SETCURSOR:
		{
			HCURSOR hCur = LoadCursor( g_hInstance, (char*)IDC_CURSOR2);
			if( LOWORD(lParam) == HTCLIENT ){
				SetCursor(  hCur );
				return 0;
			}else{
				//�ǿͻ����
			}			
		}
		break;
	}
	return DefWindowProc( hWnd, msgID, wParam, lParam );
}
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	g_hInstance = hIns;
	//ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor = LoadCursor( hIns, (char*)IDC_CURSOR1);
	wc.hIcon = LoadIcon( hIns, (char*)IDI_ICON1);
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = (CHAR*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &wc );//���������и�ֵȫ��д�����ϵͳ��
	//���ڴ洴������
	char szTitle[256]={ 0 };
	LoadString( hIns, IDS_WND, szTitle, 256);
	HWND hWnd = CreateWindowEx( 0, "Main", szTitle, WS_OVERLAPPEDWINDOW,
																	100, 100, 500, 500, NULL, NULL, hIns, NULL );
	//��ʾ����
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );

	HACCEL hAccel = LoadAccelerators(hIns, (CHAR*)IDR_ACCELERATOR1);
	//��Ϣѭ��
	MSG nMsg = { 0 };
	while( GetMessage(&nMsg,NULL,0,0) ){
		if( !TranslateAccelerator(hWnd, hAccel, &nMsg) ){
			TranslateMessage( &nMsg );
			DispatchMessage( &nMsg );//����Ϣ�������ڴ�����������
		}
	}
	return 0;
}