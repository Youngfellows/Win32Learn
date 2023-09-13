#include <windows.h>
#include <iostream>
#include "WinThread.h"
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Hello Window Thread" << endl;
	DWORD nId = 0;
	const char* pszText1 = "********";
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, (LPVOID)pszText1, 0, &nId);
	cout << "hThred1:" << hThread1 << endl;

	//WaitForSingleObject(hThread1, INFINITE);

	const char* pszText2 = "========";
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, (LPVOID)pszText2, CREATE_SUSPENDED, &nId);//挂起线程2
	cout << "hThread2:" << hThread2 << endl;
	int ret = getchar();
	SuspendThread(hThread1);//挂起线程1
	ResumeThread(hThread2);//唤醒线程2
	ret = getchar();
	TerminateThread(hThread2, 0);//结束线程2
	ret = getchar();
	return 0;
}

DWORD CALLBACK ThreadProc1(LPVOID pParam)
{
	DWORD nId = GetCurrentThreadId();
	HANDLE hThread = GetCurrentThread();
	cout << "ThreadProc1:: nId=" << nId << ",hThread:" << hThread << endl;

	char* pszText = (char*)pParam;
	int count = 0;
	while (true)
	{
		printf("%s\n", pszText);
		Sleep(1000);
		if (count == 10)
		{
			ExitThread(0);//结束函数所在的线程1
		}
		count++;
	}

	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID pParam)
{
	DWORD nId = GetCurrentThreadId();
	HANDLE hThread = GetCurrentThread();
	cout << "ThreadProc2:: nId=" << nId << ",hThread:" << hThread << endl;

	char* pszText = (char*)pParam;
	while (true)
	{
		printf("%s\n", pszText);
		Sleep(1000);
	}
	return 0;
}