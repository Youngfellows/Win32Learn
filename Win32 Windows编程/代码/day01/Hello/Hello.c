#include <windows.h>
int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine,
                         int nCmdShow ){
    int nRet = MessageBox( NULL, "hello world", "Information", 
                       MB_YESNOCANCEL|MB_ICONERROR);
    if( nRet == IDYES){

    }else if(nRet==IDNO){

    }else{

    }
    return 0;
}