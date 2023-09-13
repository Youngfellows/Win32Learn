#include <stdio.h>

#pragma comment(lib,"../x64/Debug/Clib.lib")

//通知链接器到哪抓源码
int main(int argc, char* argv[])
{
	int sum, sub;
	sum = Clib_add(5, 3);
	sub = Clib_sub(5, 3);
	printf("sum=%d,sub=%d\n", sum, sub);
	return 0;
}