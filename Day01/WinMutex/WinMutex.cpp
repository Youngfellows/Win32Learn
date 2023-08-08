#include<Windows.h>
#include<iostream>
#include<stdio.h>

HANDLE g_hMutex;

DWORD CALLBACK ThreadProc1(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (true)
	{
		//printf("%s\n", pszText);
		//Sleep(1000);
		//等待并获取互斥锁
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
		//printf("%s\n", pszText);
		//Sleep(1000);
		//等待并获取互斥锁
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pszText); i++)
		{
			printf("%c", pszText[i]);
			Sleep(125);
		}
		printf("\n");
		//释放互斥锁
		ReleaseMutex(g_hMutex);
	}
	return 0;
}


int main(int argc, char* argv[])
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);//创建互斥锁
	DWORD nID = 0;
	const char* pszText1 = "********";
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, (LPVOID)pszText1, 0, &nID);
	const char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, (LPVOID)pszText2, 0, &nID);
	int result = getchar();
	CloseHandle(g_hMutex);
	return 0;
}