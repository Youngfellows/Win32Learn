#include <Windows.h>
#include <iostream>
#include <stdio.h>

DWORD CALLBACK ThreadProc1(LPVOID pParam)
{
	DWORD nId = GetCurrentThreadId();
	HANDLE hThread = GetCurrentThread();
	printf("ThreadProc1:: %ld\n", nId);

	char* pszText = (char*)pParam;
	int count = 0;
	while (true)
	{
		printf("%s\n", pszText);
		Sleep(1000);
		if (count == 10)
		{
			ExitThread(0);
		}
		count++;
	}
	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (true)
	{
		printf("%s\n", pszText);
		Sleep(1000);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	std::cout << "Hello world" << std::endl;
	DWORD nId = 0;
	const	char* pszText = "********";
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc1, (LPVOID)pszText, 0, &nId);

	//WaitForSingleObject(hThread, INFINITE);

	const char* pszText2 = "========";
	//CREATE_SUSPENDED
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, (LPVOID)pszText2, CREATE_SUSPENDED, &nId);
	int ret = getchar();
	SuspendThread(hThread);
	ResumeThread(hThread2);
	ret = getchar();
	TerminateThread(hThread2, 0);
	ret = getchar();
	return 0;
}