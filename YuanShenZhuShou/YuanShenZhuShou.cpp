// YuanShenZhuShou.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "YSHotKey.h"
#include <windows.h>
#include <timeapi.h>
#pragma comment(lib, "Winmm.lib")

YSHotKey* hotKey1;
YSHotKey* hotKey2;
YSHotKey* hotKey3;
YSHotKey* hotKey4;
YSHotKey* hotKeyF8;
YSHotKey* hotKeyF9;
YSHotKey* hotKeyF10;
YSHotKey* hotKeyF11;
YSHotKey* hotKeyF12;
YSHotKey* hotKey_mouseSideBtn1;

void test(){
	std::cout << "按下F8键" << std::endl;
}

void test2(){
	std::cout << "按住F8键" << std::endl;
}

void test3(){
	std::cout << "弹起F8键" << std::endl;
}

int main(){
	hotKey1 = new YSHotKey("F8键",
						   VirtualCode_F8,
						   0,
						   test,
						   test2,
						   test3);

	while(true){
		hotKey1->getHotKeyStateAndCallback();
	}
	std::cout << "Hello World!\n";
}

