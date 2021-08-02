#include "YSWinApi.h"
#include <windows.h>
#include <iostream>
#include <string.h>

void getModuleAbsolutePath() {
	setlocale(LC_ALL, "zh-CN");//设置控制台的区域性，从而改变控制台使用的编码格式
	WCHAR str[MAX_PATH];
	GetModuleFileName(NULL, str, MAX_PATH);
	std::wstring path(str);
	std::wcout << L"绝对路径1：" << path << std::endl << L"-----------------------" << std::endl;
	std::wstring::size_type index = path.find_last_of(L"\\");
	std::wstring path2(path, 0, index + 1);
	std::wcout << L"绝对路径2：" << path2 << std::endl << L"-----------------------" << std::endl;
}