#include <iostream>
#include <windows.h>

PIMAGE_EXPORT_DIRECTORY getExportDirectory(HMODULE moduleHandle);
UINT64 myGetProcAddress(HMODULE moduleHandle, const char* funcName);

int main(){
	//1. 声明函数指针类型，函数签名要和库里面的你要使用的函数一致，如：
	typedef int(__stdcall* LpAdd)(int, int);

	//2. 声明函数指针变量
	LpAdd add, sub, add2, sub2;

	//3. 动态加载dll到内存中
	wchar_t projectPath[1000];
	GetCurrentDirectory(1000, projectPath);//得到项目路径
	wcscat_s(projectPath, L"\\生成动态链接库.dll");
	HINSTANCE hModule = LoadLibrary(projectPath);
	if(!hModule){
		printf("LoadLibrary error :%x", GetLastError());
		return 0;
	}
	else{
		printf("LoadLibrary successfully\n");
	}

	//4. 使用win32的API, 函数GetProcAddress，根据导出函数名字或者序号获取函数地址
	add = (LpAdd)GetProcAddress(hModule, (char*)"add");
	sub = (LpAdd)GetProcAddress(hModule, (char*)5);

	//5. 使用自己实现的函数myGetProcAddress，根据导出函数名字后者序号获取函数地址
	add2 = (LpAdd)myGetProcAddress(hModule, (char*)"add");
	sub2 = (LpAdd)myGetProcAddress(hModule, (char*)5);

	//测试
	printf("add 函数地址：%p, sub 函数地址：%p\n", add, sub);
	printf("add2函数地址：%p, sub2函数地址：%p\n", add2, sub2);
	return 0;
}

//通过模块句柄获取导出表
PIMAGE_EXPORT_DIRECTORY getExportDirectory(HMODULE moduleHandle){
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)moduleHandle;
	PIMAGE_NT_HEADERS64 pNTHeader = (PIMAGE_NT_HEADERS64)((UINT64)moduleHandle + pDosHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER64 pOptionHeader = &(pNTHeader->OptionalHeader);
	IMAGE_DATA_DIRECTORY dd = pOptionHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	//如果没有导出表就返回 0
	if(dd.VirtualAddress == 0){
		return 0;
	}
	PIMAGE_EXPORT_DIRECTORY pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)(dd.VirtualAddress + (UINT64)moduleHandle);
	return pExportDirectory;
}

//通过导出函数名字或序号找函数地址
UINT64 myGetProcAddress(HMODULE moduleHandle, const char* funcNameOrOrdinal){
	//通过模块句柄找到导出表pExportDirectory
	PIMAGE_EXPORT_DIRECTORY pExportDirectory = getExportDirectory(moduleHandle);
	//如果没有导出表就返回0
	if(pExportDirectory == 0){
		return 0;
	}

	//找到函数地址表
	DWORD* pAddress = (DWORD*)(pExportDirectory->AddressOfFunctions + (UINT64)moduleHandle);

	//判断传进来的是函数序号还是函数名字，序号两个字节，所以必定小于等于0xFFFF，而内存0x0~0xFFFF是64K禁入区，肯定不是函数名字地址
	if((UINT64)funcNameOrOrdinal <= 0xFFFF){
		UINT64 index = (UINT64)funcNameOrOrdinal - pExportDirectory->Base;
		return pAddress[index] + (UINT64)moduleHandle;
	}

	//找到导出函数名字表 和 序号表
	DWORD* pName = (DWORD*)(pExportDirectory->AddressOfNames + (UINT64)moduleHandle);
	WORD* pOrdinal = (WORD*)(pExportDirectory->AddressOfNameOrdinals + (UINT64)moduleHandle);
	//找到序号
	WORD ordinal = 0x0;
	for(size_t i = 0; i < pExportDirectory->NumberOfNames; i++){
		char* name = (char*)(pName[i] + (UINT64)moduleHandle);
		if(strcmp(funcNameOrOrdinal, name) == 0){
			//再通过序号找到函数地址
			return pAddress[ordinal] + (UINT64)moduleHandle;
		}
	}
	//找不到返回0
	return 0;
}

