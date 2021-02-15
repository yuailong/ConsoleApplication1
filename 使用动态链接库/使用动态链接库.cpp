#include <iostream>
#include <windows.h>

int main(){
	//1. 声明函数指针类型，函数签名要和库里面的你要使用的函数一致，如：
	typedef int(__stdcall* LpAdd)(int, int);
	
	//2. 声明函数指针变量
	LpAdd add, sub;
	
	//3. 动态加载dll到内存中
	wchar_t projectPath[1000];
	GetCurrentDirectory(1000, projectPath);//得到项目路径
	wcscat_s(projectPath, L"\\生成动态链接库.dll");
	HINSTANCE hModule = LoadLibrary(projectPath);
	if(!hModule){
		printf("LoadLibrary error :%x", GetLastError());
		return 0;
	}
	
	//4. 根据函数名获取函数地址
	add = (LpAdd)GetProcAddress(hModule, "add");
	
	//5. 动态库隐藏了导出函数名字，但是我们知道函数序号，可以根据函数序号获取函数地址
	sub = (LpAdd)GetProcAddress(hModule, (char*)5);

	//测试
	int a = add(1, 2);
	int b = sub(2, 3);
	printf("address :%x, test1:%d, test2:%d\n", (DWORD)add, a, b);

	//7. 不再使用后，释放动态链接库
	FreeLibrary(hModule);
	return 0;
}