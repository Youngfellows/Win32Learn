#include <iostream>
#include "../ClassDll/ClassDll.h"

using namespace std;
#pragma comment(lib,"../x64/Debug/ClassDll.lib")

int main(int argc, char* argv[])
{
	CMath math;
	int sum = math.Add(5, 6);
	int sub = math.Sub(5, 7);
	cout << "sum=" << sum << ",sub=" << sub << endl;

	return 0;
}