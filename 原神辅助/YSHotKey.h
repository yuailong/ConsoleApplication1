#pragma once
#include <windows.h>
#include <iostream>

#define VirtualCode_1 0x31 //1¼üĞéÄâÂë
#define VirtualCode_2 0x32 //2¼üĞéÄâÂë
#define VirtualCode_3 0x33 //3¼üĞéÄâÂë
#define VirtualCode_4 0x34 //4¼üĞéÄâÂë
#define VirtualCode_E 0x45 //E¼üĞéÄâÂë
#define VirtualCode_Q 0x51 //Q¼üĞéÄâÂë
#define VirtualCode_F8 0x77 //F8¼üĞéÄâÂë
#define VirtualCode_F9 0x78 //F9¼üĞéÄâÂë
#define VirtualCode_F10 0x79 //F10¼üĞéÄâÂë
#define VirtualCode_F11 0x7A //F11¼üĞéÄâÂë
#define VirtualCode_F12 0x7B //F12¼üĞéÄâÂë
#define VirtualCode_Space 0x20 //¿Õ¸ñ¼üĞéÄâÂë
#define VirtualCode_MouseLeftButton 0x01 //Êó±ê1ºÅ²à¼üĞéÄâÂë
#define VirtualCode_MouseSideButton1 0x05 //Êó±ê1ºÅ²à¼üĞéÄâÂë
#define VirtualCode_MouseSideButton2 0x06 //Êó±ê2ºÅ²à¼üĞéÄâÂë
#define VirtualCode_R 0x52 //Êó±ê2ºÅ²à¼üĞéÄâÂë
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
	void (*hotKeyDownCallback)(unsigned char virtualCode);
	void (*hotKeyHoldCallback)(unsigned char virtualCode);
	void (*hotKeyUpCallback)(unsigned char virtualCode);
	YSHotKey(const char* name,
			 unsigned char virtualCode,
			 unsigned char scanCode,
			 void (*hotKeyDownCallback)(unsigned char virtualCode),
			 void (*hotKeyHoldCallback)(unsigned char virtualCode),
			 void (*hotKeyUpCallback)(unsigned char virtualCode));
};
