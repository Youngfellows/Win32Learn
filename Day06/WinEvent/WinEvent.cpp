#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "WinEvent.h"

using namespace std;

HANDLE g_hEvent = 0;//�����¼����

int main(int argc, char* argv[])
{
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);//�����¼����
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	const char* pszText = "********";
	hThread[0] = CreateThread(NULL, 0, PrintProc, (LPVOID)pszText, 0, &nID);//�����߳�
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);//�ȴ������߳����ź�ִ�����
	//int nRes = getchar();
	CloseHandle(g_hEvent);//�ͷ��¼����
	return 0;
}

DWORD CALLBACK PrintProc(LPVOID pParam)
{
	char* pszText = (char*)pParam;
	while (true)
	{
		WaitForSingleObject(g_hEvent, INFINITE);//�ȴ�g_hEvent�¼����źţ����û���¼��źţ�������
		printf("%s\n", pszText);
		ResetEvent(g_hEvent);//��λ�¼������¼����ó����ź�״̬
	}
	return 0;
}

DWORD CALLBACK CtrlProc(LPVOID pParam)
{
	while (true)
	{
		Sleep(1000);//����1��
		SetEvent(g_hEvent);//�����¼������¼����ó����ź�״̬
	}
	return 0;
}