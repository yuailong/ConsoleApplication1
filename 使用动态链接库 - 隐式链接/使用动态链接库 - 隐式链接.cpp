#include <iostream>
#pragma comment(lib,"生成动态链接库.lib")  

/*
导入函数
需要注意的是：
1.如果生成动态库时函数声明前面加了extern "C __declspec(dllexport)，则这里函数声明前就要写extern "C" __declspec(dllimport)
2.如果生成动态库时函数声明前面没有加extern "C __declspec(dllexport)，则这里函数声明前面只需要写__declspec(dllimport)
*/
__declspec(dllimport) int __stdcall add(int x, int y); 
__declspec(dllimport) int __stdcall sub(int x, int y);
int main(){
	int a = add(1, 2);
	int b = sub(2, 3);
	printf("test1:%d, test2:%d\n", a, b);
	return 0;
}