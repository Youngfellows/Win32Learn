
#pragma comment( lib, "../Debug/Clib.lib" )
//通知链接器到哪抓源码
int main(){
	int sum, sub;

	sum = Clib_add(5,3);
	sub = Clib_sub(5,3);

	printf("sum=%d,sub=%d\n", sum,sub);
	return 0;
}