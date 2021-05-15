#include "YS_E_Q.h"
#include "main.h"
#include "YSHotKey.h"

int E_Q_Buzhou = 1;
DWORD change_E_Q_Time = 0;//切换到这个角色的时间
DWORD EQ_buzhou1_Time = 0;
DWORD EQ_buzhou3_Time = 0;
DWORD EQ_buzhou5_Time = 0;
void E_Q_Down(int selectedCharacterCodeAfter){
	if(selectedCharacterCodeBefore != selectedCharacterCodeAfter){
		selectedCharacterCodeBefore = selectedCharacterCodeAfter;
		change_E_Q_Time = timeGetTime();
	}
	E_Q_Buzhou = 1;
}

void E_Q_Hold(int selectedCharacterCodeAfter){
	//等待切换硬直时间
	if(nowTime - change_E_Q_Time < changeDelay){
		return;
	}

	switch(E_Q_Buzhou){
	case 1:
		keybd_event(VirtualCode_E, ScanCode_E, 0, 0);
		keybd_event(VirtualCode_E, ScanCode_E, KEYEVENTF_KEYUP, 0);
		EQ_buzhou1_Time = nowTime;
		E_Q_Buzhou = 2;
		break;

	case 2:
		if(nowTime - EQ_buzhou1_Time >= 100){
			E_Q_Buzhou = 3;
		}
		break;

	case 3:
		keybd_event(VirtualCode_Q, ScanCode_Q, 0, 0);
		keybd_event(VirtualCode_Q, ScanCode_Q, KEYEVENTF_KEYUP, 0);
		EQ_buzhou3_Time = nowTime;
		E_Q_Buzhou = 4;
		break;

	case 4:
		if(nowTime - EQ_buzhou3_Time >= 100){
			E_Q_Buzhou = 5;
		}
		break;

	case 5:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		EQ_buzhou5_Time = nowTime;
		E_Q_Buzhou = 6;
		break;

	case 6:
		if(nowTime - EQ_buzhou5_Time >= 50){
			E_Q_Buzhou = 1;
		}
		break;
	}
}

void E_Q_Up(int selectedCharacterCodeAfter){

}