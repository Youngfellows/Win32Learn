#include<windows.h>
#include<iostream>
#include<stdio.h>
#include "WinSema.h"

using namespace std;
HANDLE g_hSema = 0;//�ź������

int main(int argc, char* argv[])
{
	g_hSema = CreateSemaphore(NULL, 3, 11, NULL);//�����ź������

	DWORD nID = 0;
	const char* pszText = "********";
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)pszText, 0, &nID);//�����߳̾�����߳�����ִ��
	int nRet = getchar();
	ReleaseSemaphore(g_hSema, 6, NULL);//���ź���ָ������ֵ
	WaitForSingleObject(hThread, INFINITE);//�ȴ��߳�û���źţ��߳�ִ�����
	CloseHandle(g_hSema);//�ͷ��ź������
	return 0;
}

DWORD CALLBACK ThreadProc(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (true)
	{
		WaitForSingleObject(g_hSema, INFINITE);//�ȴ��ź���������ź�
		printf("%s\n", pszText);
	}
	return 0;
}