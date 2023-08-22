#include<Windows.h>
#include<iostream>
#include<stdio.h>

HANDLE g_hSema = 0;//信号量句柄

DWORD CALLBACK ThreadProc(LPVOID pParam)
{
	while (true)
	{
		WaitForSingleObject(g_hSema, INFINITE);//等待信号量句柄有信号
		printf("********\n");
	}

	return 0;
}

int main(int argc, char* argv[])
{
	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);//创建信号量句柄
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &nID);//创建线程句柄，线程立即执行
	int result = getchar();
	ReleaseSemaphore(g_hSema, 6, NULL);//给信号量指定计数值
	WaitForSingleObject(hThread, INFINITE);//等待线程没有信号，线程执行完毕
	CloseHandle(g_hSema);//释放信号量句柄

	return 0;
}