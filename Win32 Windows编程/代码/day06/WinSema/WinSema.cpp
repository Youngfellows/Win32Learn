#include <Windows.h>
#include <stdio.h>
HANDLE g_hSema = 0;//ÐÅºÅÁ¿¾ä±ú
DWORD CALLBACK TestProc( LPVOID pParam ){
	while(1){
		WaitForSingleObject( g_hSema, INFINITE );
		printf("*********\n");
	}
}
int main(){
	g_hSema = CreateSemaphore( NULL, 3, 10, NULL );
	DWORD nID = 0;
	HANDLE hThread = CreateThread( NULL, 0, TestProc, NULL, 0, &nID );
	getchar();
	ReleaseSemaphore( g_hSema, 10, NULL );
	WaitForSingleObject( hThread, INFINITE );
	CloseHandle( g_hSema );
	return 0;
}
