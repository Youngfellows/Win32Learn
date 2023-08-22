#include <windows.h>
HANDLE g_hOutput = 0;
void OnPaint( HWND hWnd ){
	char* pszText = "WM_PAINT\n";
	WriteConsole( g_hOutput, pszText, strlen(pszText), NULL, NULL );
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint( hWnd, &ps );
	TextOut( hdc, 100, 100, "hello",  5);
	EndPaint( hWnd, &ps );
	//���ϻ���ͼ�Ĵ��룬������ڴ���WM_PAINT��Ϣʱ���á�
}
//���ڴ�����( �Զ��壬������Ϣ)
LRESULT CALLBACK WndProc( HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam ){
	switch(msgID){
	case WM_PAINT:
		OnPaint( hWnd );
		break;
	case WM_LBUTTONDOWN:
		InvalidateRect( hWnd, NULL, TRUE );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );//����ʹGetMessage��������0
		break;
	}
	return DefWindowProc( hWnd, msgID, wParam, lParam );
}
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	AllocConsole();
	g_hOutput = GetStdHandle( STD_OUTPUT_HANDLE );
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
	wc.style = CS_HREDRAW | CS_VREDRAW;
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