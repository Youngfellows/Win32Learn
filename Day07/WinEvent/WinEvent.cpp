#include<Windows.h>
#include<iostream>
#include<stdio.h>

HANDLE g_hEvent = 0;//�����¼����

DWORD CALLBACK PrintProc(LPVOID pParam)
{
	while (true)
	{
		WaitForSingleObject(g_hEvent, INFINITE);//�ȴ�g_hEvent�¼����źţ����û���¼��źţ�������
		const char* psxText = "********";
		printf("%s\n", psxText);
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

int main(int argc, char* argv[])
{
	g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);//�����߳�
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);//�ȴ������߳����ź�ִ�����
	CloseHandle(g_hEvent);//�ͷ��¼����

	return 0;
}