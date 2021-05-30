#include "YSLongE.h"
#include "main.h"
#include "YSHotKey.h"

DWORD changeLong_E_Time = 0;//切换到长按E的角色的时间
DWORD down_E_Time = 0;//按下E键的时间
DWORD up_E_Time = 0;//弹起E键的时间
DWORD long_E_buzhou = 0;
DWORD long_E_A_Time = 0;
void longE_Down(int selectedCharacterCodeAfter) {
	if (selectedCharacterCodeBefore != selectedCharacterCodeAfter) {
		changeLong_E_Time = timeGetTime();
		long_E_buzhou = 0;
	}
}


void longE_Hold(int selectedCharacterCodeAfter) {
	//等待切换硬直时间
	if (nowTime - changeLong_E_Time < changeDelay) {
		return;
	}

	switch (long_E_buzhou) {
	case 0:
		keybd_event(VirtualCode_E, ScanCode_E, 0, 0);//按下E键
		down_E_Time = nowTime;
		long_E_A_Time = nowTime;
		long_E_buzhou = 1;
		printf("0");
		break;

	case 1:
		if (nowTime - down_E_Time >= 200) {
			long_E_buzhou = 2;
			printf("1");
		}
		break;

	case 2:
		if (nowTime - down_E_Time >= 1000) {
			keybd_event(VirtualCode_E, ScanCode_E, KEYEVENTF_KEYUP, 0);//弹起E键
			up_E_Time = nowTime;
			long_E_buzhou = 3;
			printf("2");
			break;
		}

		if (nowTime - long_E_A_Time >= 100) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
			long_E_A_Time = nowTime;
			printf("2-");
		}
		break;

	case 3:
		if (nowTime - up_E_Time >= 100) {
			long_E_buzhou = 0;
			printf("3");
		}
		break;
	}
}

void longE_Up(int selectedCharacterCodeAfter) {

}
