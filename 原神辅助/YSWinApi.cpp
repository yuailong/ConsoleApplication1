#include "YSWinApi.h"
#include <windows.h>

//获取模块文件所在目录
std::wstring* getModuleDirectory() {
	WCHAR str[MAX_PATH];
	GetModuleFileName(NULL, str, MAX_PATH);
	std::wstring* path  = new std::wstring(str);
	std::wstring::size_type index = path->find_last_of(L"\\");
	std::wstring* path2 = new std::wstring(*path, 0, index + 1);
#ifdef DEBUG
	setlocale(LC_ALL, "zh-CN");//设置控制台的区域性，从而改变控制台使用的编码格式
	std::wcout << L"目录：" << *path2 << std::endl << L"-----------------------" << std::endl;
#endif DEBUG
	return path2;
}