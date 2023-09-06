//#define UNICODE
#include <Windows.h>
#include <stdio.h>

void C_char() {
	const char* pszText = "hello char";
	printf("%d %s\n", strlen(pszText), pszText);//strlen
}

void W_char() {
	const wchar_t* pszText = L"hello wchar";
	int len = wcslen(pszText);
	wprintf(L"%d %s \n", len, pszText);
}

void T_char() {
	const	TCHAR* pszText = __TEXT("hello txt");//char* pszText = "hello txt"; / wchar_t* pszText = L"hello txt";
#ifdef UNICODE
	wprintf(L"%s\n", pszText);
#else
	printf("��:%s\n", pszText);
#endif
}
void PrintUnicode() {
	const char* pszText1 = "�����Կ���¼�Ż��������·羰�����˹�����ɵ������ſ�";
	printf("%s\n", pszText1);

	const wchar_t* pszText = L"�����Կ���¼�Ż��������·羰�����˹�����ɵ������ſ�";
	wprintf(L"%s\n", pszText);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(hOut, pszText, wcslen(pszText), NULL, NULL);
	printf("\n");
}
int main() {
	PrintUnicode();
	T_char();
	W_char();
	C_char();
	getchar();
	return 0;
}
