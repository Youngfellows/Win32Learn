#include <Windows.h>
#include <iostream>
#include <stdio.h>

int g_value = 0;

DWORD CALLBACK ThreadProc1(LPVOID pParam)
{
	for (int i = 0; i < 100000000; i++)
	{
		//g_value++;
		InterlockedIncrement((unsigned long volatile*)&g_value);//原子锁函数
	}
	return 0;
}

DWORD CALLBACK ThreadProc2(LPVOID pParam)
{
	for (int i = 0; i < 100000000; i++)
	{
		//g_value++;
		InterlockedIncrement((unsigned long volatile*)&g_value);//原子锁函数
	}
	return 0;
}

int main()
{
	printf("Hello world\n");
	HANDLE hThread[2];
	DWORD nID = 0;
	hThread[0] = CreateThread(NULL, 0, ThreadProc1, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, ThreadProc2, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	printf("g_value = %d\n", g_value);

	return 0;
}