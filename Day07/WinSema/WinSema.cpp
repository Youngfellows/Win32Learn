#include<Windows.h>
#include<iostream>
#include<stdio.h>

HANDLE g_hSema = 0;//�ź������

DWORD CALLBACK ThreadProc(LPVOID pParam)
{
	while (true)
	{
		WaitForSingleObject(g_hSema, INFINITE);//�ȴ��ź���������ź�
		printf("********\n");
	}

	return 0;
}

int main(int argc, char* argv[])
{
	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);//�����ź������
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &nID);//�����߳̾�����߳�����ִ��
	int result = getchar();
	ReleaseSemaphore(g_hSema, 6, NULL);//���ź���ָ������ֵ
	WaitForSingleObject(hThread, INFINITE);//�ȴ��߳�û���źţ��߳�ִ�����
	CloseHandle(g_hSema);//�ͷ��ź������

	return 0;
}