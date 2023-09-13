#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "WinInterlock.h"

long g_value = 0;

int main(int argc, char* argv[])
{
	DWORD nID = 0;
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, ThreadProc1, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	printf("g_value=%d\n", g_value);
	//int nRet = getchar();
	return 0;
}

DWORD CALLBACK ThreadProc1(LPVOID pParam)
{
	for (int i = 0; i < 100000000; i++)
	{
		//g_value++;
		InterlockedIncrement(&g_value);//使用原子锁
	}
	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID pParam)
{
	for (int i = 0; i < 100000000; i++)
	{
		//g_value++;
		InterlockedIncrement(&g_value);//使用原子锁
	}
	return 0;
}