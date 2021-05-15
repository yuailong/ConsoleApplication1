#include "YSKeqing.h"
#include "main.h"
#include "YSHotKey.h"

/*
步骤1 E，下一步
步骤2 等待50毫秒，下一步
步骤3 按下左键，下一步
步骤4 如果重击完毕则弹起鼠标跳到第7步，否则等待50毫秒，下一步
步骤5 如果重击完毕则弹起鼠标跳到第7步，否则E，下一步
步骤6 如果重击完毕则弹起鼠标跳到第7步，否则等待50毫秒回到第5步
步骤7 等待50毫秒回到第3步
*/
int keqingBuzhou = 1;
DWORD changeKeqingTime = 0;//切换到刻晴的时间
DWORD keqing_E_Time = 0;
DWORD keqing_MouseDown_Time = 0;
DWORD keqing_MouseUp_Time = 0;

void keqingDown(int selectedCharacterCodeAfter){
	if(selectedCharacterCodeBefore != selectedCharacterCodeAfter){
		changeKeqingTime = timeGetTime();
	}
	keqingBuzhou = 1;
}

void keqingHold(int selectedCharacterCodeAfter){
	//等待切换硬直时间
	if(nowTime - changeKeqingTime < changeDelay){
		return;
	}

	switch(keqingBuzhou){
	case 1:
		keybd_event(VirtualCode_E, ScanCode_E, 0, 0);//按下E键
		keybd_event(VirtualCode_E, ScanCode_E, KEYEVENTF_KEYUP, 0);//弹起E键
		keqing_E_Time = nowTime;
		keqingBuzhou = 2;
		break;

	case 2:
		if(nowTime - keqing_E_Time >= 50){
			keqingBuzhou = 3;
		}
		break;

	case 3:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		keqing_MouseDown_Time = nowTime;
		keqingBuzhou = 4;
		break;

	case 4:
		if(nowTime - keqing_MouseDown_Time >= 400){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
			keqing_MouseUp_Time = nowTime;
			keqingBuzhou = 7;
		}
		else if(nowTime - keqing_MouseDown_Time > 50){
			keqingBuzhou = 5;
		}
		break;

	case 5:
		if(nowTime - keqing_MouseDown_Time >= 400){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
			keqing_MouseUp_Time = nowTime;
			keqingBuzhou = 7;
		}
		else{
			keybd_event(VirtualCode_E, ScanCode_E, 0, 0);//按下E键
			keybd_event(VirtualCode_E, ScanCode_E, KEYEVENTF_KEYUP, 0);//弹起E键
			keqing_E_Time = nowTime;
			keqingBuzhou = 6;
		}
		break;

	case 6:
		if(nowTime - keqing_MouseDown_Time >= 400){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
			keqing_MouseUp_Time = nowTime;
			keqingBuzhou = 7;
		}
		else if(nowTime - keqing_E_Time >= 50){
			keqingBuzhou = 5;
		}
		break;

	case 7:
		if(nowTime - keqing_MouseUp_Time >= 100){
			keqingBuzhou = 3;
		}
		break;
	}
}

void keqingUp(int selectedCharacterCodeAfter){
	if(keqingBuzhou == 4 || keqingBuzhou == 5 || keqingBuzhou == 6){
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	}
}