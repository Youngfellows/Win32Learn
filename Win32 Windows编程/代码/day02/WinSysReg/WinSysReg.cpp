#include <windows.h>
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	//���ڴ洴������
	HWND hWnd = CreateWindow( "Edit", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL );
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