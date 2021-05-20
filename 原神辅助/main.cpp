// 鼠标.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "main.h"
#include <iostream>
#include <timeapi.h>
#include "YSHotKey.h"
#include "HotKeyStrategy1.h"
#include "HotKeyStrategy2.h"
#include "YSDengLongJian.h"
#pragma comment(lib, "Winmm.lib")


DWORD changeDelay = 250; //切换硬直时间
bool isNeedModifyTeam = 0;//是否需要修改队员
int selectedCharacterCodeBefore = SelectedCharacter1_E_A;
int selectedCharacterCodeAfter = SelectedCharacter1_E_A;
int team1[4] = { SelectedCharacter1_LongE, SelectedCharacter_Keqing, SelectedCharacter3_Q_E, SelectedCharacter_Youla };
int team2[4] = { SelectedCharacter1_LongE, SelectedCharacter2_Q_E, SelectedCharacter2_Q_E, SelectedCharacter_Diluke };
int team3[4] = { SelectedCharacter1_LongE, SelectedCharacter2_E_A, SelectedCharacter3_Q_E, SelectedCharacter_Diluke };
int team4[4] = { SelectedCharacter1_LongE, SelectedCharacter2_E_A, SelectedCharacter3_Q_E, SelectedCharacter_Keli };
int(*pSelectedTeam)[4] = &team1;

DWORD nowTime = 0;
HWND hYuanShenWindow;//原神窗口句柄
HWND hForegroundWindow;//前景窗口
DWORD count = 0;

YSHotKey* hotKey1;
YSHotKey* hotKey2;
YSHotKey* hotKey3;
YSHotKey* hotKey4;
YSHotKey* hotKeyF8;
YSHotKey* hotKeyF9;
YSHotKey* hotKeyF10;
YSHotKey* hotKeyF11;
YSHotKey* hotKeyF12;
YSHotKey* hotKey_mouseLeftBtn;
YSHotKey* hotKey_mouseSideBtn1;
YSHotKey* hotKey_mouseSideBtn2;
YSHotKey* hotKeyR;


void F8_KeyUpCallback(unsigned char virtualCode);
void F9_to_F12_KeyUpCallback(unsigned char virtualCode);


void printCode();
void printSelectedCode();

int main(){
	printf("F8开关，F9一队(默认)，F10二队，F11三队，F12四队\n------------------------------------------------\n");
	printCode();
	printf("已选择一队:%d,%d,%d,%d\n------------------------------------------------\n", (*pSelectedTeam)[0], (*pSelectedTeam)[1], (*pSelectedTeam)[2], (*pSelectedTeam)[3]);

	hotKey1 = new YSHotKey("1键",
						   VirtualCode_1,
						   0,
						   keyDownCallback,
						   keyHoldCallback,
						   keyUpCallback);

	hotKey2 = new YSHotKey("2键",
						   VirtualCode_2,
						   0,
						   keyDownCallback,
						   keyHoldCallback,
						   keyUpCallback);

	hotKey3 = new YSHotKey("3键",
						   VirtualCode_3,
						   0,
						   keyDownCallback,
						   keyHoldCallback,
						   keyUpCallback);

	hotKey4 = new YSHotKey("4键",
						   VirtualCode_4,
						   0,
						   keyDownCallback,
						   keyHoldCallback,
						   keyUpCallback);

	hotKeyF8 = new YSHotKey("F8键",
							VirtualCode_F8,
							0,
							NULL,
							NULL,
							F8_KeyUpCallback);

	hotKeyF9 = new YSHotKey("F9键",
							VirtualCode_F9,
							0,
							NULL,
							NULL,
							F9_to_F12_KeyUpCallback);

	hotKeyF10 = new YSHotKey("F10键",
							 VirtualCode_F10,
							 0,
							 NULL,
							 NULL,
							 F9_to_F12_KeyUpCallback);

	hotKeyF11 = new YSHotKey("F11键",
							 VirtualCode_F11,
							 0,
							 NULL,
							 NULL,
							 F9_to_F12_KeyUpCallback);

	hotKeyF12 = new YSHotKey("F12键",
							 VirtualCode_F12,
							 0,
							 NULL,
							 NULL,
							 F9_to_F12_KeyUpCallback);

	hotKey_mouseLeftBtn = new YSHotKey("鼠标左键",
									   VirtualCode_MouseLeftButton,
									   0,
									   NULL,
									   NULL,
									   NULL);

	hotKey_mouseSideBtn1 = new YSHotKey("鼠标1号侧键",
										VirtualCode_MouseSideButton1,
										0,
										keyDownCallback,
										keyHoldCallback,
										keyUpCallback);

	hotKey_mouseSideBtn2 = new YSHotKey("鼠标2号侧键",
										VirtualCode_MouseSideButton2,
										0,
										keyDownCallback2,
										keyHoldCallback2,
										keyUpCallback2);
	hotKeyR = new YSHotKey("R键",
						   VirtualCode_R,
						   0,
						   keyDownCallback2,
						   keyHoldCallback2,
						   keyUpCallback2);

	while(true){
		/*
		//打印扫描码
		if(GetAsyncKeyState(VK_F8)){
			printf("F8的扫描码：%d\n", MapVirtualKeyA(VK_F8, 0));
		}
		*/

		//每循环10万次，检测一次F8~F12键
		if(count % 0x186A0 == 0){
			hotKeyF8->getHotKeyStateAndCallback();
			hotKeyF9->getHotKeyStateAndCallback();
			hotKeyF10->getHotKeyStateAndCallback();
			hotKeyF11->getHotKeyStateAndCallback();
			hotKeyF12->getHotKeyStateAndCallback();
		}

		//每循环160万次，检测一次窗口
		if(count % 0x186A00 == 0){
			hYuanShenWindow = FindWindowA("UnityWndClass", "原神");
			hForegroundWindow = GetForegroundWindow();
		}
		count++;
		
		if(!hForegroundWindow || !hYuanShenWindow || hForegroundWindow != hYuanShenWindow){
			continue;
		}

		nowTime = timeGetTime();

		//每次循环都检测一次1~4键、鼠标侧键
		hotKey1->getHotKeyStateAndCallback();
		hotKey2->getHotKeyStateAndCallback();
		hotKey3->getHotKeyStateAndCallback();
		hotKey4->getHotKeyStateAndCallback();
		hotKey_mouseLeftBtn->getHotKeyStateAndCallback();
		hotKey_mouseSideBtn1->getHotKeyStateAndCallback();
		hotKey_mouseSideBtn2->getHotKeyStateAndCallback();
		hotKeyR->getHotKeyStateAndCallback();
	}
}

void F8_KeyUpCallback(unsigned char virtualCode){
	isNeedModifyTeam = !isNeedModifyTeam;
	if(isNeedModifyTeam){
		printCode();
		printf("修改4个队员的代码，用空格键分隔：");
		fflush(stdin);//将输入缓冲区清空
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;
		scanf_s("%d %d %d %d", &a, &b, &c, &d);
		if(a && b && c && d){
			(*pSelectedTeam)[0] = a;
			(*pSelectedTeam)[1] = b;
			(*pSelectedTeam)[2] = c;
			(*pSelectedTeam)[3] = d;
			printf("已选择%d,%d,%d,%d\n--------------------------------------------------\n", (*pSelectedTeam)[0], (*pSelectedTeam)[1], (*pSelectedTeam)[2], (*pSelectedTeam)[3]);
		}
		else{
			printf("没修改\n--------------------------------------------------\n");
		}
		isNeedModifyTeam = 0;
	}
}

void F9_to_F12_KeyUpCallback(unsigned char virtualCode){
	printCode();
	switch(virtualCode){
	case VirtualCode_F9:
		pSelectedTeam = &team1;
		printf("已选择一队：");
		break;

	case VirtualCode_F10:
		pSelectedTeam = &team2;
		printf("已选择二队：");
		break;

	case VirtualCode_F11:
		pSelectedTeam = &team3;
		printf("已选择三队：");
		break;

	case VirtualCode_F12:
		pSelectedTeam = &team4;
		printf("已选择四队：");
		break;
	}
	printSelectedCode();
}


void printCode(){
	printf("迪卢克 %d\n刻晴   %d\nEA     %d %d %d %d\n长E    %d %d %d %d\nQE     %d %d %d %d\nEQ     %d %d %d %d\n可莉   %d\n------------------------------------------------\n",
		   SelectedCharacter_Diluke,
		   SelectedCharacter_Keqing,
		   SelectedCharacter1_E_A,
		   SelectedCharacter2_E_A,
		   SelectedCharacter3_E_A,
		   SelectedCharacter4_E_A,
		   SelectedCharacter1_LongE,
		   SelectedCharacter2_LongE,
		   SelectedCharacter3_LongE,
		   SelectedCharacter4_LongE,
		   SelectedCharacter1_Q_E,
		   SelectedCharacter2_Q_E,
		   SelectedCharacter3_Q_E,
		   SelectedCharacter4_Q_E,
		   SelectedCharacter1_E_Q,
		   SelectedCharacter2_E_Q,
		   SelectedCharacter3_E_Q,
		   SelectedCharacter4_E_Q,
		   SelectedCharacter_Keli
	);
}

void printSelectedCode(){
	printf("%d, %d, %d, %d\n------------------------------------------------\n", (*pSelectedTeam)[0], (*pSelectedTeam)[1], (*pSelectedTeam)[2], (*pSelectedTeam)[3]);
}


