#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int nRet = MessageBox(NULL, "Hell Visual Studio", "Information", MB_YESNOCANCEL | MB_ICONERROR);
	if (nRet == IDYES)
	{
	}
	else if (nRet == IDNO)
	{

	}
	return 0;
}