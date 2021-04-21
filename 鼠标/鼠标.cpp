// 鼠标.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <timeapi.h>
#pragma comment(lib, "Winmm.lib")

#define E键虚拟码 0x45
#define E键扫描码 18

#define Q键虚拟码 0x51
#define Q键扫描码 56

#define 开关键_F8_虚拟码 VK_F8
#define 一队_F9_虚拟码 VK_F9
#define 二队_F10_虚拟码 VK_F10
#define 三队_F10_虚拟码 VK_F11
#define 四队_F10_虚拟码 VK_F12


//当前角色
#define SelectedCharacter1_E_A 1001			//在1号位的，有E用E的，没E普攻的角色
#define SelectedCharacter2_E_A 1002			//在2号位的，有E用E的，没E普攻的角色
#define SelectedCharacter3_E_A 1003			//在3号位的，有E用E的，没E普攻的角色
#define SelectedCharacter4_E_A 1004			//在4号位的，有E用E的，没E普攻的角色
#define SelectedCharacter_Diluke 104			//迪卢克AEAEAE
#define SelectedCharacter_Keqing 203			//刻晴EE重击重击重击...

bool kaiguan = 1;
int selectedTeam = 0;//0代表第一队，1代表第二队...
int selectedCharacter = SelectedCharacter1_E_A;

SHORT kaiguanKeyStateBefore = 0;
SHORT key1StateBefore = 0;
SHORT key2StateBefore = 0;
SHORT key3StateBefore = 0;
SHORT key4StateBefore = 0;
SHORT team1KeyStateBefore = 0;
SHORT team2KeyStateBefore = 0;
SHORT team3KeyStateBefore = 0;
SHORT team4KeyStateBefore = 0;
SHORT mouseSideKey2StateBefore = 0;//鼠标侧面键2

SHORT kaiguanKeyStateAfter = 0;
SHORT key1StateAfter = 0;
SHORT key2StateAfter = 0;
SHORT key3StateAfter = 0;
SHORT key4StateAfter = 0;
SHORT team1KeyStateAfter = 0;
SHORT team2KeyStateAfter = 0;
SHORT team3KeyStateAfter = 0;
SHORT team4KeyStateAfter = 0;
SHORT mouseSideKey2StateAfter = 0;

DWORD beginTimeLongE = 0;

void keqingDown();//按下
void keqingHold();//按住
void keqingUp();//弹起

void longE_Down();//按下
void longE_Hold();//按住
void longE_Up();//弹起

void dilukeDown();//按下
void dilukeHold();//按住
void dilukeUp();//弹起

void E_A_Down(int ordinal);//按下
void E_A_Hold(int ordinal);//按住
void E_A_Up(int ordinal);//弹起

void funcForTeam1();
void funcForTeam2();
void funcForTeam3();
void funcForTeam4();

int main(){
	/*
	if(GetAsyncKeyState(VK_F8)){
		printf("F8的扫描码：%d\n", MapVirtualKeyA(VK_F8, 0));
	}
	*/

	printf("F8开关，F9一队(默认)，F10二队，F11三队，F12四队\n一队：EA、EA、EA、迪卢克\n二队：EA、EA、刻晴、琴\n");

	while(true){
		//脚本开关
		kaiguanKeyStateAfter = GetAsyncKeyState(开关键_F8_虚拟码);
		if(kaiguanKeyStateBefore && !kaiguanKeyStateAfter){//正在抬起开关键
			kaiguan = !kaiguan;
		}
		kaiguanKeyStateBefore = kaiguanKeyStateAfter;
		if(!kaiguan){
			continue;
		}

		team1KeyStateAfter = GetAsyncKeyState(一队_F9_虚拟码);
		team2KeyStateAfter = GetAsyncKeyState(二队_F10_虚拟码);
		team3KeyStateAfter = GetAsyncKeyState(三队_F10_虚拟码);
		team4KeyStateAfter = GetAsyncKeyState(四队_F10_虚拟码);
		key1StateAfter = GetAsyncKeyState(0x31);
		key2StateAfter = GetAsyncKeyState(0x32);
		key3StateAfter = GetAsyncKeyState(0x33);
		key4StateAfter = GetAsyncKeyState(0x34);
		mouseSideKey2StateAfter = GetAsyncKeyState(VK_XBUTTON1);

		if(team1KeyStateBefore && !team1KeyStateAfter){
			selectedTeam = 0;
			printf("切换到一队");
		}
		else if(team2KeyStateBefore && !team2KeyStateAfter){
			selectedTeam = 1;
			printf("切换到一队");
		}
		else if(team3KeyStateBefore && !team3KeyStateAfter){
			selectedTeam = 2;
			printf("切换到三队");
		}
		else if(team4KeyStateBefore && !team4KeyStateAfter){
			selectedTeam = 3;
			printf("切换到四队");
		}

		switch(selectedTeam){
		case 0:
			funcForTeam1();
			break;
		case 1:
			funcForTeam2();
			break;
		case 2:
			funcForTeam3();
			break;
		case 3:
			funcForTeam4();
			break;
		}

		switch(selectedCharacter){
		case SelectedCharacter_Keqing:
			if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				keqingDown();
			}
			else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				keqingHold();
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
				keqingUp();
			}
			break;

		case SelectedCharacter_Diluke:
			if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				dilukeDown();
			}
			else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				dilukeHold();
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
				dilukeUp();
			}
			break;

		case SelectedCharacter1_E_A:
			if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Down(SelectedCharacter1_E_A);
			}
			else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Hold(SelectedCharacter1_E_A);
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
				E_A_Up(SelectedCharacter1_E_A);
			}
			break;

		case SelectedCharacter2_E_A:
			if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Down(SelectedCharacter2_E_A);
			}
			else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Hold(SelectedCharacter2_E_A);
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
				E_A_Up(SelectedCharacter2_E_A);
			}
			break;

		case SelectedCharacter3_E_A:
			if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Down(SelectedCharacter3_E_A);
			}
			else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Hold(SelectedCharacter3_E_A);
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
				E_A_Up(SelectedCharacter3_E_A);
			}
			break;

		case SelectedCharacter4_E_A:
			if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Down(SelectedCharacter4_E_A);
			}
			else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
				E_A_Hold(SelectedCharacter4_E_A);
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
				E_A_Up(SelectedCharacter4_E_A);
			}
			break;
		}

		team1KeyStateBefore = team1KeyStateAfter;
		team2KeyStateBefore = team2KeyStateAfter;
		team3KeyStateBefore = team3KeyStateAfter;
		team4KeyStateBefore = team4KeyStateAfter;
		key1StateBefore = key1StateAfter;
		key2StateBefore = key2StateAfter;
		key3StateBefore = key3StateAfter;
		key4StateBefore = key4StateAfter;
		mouseSideKey2StateBefore = mouseSideKey2StateAfter;
	}
}

void funcForTeam1(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up(SelectedCharacter1_E_A);
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up(SelectedCharacter2_E_A);
	}

	if(!key3StateBefore && key3StateAfter){
		E_A_Down(SelectedCharacter3_E_A);
	}
	else if(key3StateBefore && key3StateAfter){
		E_A_Hold(SelectedCharacter3_E_A);
	}
	else if(key3StateBefore && !key3StateAfter){
		E_A_Up(SelectedCharacter3_E_A);
	}

	if(!key4StateBefore && key4StateAfter){
		dilukeDown();
	}
	else if(key4StateBefore && key4StateAfter){
		dilukeHold();
	}
	else if(key4StateBefore && !key4StateAfter){
		dilukeUp();
	}
}

void funcForTeam2(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up(SelectedCharacter1_E_A);
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up(SelectedCharacter2_E_A);
	}

	if(!key3StateBefore && key3StateAfter){
		keqingDown();
	}
	else if(key3StateBefore && key3StateAfter){
		keqingHold();
	}
	else if(key3StateBefore && !key3StateAfter){
		keqingUp();
	}

	if(!key4StateBefore && key4StateAfter){
		keqingDown();
	}
	else if(key4StateBefore && key4StateAfter){
		keqingHold();
	}
	else if(key4StateBefore && !key4StateAfter){
		keqingUp();
	}
}

void funcForTeam3(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up(SelectedCharacter1_E_A);
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up(SelectedCharacter2_E_A);
	}

	if(!key3StateBefore && key3StateAfter){
		E_A_Down(SelectedCharacter3_E_A);
	}
	else if(key3StateBefore && key3StateAfter){
		E_A_Hold(SelectedCharacter3_E_A);
	}
	else if(key3StateBefore && !key3StateAfter){
		E_A_Up(SelectedCharacter3_E_A);
	}

	if(!key4StateBefore && key4StateAfter){
		E_A_Down(SelectedCharacter4_E_A);
	}
	else if(key4StateBefore && key4StateAfter){
		E_A_Hold(SelectedCharacter4_E_A);
	}
	else if(key4StateBefore && !key4StateAfter){
		E_A_Up(SelectedCharacter4_E_A);
	}
}

void funcForTeam4(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold(SelectedCharacter1_E_A);
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up(SelectedCharacter1_E_A);
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold(SelectedCharacter2_E_A);
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up(SelectedCharacter2_E_A);
	}

	if(!key3StateBefore && key3StateAfter){
		E_A_Down(SelectedCharacter3_E_A);
	}
	else if(key3StateBefore && key3StateAfter){
		E_A_Hold(SelectedCharacter3_E_A);
	}
	else if(key3StateBefore && !key3StateAfter){
		E_A_Up(SelectedCharacter3_E_A);
	}

	if(!key4StateBefore && key4StateAfter){
		E_A_Down(SelectedCharacter4_E_A);
	}
	else if(key4StateBefore && key4StateAfter){
		E_A_Hold(SelectedCharacter4_E_A);
	}
	else if(key4StateBefore && !key4StateAfter){
		E_A_Up(SelectedCharacter4_E_A);
	}
}



#define 步骤_刻晴一段E 1
#define 步骤_刻晴一段E等待后摇 2
#define 步骤_刻晴二段E 3
#define 步骤_刻晴二段E等待后摇 4
#define 步骤_刻晴重击按下鼠标 5
#define 步骤_刻晴重击等待或者E 6
#define 步骤_刻晴重击等待后摇 7


#define 刻晴重击按住时间 400
#define 刻晴重击松开鼠标后等待时间 100

int keqingBuzhou = 步骤_刻晴一段E;
DWORD changeKeqingTime = 0;
DWORD keqingFirst_E_Time = 0;
DWORD keqingSecond_E_Time = 0;
DWORD keqing_Down_Time = 0;
DWORD keqing_Up_Time = 0;

void keqingDown(){
	if(selectedCharacter != SelectedCharacter_Keqing){
		selectedCharacter = SelectedCharacter_Keqing;
		keqingBuzhou = 步骤_刻晴一段E;
		changeKeqingTime = timeGetTime();
	}
}

void keqingHold(){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeKeqingTime < 250){
		return;
	}

	switch(keqingBuzhou){
	case 步骤_刻晴一段E:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		keqingBuzhou = 步骤_刻晴一段E等待后摇;
		keqingFirst_E_Time = nowTime;
		break;

	case 步骤_刻晴一段E等待后摇:
		if(nowTime - keqingFirst_E_Time > 50){
			keqingBuzhou = 步骤_刻晴重击按下鼠标;
		}
		break;

	case 步骤_刻晴重击按下鼠标:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		keqingBuzhou = 步骤_刻晴重击等待或者E;
		keqing_Down_Time = nowTime;
		break;

	case 步骤_刻晴重击等待或者E:
		if(nowTime - keqing_Down_Time >= 刻晴重击按住时间){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
			keqingBuzhou = 步骤_刻晴重击等待后摇;
			keqing_Up_Time = nowTime;
		}
		else if(nowTime - keqingFirst_E_Time >= 50){
			keqingBuzhou = 步骤_刻晴二段E;
		}
		break;

	case 步骤_刻晴重击等待后摇:
		if(nowTime - keqing_Up_Time >= 刻晴重击松开鼠标后等待时间){
			keqingBuzhou = 步骤_刻晴重击按下鼠标;
		}
		break;

	case 步骤_刻晴二段E:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		keqingBuzhou = 步骤_刻晴二段E等待后摇;
		keqingFirst_E_Time = nowTime;
		break;

	case 步骤_刻晴二段E等待后摇:
		if(nowTime - keqingFirst_E_Time > 50){
			keqingBuzhou = 步骤_刻晴重击等待或者E;
		}
		break;
	}
}

void keqingUp(){
	if(keqingBuzhou == 步骤_刻晴重击等待或者E){
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	}
}



DWORD longE_buzhou = 0;
void longE_Down(){
	longE_buzhou = 0;
	beginTimeLongE = timeGetTime();
}

void longE_Hold(){
	DWORD nowTime = timeGetTime();
	DWORD time = nowTime - beginTimeLongE;

	switch(longE_buzhou){
	case 0:
		if(time >= 180){
			keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
			longE_buzhou = 1;
			beginTimeLongE = nowTime;
		}
		break;
	case 1:
		if(time >= 100){
			keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
			longE_buzhou = 2;
			beginTimeLongE = nowTime;
		}
		break;
	case 2:
		if(time >= 500){
			keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
			longE_buzhou = 1;
			beginTimeLongE = nowTime;
		}
		break;
	}
}

void longE_Up(){
	keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
}


#define 步骤_迪卢克第一次普攻 1
#define 步骤_迪卢克等待50毫秒 2
#define 步骤_迪卢克E或者A 3

int dilukeBuzhou = 步骤_迪卢克E或者A;
DWORD changeDilukeTime = 0;//切换到迪卢克的时间
DWORD diluke_E_or_A_Time = 0;//迪卢克上一次E或者A的时间
DWORD diluke_E_time = 0;//迪卢克上一次E的时间

void dilukeDown(){
	if(selectedCharacter != SelectedCharacter_Diluke){
		selectedCharacter = SelectedCharacter_Diluke;
		changeDilukeTime = timeGetTime();
		diluke_E_or_A_Time = changeDilukeTime;
	}
}

void dilukeHold(){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeDilukeTime < 250){
		return;
	}

	switch(dilukeBuzhou){
	case 步骤_迪卢克第一次普攻:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		diluke_E_or_A_Time = nowTime;
		diluke_E_time = nowTime;
		dilukeBuzhou = 步骤_迪卢克等待50毫秒;
		break;

	case 步骤_迪卢克等待50毫秒:
		if(nowTime - diluke_E_or_A_Time >= 50){
			dilukeBuzhou = 步骤_迪卢克E或者A;
		}
		break;

	case 步骤_迪卢克E或者A:
		if(nowTime - diluke_E_time >= 500){
			keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
			keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
			diluke_E_time = nowTime;
		}
		else{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		}
		dilukeBuzhou = 步骤_迪卢克等待50毫秒;
		diluke_E_or_A_Time = nowTime;
		break;
	}
}

void dilukeUp(){

}

int E_A_Buzhou = 0;
DWORD change_E_A_Time = 0;//切换到这个角色的时间
DWORD E_Time = 0;//E的时间
DWORD A_Time = 0;//A的时间
void E_A_Down(int ordinal){
	if(selectedCharacter != ordinal){
		selectedCharacter = ordinal;
		change_E_A_Time = timeGetTime();
	}
	E_A_Buzhou = 0;
}
void E_A_Hold(int ordinal){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - change_E_A_Time < 230){
		return;
	}

	switch(E_A_Buzhou){
	case 0:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		E_A_Buzhou = 1;
		E_Time = nowTime;
		break;

	case 1:
		if(nowTime - E_Time >= 20){
			E_A_Buzhou = 2;
		}
		break;

	case 2:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		E_A_Buzhou = 3;
		A_Time = nowTime;
		break;

	case 3:
		if(nowTime - A_Time >= 20){
			E_A_Buzhou = 0;
		}
		break;
	}
}

void E_A_Up(int ordinal){

}
