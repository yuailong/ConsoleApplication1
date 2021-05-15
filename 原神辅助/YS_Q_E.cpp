#include "YS_Q_E.h"
#include "main.h"
#include "YSHotKey.h"

//先Q再E再A
int Q_E_Buzhou = 0;
DWORD change_Q_E_Time = 0;//切换到这个角色的时间
DWORD QE_buzhou1_Time = 0;
DWORD QE_buzhou3_Time = 0;
DWORD QE_buzhou5_Time = 0;
void Q_E_Down(int selectedCharacterCodeAfter){
	if(selectedCharacterCodeBefore != selectedCharacterCodeAfter){
		selectedCharacterCodeBefore = selectedCharacterCodeAfter;
		change_Q_E_Time = timeGetTime();
	}
	Q_E_Buzhou = 1;
}

void Q_E_Hold(int selectedCharacterCodeAfter){
	//等待切换硬直时间
	if(nowTime - change_Q_E_Time < changeDelay){
		return;
	}

	switch(Q_E_Buzhou){
	case 1:
		keybd_event(VirtualCode_Q, ScanCode_Q, 0, 0);
		keybd_event(VirtualCode_Q, ScanCode_Q, KEYEVENTF_KEYUP, 0);
		QE_buzhou1_Time = nowTime;
		Q_E_Buzhou = 2;
		break;

	case 2:
		if(nowTime - QE_buzhou1_Time >= 100){
			Q_E_Buzhou = 3;
		}
		break;

	case 3:
		keybd_event(VirtualCode_E, ScanCode_E, 0, 0);
		keybd_event(VirtualCode_E, ScanCode_E, KEYEVENTF_KEYUP, 0);
		QE_buzhou3_Time = nowTime;
		Q_E_Buzhou = 4;
		break;

	case 4:
		if(nowTime - QE_buzhou3_Time >= 100){
			Q_E_Buzhou = 5;
		}
		break;

	case 5:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		QE_buzhou5_Time = nowTime;
		Q_E_Buzhou = 6;
		break;

	case 6:
		if(nowTime - QE_buzhou5_Time >= 100){
			Q_E_Buzhou = 1;
		}
		break;
	}
}

void Q_E_Up(int selectedCharacterCodeAfter){

}