#include <iostream>

using namespace std;

int CPPlib_add(int add1, int add2);
int CPPlib_sub(int sub1, int sub2);
//以上代码给编译器看的
#pragma comment(lib,"../x64/Debug/CPPlib.lib")//?CPPlib_add@@YAHHH@Z / ?CPPlib_sub@@YAHHH@Z

//给链接器看的
extern "C" int Clib_add(int add1, int add2);
extern "C" int Clib_sub(int sub1, int sub2);
#pragma comment(lib,"../x64/Debug/Clib.lib")//Clib_add  /  Clib_sub


int main(int argc, char* argv[])
{
	int sum = CPPlib_add(5, 4);//?CPPlib_add@@YAHHH@Z
	int sub = CPPlib_sub(5, 4);//?CPPlib_sub@@YAHHH@Z
	cout << "sum=" << sum << ",sub=" << sub << endl;
	sum = Clib_add(5, 3);//Clib_add
	sub = Clib_sub(5, 3);//Clib_add
	cout << "sum=" << sum << ",sub=" << sub << endl;
	return 0;
}