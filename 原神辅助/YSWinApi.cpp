#include "YSWinApi.h"
#include <windows.h>
#include <iostream>
#include <string.h>

void getModuleAbsolutePath() {
	setlocale(LC_ALL, "zh-CN");//���ÿ���̨�������ԣ��Ӷ��ı����̨ʹ�õı����ʽ
	WCHAR str[MAX_PATH];
	GetModuleFileName(NULL, str, MAX_PATH);
	std::wstring path(str);
	std::wcout << L"����·��1��" << path << std::endl << L"-----------------------" << std::endl;
	std::wstring::size_type index = path.find_last_of(L"\\");
	std::wstring path2(path, 0, index + 1);
	std::wcout << L"����·��2��" << path2 << std::endl << L"-----------------------" << std::endl;
}