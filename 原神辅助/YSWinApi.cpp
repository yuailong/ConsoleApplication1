#include "YSWinApi.h"
#include <windows.h>

//��ȡģ���ļ�����Ŀ¼
std::wstring* getModuleDirectory() {
	WCHAR str[MAX_PATH];
	GetModuleFileName(NULL, str, MAX_PATH);
	std::wstring* path  = new std::wstring(str);
	std::wstring::size_type index = path->find_last_of(L"\\");
	std::wstring* path2 = new std::wstring(*path, 0, index + 1);
#ifdef DEBUG
	setlocale(LC_ALL, "zh-CN");//���ÿ���̨�������ԣ��Ӷ��ı����̨ʹ�õı����ʽ
	std::wcout << L"Ŀ¼��" << *path2 << std::endl << L"-----------------------" << std::endl;
#endif DEBUG
	return path2;
}