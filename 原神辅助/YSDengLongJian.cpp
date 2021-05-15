#include "YSDengLongJian.h"
#include "main.h"
#include "YSHotKey.h"

//登龙剑
void dengLongJian(unsigned char virtualCode){
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);//按下鼠标右键
	DWORD time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);//弹起鼠标右键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	keybd_event(VirtualCode_Space, 0, 0, 0);//按下空格键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	keybd_event(VirtualCode_Space, 0, KEYEVENTF_KEYUP, 0);//弹起空格键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 128);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	time1 = timeGetTime();
	while(timeGetTime() - time1 < 64);
}