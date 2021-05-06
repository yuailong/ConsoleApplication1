#pragma once
#include <windows.h>
#include <iostream>

#define VirtualCode_1 0x31 //1¼üĞéÄâÂë
#define VirtualCode_2 0x32 //2¼üĞéÄâÂë
#define VirtualCode_3 0x33 //3¼üĞéÄâÂë
#define VirtualCode_4 0x34 //4¼üĞéÄâÂë
#define VirtualCode_E 0x45 //E¼üĞéÄâÂë
#define VirtualCode_Q 0x51 //Q¼üĞéÄâÂë
#define VirtualCode_F8 VK_F8 //F8¼üĞéÄâÂë
#define VirtualCode_F9 VK_F9 //F9¼üĞéÄâÂë
#define VirtualCode_F10 VK_F10 //F10¼üĞéÄâÂë
#define VirtualCode_F11 VK_F11 //F11¼üĞéÄâÂë
#define VirtualCode_F12 VK_F12 //F12¼üĞéÄâÂë
#define VirtualCode_MouseSideButton1 VK_XBUTTON1 //Êó±ê1ºÅ²à¼üĞéÄâÂë
#define ScanCode_E 18 //E¼üÉ¨ÃèÂë
#define ScanCode_Q 56 //Q¼üÉ¨ÃèÂë

class YSHotKey{
	YSHotKey();
	unsigned char virtualCode;//ĞéÄâÂë
	unsigned char scanCode;//É¨ÃèÂë
	SHORT stateBefore{ 0 };//
	SHORT stateAfter{ 0 };//
	
public:
	const char* name;
	void getHotKeyStateAndCallback();
	void (*hotKeyDownCallback)();
	void (*hotKeyHoldCallback)();
	void (*hotKeyUpCallback)();
	YSHotKey(const char* name,
			 unsigned char virtualCode,
			 unsigned char scanCode,
			 void (*hotKeyDownCallback)(),
			 void (*hotKeyHoldCallback)(),
			 void (*hotKeyUpCallback)());
};
