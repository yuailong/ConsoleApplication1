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
#define SelectedCharacter_Diluke 101		//迪卢克
#define SelectedCharacter_Keqing 102		//刻晴
#define SelectedCharacter_Qin 103			//琴
#define SelectedCharacter1_E_A 1001			//在1号位的，有E用E的，没E普攻的角色
#define SelectedCharacter2_E_A 1002			//在2号位的，有E用E的，没E普攻的角色
#define SelectedCharacter3_E_A 1003			//在3号位的，有E用E的，没E普攻的角色
#define SelectedCharacter4_E_A 1004			//在4号位的，有E用E的，没E普攻的角色
#define SelectedCharacter_LongE 1005		//长按E的角色



bool kaiguan = 1;
int selectedCharacterBefore = SelectedCharacter1_E_A;
int selectedCharacterAfter = SelectedCharacter1_E_A;
int team1[4] = { SelectedCharacter1_E_A, SelectedCharacter2_E_A, SelectedCharacter3_E_A, SelectedCharacter_Diluke };
int team2[4] = { SelectedCharacter1_E_A, SelectedCharacter_Qin, SelectedCharacter_Keqing, SelectedCharacter_LongE };
int team3[4] = { SelectedCharacter1_E_A, SelectedCharacter2_E_A, SelectedCharacter3_E_A, SelectedCharacter4_E_A };
int team4[4] = { SelectedCharacter1_E_A, SelectedCharacter2_E_A, SelectedCharacter3_E_A, SelectedCharacter4_E_A };
int(*pSelectedTeam)[4] = &team1;

#define 切换到一队输出的文本 "已切换到一队：EA、EA、EA、迪卢克\n"
#define 切换到二队输出的文本 "已切换到二队：EA、琴、刻晴、长按E角色\n"
#define 切换到三队输出的文本 "已切换到三队：EA、EA、EA、迪卢克\n"
#define 切换到四队输出的文本 "已切换到四队：EA、EA、EA、迪卢克\n"

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

void keyDown(int willSelecteCharacter);
void keyHold(int willSelecteCharacter);
void keyUp(int willSelecteCharacter);

void keqingDown(int willSelecteCharacter);//按下
void keqingHold(int willSelecteCharacter);//按住
void keqingUp(int willSelecteCharacter);//弹起

void longE_Down(int willSelecteCharacter);//按下
void longE_Hold(int willSelecteCharacter);//按住
void longE_Up(int willSelecteCharacter);//弹起

void dilukeDown(int willSelecteCharacter);//按下
void dilukeHold(int willSelecteCharacter);//按住
void dilukeUp(int willSelecteCharacter);//弹起

void E_A_Down(int willSelecteCharacter);//按下
void E_A_Hold(int willSelecteCharacter);//按住
void E_A_Up(int willSelecteCharacter);//弹起

int main(){
	/*
	if(GetAsyncKeyState(VK_F8)){
		printf("F8的扫描码：%d\n", MapVirtualKeyA(VK_F8, 0));
	}
	*/

	printf("F8开关，F9一队(默认)，F10二队，F11三队，F12四队\n");
	printf(切换到一队输出的文本);

	while(true){
		//脚本开关
		kaiguanKeyStateAfter = GetAsyncKeyState(开关键_F8_虚拟码);
		if(kaiguanKeyStateBefore && !kaiguanKeyStateAfter){//正在抬起开关键
			kaiguan = !kaiguan;
			printf(kaiguan ? "已开启\n" : "已关闭\n");
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
			pSelectedTeam = &team1;
			printf(切换到一队输出的文本);
		}
		else if(team2KeyStateBefore && !team2KeyStateAfter){
			pSelectedTeam = &team2;
			printf(切换到二队输出的文本);
		}
		else if(team3KeyStateBefore && !team3KeyStateAfter){
			pSelectedTeam = &team3;
			printf(切换到三队输出的文本);
		}
		else if(team4KeyStateBefore && !team4KeyStateAfter){
			pSelectedTeam = &team4;
			printf(切换到四队输出的文本);
		}

		if(!key1StateBefore && key1StateAfter){
			selectedCharacterAfter = (*pSelectedTeam)[0];
			keyDown(selectedCharacterAfter);
		}
		else if(key1StateBefore && key1StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(key1StateBefore && !key1StateAfter){
			keyUp(selectedCharacterAfter);
		}

		if(!key2StateBefore && key2StateAfter){
			selectedCharacterAfter = (*pSelectedTeam)[1];
			keyDown(selectedCharacterAfter);
		}
		else if(key2StateBefore && key2StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(key2StateBefore && !key2StateAfter){
			keyUp(selectedCharacterAfter);
		}

		if(!key3StateBefore && key3StateAfter){
			selectedCharacterAfter = (*pSelectedTeam)[2];
			keyDown(selectedCharacterAfter);
		}
		else if(key3StateBefore && key3StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(key3StateBefore && !key3StateAfter){
			keyUp(selectedCharacterAfter);
		}

		if(!key4StateBefore && key4StateAfter){
			selectedCharacterAfter = (*pSelectedTeam)[3];
			keyDown(selectedCharacterAfter);
		}
		else if(key4StateBefore && key4StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(key4StateBefore && !key4StateAfter){
			keyUp(selectedCharacterAfter);
		}

		if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
			keyDown(selectedCharacterAfter);
		}
		else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
			keyUp(selectedCharacterAfter);
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
		selectedCharacterBefore = selectedCharacterAfter;
	}
}

void keyDown(int willSelecteCharacter){
	switch(willSelecteCharacter){
	case SelectedCharacter_Keqing:
		keqingDown(willSelecteCharacter);
		break;

	case SelectedCharacter_Diluke:
		dilukeDown(willSelecteCharacter);
		break;

	case SelectedCharacter_Qin:
		keqingDown(willSelecteCharacter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Down(willSelecteCharacter);
		break;

	case SelectedCharacter_LongE:
		longE_Down(willSelecteCharacter);
		break;
	}
}

void keyHold(int willSelecteCharacter){
	switch(willSelecteCharacter){
	case SelectedCharacter_Keqing:
		keqingHold(willSelecteCharacter);
		break;

	case SelectedCharacter_Diluke:
		dilukeHold(willSelecteCharacter);
		break;

	case SelectedCharacter_Qin:
		keqingHold(willSelecteCharacter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Hold(willSelecteCharacter);
		break;

	case SelectedCharacter_LongE:
		longE_Hold(willSelecteCharacter);
		break;
	}
}

void keyUp(int willSelecteCharacter){
	switch(willSelecteCharacter){
	case SelectedCharacter_Keqing:
		keqingUp(willSelecteCharacter);
		break;

	case SelectedCharacter_Diluke:
		dilukeUp(willSelecteCharacter);
		break;

	case SelectedCharacter_Qin:
		keqingUp(willSelecteCharacter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Up(willSelecteCharacter);
		break;
	case SelectedCharacter_LongE:
		longE_Up(willSelecteCharacter);
		break;
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

void keqingDown(int willSelecteCharacter){
	if(selectedCharacterBefore != willSelecteCharacter){
		keqingBuzhou = 步骤_刻晴一段E;
		changeKeqingTime = timeGetTime();
	}
}

void keqingHold(int willSelecteCharacter){
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

void keqingUp(int willSelecteCharacter){
	if(keqingBuzhou == 步骤_刻晴重击等待或者E){
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	}
}



DWORD longE_buzhou = 0;
DWORD changeLong_E_Time = 0;//切换到长按E的角色的时间
DWORD beginLong_E_Time = 0;//按下E键的时间
void longE_Down(int willSelecteCharacter){
	if(selectedCharacterBefore != willSelecteCharacter){
		longE_buzhou = 0;//刚切换到这个角色时从第0步开始
		changeLong_E_Time = timeGetTime();
	}
}

void longE_Hold(int willSelecteCharacter){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeLong_E_Time < 250){
		return;
	}

	switch(longE_buzhou){
	case 0:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		beginLong_E_Time = nowTime;
		while(nowTime - beginLong_E_Time < 500){
			nowTime = timeGetTime();
		}
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		longE_buzhou = 0;
		break;
	}
}

void longE_Up(int willSelecteCharacter){
	
}


#define 步骤_迪卢克第一次普攻 1
#define 步骤_迪卢克等待50毫秒 2
#define 步骤_迪卢克E或者A 3

int dilukeBuzhou = 步骤_迪卢克E或者A;
DWORD changeDilukeTime = 0;//切换到迪卢克的时间
DWORD diluke_E_or_A_Time = 0;//迪卢克上一次E或者A的时间
DWORD diluke_E_time = 0;//迪卢克上一次E的时间

void dilukeDown(int willSelecteCharacter){
	if(selectedCharacterBefore != willSelecteCharacter){
		changeDilukeTime = timeGetTime();
		diluke_E_or_A_Time = changeDilukeTime;
	}
}

void dilukeHold(int willSelecteCharacter){
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

void dilukeUp(int willSelecteCharacter){

}

int E_A_Buzhou = 0;
DWORD change_E_A_Time = 0;//切换到这个角色的时间
DWORD E_Time = 0;//E的时间
DWORD A_Time = 0;//A的时间
void E_A_Down(int willSelecteCharacter){
	if(selectedCharacterBefore != willSelecteCharacter){
		selectedCharacterBefore = willSelecteCharacter;
		change_E_A_Time = timeGetTime();
	}
	E_A_Buzhou = 0;
}
void E_A_Hold(int willSelecteCharacter){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - change_E_A_Time < 250){
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
		if(nowTime - E_Time >= 100){
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
		if(nowTime - A_Time >= 100){
			E_A_Buzhou = 0;
		}
		break;
	}
}

void E_A_Up(int willSelecteCharacter){

}
