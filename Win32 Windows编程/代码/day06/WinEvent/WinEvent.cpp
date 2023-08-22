#include <Windows.h>
#include <stdio.h>
HANDLE g_hEvent = 0;//接收事件句柄
DWORD CALLBACK PrintProc( LPVOID pParam ){
	while( 1 ) {
		WaitForSingleObject( g_hEvent,  INFINITE );
//		ResetEvent( g_hEvent );
		printf("****************\n");
	}
	return 0;
}
DWORD CALLBACK CtrlProc( LPVOID pParam ){
	while( 1 ){
		Sleep(1000);
		SetEvent( g_hEvent );
	}
	return 0;
}
int main(){
	g_hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread( NULL, 0, PrintProc, NULL, 0, &nID );
	hThread[1] = CreateThread( NULL, 0, CtrlProc, NULL, 0, &nID );
	WaitForMultipleObjects( 2, hThread, TRUE, INFINITE );
	CloseHandle( g_hEvent );
	return 0;
}