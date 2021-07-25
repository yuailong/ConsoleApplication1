#include "YSWinApi.h"
#include <windows.h>
#include <iostream>

void getModuleAbsolutePath() {
	WCHAR fileAbsolutePath[MAX_PATH];
	GetModuleFileName(NULL, fileAbsolutePath, MAX_PATH);
	std::wcout << "Ä£¿éÂ·¾¶£º" << fileAbsolutePath << std::endl;
	std::cout << L"---------------" << std::endl;
}