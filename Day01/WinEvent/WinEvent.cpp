#include<Windows.h>
#include<iostream>
#include<stdio.h>

HANDLE g_hEvent = 0;//接收事件句柄

DWORD CALLBACK PrintProc(LPVOID pParam)
{
	while (true)
	{
		WaitForSingleObject(g_hEvent, INFINITE);//等待g_hEvent事件有信号，如果没有事件信号，就阻塞
		const char* psxText = "********";
		printf("%s\n", psxText);
		ResetEvent(g_hEvent);//复位事件，将事件设置成无信号状态
	}
	return 0;
}

DWORD CALLBACK CtrlProc(LPVOID pParam)
{
	while (true)
	{
		Sleep(1000);//休眠1秒
		SetEvent(g_hEvent);//触发事件，将事件设置成有信号状态
	}
	return 0;
}

int main(int argc, char* argv[])
{
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);//创建线程
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);//等待两个线程无信号执行完毕
	CloseHandle(g_hEvent);//释放事件句柄

	return 0;
}