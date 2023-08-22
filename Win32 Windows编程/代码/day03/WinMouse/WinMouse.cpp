#include <windows.h>
#include <stdio.h>
HANDLE g_hOutput = 0;
void OnLButtonDown( HWND hWnd, WPARAM wParam, LPARAM lParam ){
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONDOWN: ��������״̬:%d, X=%d,Y=%d\n",
								wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
void OnLButtonUp( HWND hWnd, WPARAM wParam, LPARAM lParam ){
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONUP: ��������״̬:%d, X=%d,Y=%d\n",
								wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
void OnMouseMove( HWND hWnd, WPARAM wParam, LPARAM lParam ){
	char szText[256] = { 0 };
	sprintf(szText, "WM_MOUSEMOVE: ��������״̬:%d, X=%d,Y=%d\n",
								wParam, LOWORD(lParam), HIWORD(lParam));
//	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
void OnLButtonDblClk( HWND hWnd ){
	char* szText = "WM_LBUTTONDBLCLK\n";
	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
void OnMouseWheel( HWND hWnd, WPARAM wParam ){
	short nDelta = HIWORD(wParam);//ƫ����
	char szText[256] = { 0 };
	sprintf( szText, "WM_MOUSEWHEEL:nDetal=%d\n", nDelta );
	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
//���ڴ�����( �Զ��壬������Ϣ)
LRESULT CALLBACK WndProc( HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam ){
	switch(msgID){
	case WM_MOUSEWHEEL:
		OnMouseWheel( hWnd, wParam );
		break;
	case WM_LBUTTONDBLCLK:
		OnLButtonDblClk( hWnd );
		break;
	case WM_MOUSEMOVE:
		OnMouseMove( hWnd, wParam, lParam );
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown( hWnd, wParam, lParam );
		break;
	case WM_LBUTTONUP:
		OnLButtonUp( hWnd, wParam, lParam );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}
	return DefWindowProc( hWnd, msgID, wParam, lParam );
}
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	AllocConsole( );
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass( &wc );//���������и�ֵȫ��д�����ϵͳ��
	//���ڴ洴������
	HWND hWnd = CreateWindowEx( 0, "Main", "window", WS_OVERLAPPEDWINDOW,
																	100, 100, 500, 500, NULL, NULL, hIns, NULL );
	//��ʾ����
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
	//��Ϣѭ��
	MSG nMsg = { 0 };
	while( GetMessage(&nMsg,NULL,0,0) ){
		TranslateMessage( &nMsg );
		DispatchMessage( &nMsg );//����Ϣ�������ڴ�����������
	}
	return 0;
}