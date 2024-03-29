#include <windows.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;

void OnCreate( HWND hWnd ){
	HMENU hMenu = LoadMenu( g_hInstance, (char*)IDR_MENU1 );
	SetMenu( hWnd, hMenu );
}
void OnCommand( HWND hWnd, WPARAM wParam ){
	switch( LOWORD(wParam)){
	case ID_NEW:
		MessageBox( hWnd, "新建被点击", "Infor", MB_OK );
		break;
	case ID_EXIT:
		MessageBox( hWnd, "退出被点击", "Infor", MB_OK );
		break;
	case ID_ABOUT:
		MessageBox( hWnd, "关于被点击", "Infor", MB_OK );
		break;
	}
}
void OnContextMenu( HWND hWnd, LPARAM lParam ){
	HMENU hMain = LoadMenu( g_hInstance, (CHAR*)IDR_MENU1);
	HMENU hPopup = GetSubMenu( hMain, 0 );
	TrackPopupMenu( hPopup, TPM_LEFTALIGN | TPM_TOPALIGN, 
											LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL );
}
//窗口处理函数( 自定义，处理消息)
LRESULT CALLBACK WndProc( HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam ){
	switch(msgID){
	case WM_CONTEXTMENU:
		OnContextMenu( hWnd, lParam );
		break;
	case WM_COMMAND:
		OnCommand( hWnd, wParam );
		break;
	case WM_CREATE:
		OnCreate( hWnd );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}
	return DefWindowProc( hWnd, msgID, wParam, lParam );
}
//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	g_hInstance = hIns;
	//注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = NULL;//(char*)IDR_MENU1;
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