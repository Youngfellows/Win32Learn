#include <windows.h>
void OnPaint( HWND hWnd ){
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint( hWnd, &ps );

	SetTextColor( hdc, RGB(255,0,0));
	SetBkColor( hdc, RGB(0,255,0));//只适用于OPAQUE模式
	SetBkMode( hdc, TRANSPARENT);
	HFONT hFont = CreateFont( 30, 0, 45, 0, 900, 1, 1, 1, GB2312_CHARSET, 0, 0, 0, 0, "黑体");
	HGDIOBJ nOldFont = SelectObject( hdc, hFont );
	char szText[] = "hello txt";
	TextOut( hdc, 100, 100, szText, strlen(szText));

	RECT rc;
	rc.left = 100;
	rc.top = 150;
	rc.right = 200;
	rc.bottom = 200;
//	Rectangle( hdc, 100, 150, 200, 200);
	DrawText( hdc, szText, strlen(szText), &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP );
	//DT_VCENTER / DT_BOTTOM 只适用于 DT_SINGLELINE 和 DT_WORDBREAK冲突

	SelectObject( hdc, nOldFont );
	DeleteObject( hFont );
	EndPaint( hWnd, &ps );
}
//窗口处理函数( 自定义，处理消息)
LRESULT CALLBACK WndProc( HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam ){
	switch(msgID){
	case WM_PAINT:
		OnPaint( hWnd );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}
	return DefWindowProc( hWnd, msgID, wParam, lParam );
}
//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	//注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &wc );//将以上所有赋值全部写入操作系统。
	//在内存创建窗口
	HWND hWnd = CreateWindowEx( 0, "Main", "window", WS_OVERLAPPEDWINDOW,
																	100, 100, 500, 500, NULL, NULL, hIns, NULL );
	//显示窗口
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
	//消息循环
	MSG nMsg = { 0 };
	while( GetMessage(&nMsg,NULL,0,0) ){
		TranslateMessage( &nMsg );
		DispatchMessage( &nMsg );//将消息交给窗口处理函数来处理。
	}
	return 0;
}