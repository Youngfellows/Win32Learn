#include<windows.h>
#include<iostream>
#include<stdio.h>
#include "WinMutex.h"


using namespace std;

HANDLE g_hMutex = 0;//»¥³â¾ä±ú

int main(int argc, char* argv[])
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	DWORD nID = 0;
	const char* pszText1 = "********";
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, (LPVOID)pszText1, 0, 0);
	const char* pszText2 = "========";
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, (LPVOID)pszText2, 0, 0);
	int nRet = getchar();
	CloseHandle(g_hMutex);
	return 0;
}


DWORD CALLBACK ThreadProc1(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (true)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pszText); i++)
		{
			printf("%c", pszText[i]);
			Sleep(125);
		}
		printf("\n");
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (true)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pszText); i++)
		{
			printf("%c", pszText[i]);
			Sleep(125);
		}
		printf("\n");
		ReleaseMutex(g_hMutex);
	}
	return 0;
}