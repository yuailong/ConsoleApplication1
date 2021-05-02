// 鼠标.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <timeapi.h>
#pragma comment(lib, "Winmm.lib")

#define E_KeyVirtualCode 0x45 //E键虚拟码
#define E_KeyScanCode 18 //E键扫描码

#define Q_KeyVirtualCode 0x51 //Q键虚拟码
#define Q_KeyScanCode 56 //Q键扫描码


//当前角色
#define SelectedCharacter_Diluke 1001		//迪卢克
#define SelectedCharacter_Keqing 1002		//刻晴
#define SelectedCharacter1_E_A 2001			//在1号位的，短按E的角色
#define SelectedCharacter2_E_A 2002			//在2号位的，短按E的角色
#define SelectedCharacter3_E_A 2003			//在3号位的，短按E的角色
#define SelectedCharacter4_E_A 2004			//在4号位的，短按E的角色
#define SelectedCharacter1_LongE 3001		///在1号位的，长按E的角色
#define SelectedCharacter2_LongE 3002		///在2号位的，长按E的角色
#define SelectedCharacter3_LongE 3003		///在3号位的，长按E的角色
#define SelectedCharacter4_LongE 3004		///在4号位的，长按E的角色
#define SelectedCharacter1_Q_E 4001			//在1号位的，先Q后E的角色
#define SelectedCharacter2_Q_E 4002			//在2号位的，先Q后E的角色
#define SelectedCharacter3_Q_E 4003			//在3号位的，先Q后E的角色
#define SelectedCharacter4_Q_E 4004			//在4号位的，先Q后E的角色
#define SelectedCharacter1_E_Q 5001			//在1号位的，先Q后E的角色
#define SelectedCharacter2_E_Q 5002			//在2号位的，先Q后E的角色
#define SelectedCharacter3_E_Q 5003			//在3号位的，先Q后E的角色
#define SelectedCharacter4_E_Q 5004			//在4号位的，先Q后E的角色
#define SelectedCharacter_Keli 6001			//可莉


DWORD changeDelay = 250; //切换硬直时间
bool isNeedModifyTeam = 0;//是否需要修改队员
int selectedCharacterBefore = SelectedCharacter1_E_A;
int selectedCharacterAfter = SelectedCharacter1_E_A;
int team1[4] = { SelectedCharacter1_LongE, SelectedCharacter2_Q_E, SelectedCharacter2_Q_E, SelectedCharacter_Diluke };
int team2[4] = { SelectedCharacter1_E_A, SelectedCharacter2_E_A, SelectedCharacter_Keqing, SelectedCharacter4_E_A };
int team3[4] = { SelectedCharacter1_LongE, SelectedCharacter2_E_A, SelectedCharacter3_Q_E, SelectedCharacter_Diluke };
int team4[4] = { SelectedCharacter1_LongE, SelectedCharacter2_E_A, SelectedCharacter3_Q_E, SelectedCharacter_Keli };
int(*pSelectedTeam)[4] = &team1;

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

SHORT modifyTeamKeyStateAfter = 0;//修改队员开关
SHORT key1StateAfter = 0;
SHORT key2StateAfter = 0;
SHORT key3StateAfter = 0;
SHORT key4StateAfter = 0;
SHORT team1KeyStateAfter = 0;
SHORT team2KeyStateAfter = 0;
SHORT team3KeyStateAfter = 0;
SHORT team4KeyStateAfter = 0;
SHORT mouseSideKey2StateAfter = 0;

DWORD nowTime = 0;
HWND hYuanShenWindow;//原神窗口句柄
HWND hForegroundWindow;//前景窗口
int count = 0;

void keyDown(int selectedCharacterAfter);
void keyHold(int selectedCharacterAfter);
void keyUp(int selectedCharacterAfter);

//刻晴
void keqingDown(int selectedCharacterAfter);//按下
void keqingHold(int selectedCharacterAfter);//按住
void keqingUp(int selectedCharacterAfter);//弹起

//长按E的角色
void longE_Down(int selectedCharacterAfter);//按下
void longE_Hold(int selectedCharacterAfter);//按住
void longE_Up(int selectedCharacterAfter);//弹起

//迪卢克
void dilukeDown(int selectedCharacterAfter);//按下
void dilukeHold(int selectedCharacterAfter);//按住
void dilukeUp(int selectedCharacterAfter);//弹起

//短按E的角色
void E_A_Down(int selectedCharacterAfter);//按下
void E_A_Hold(int selectedCharacterAfter);//按住
void E_A_Up(int selectedCharacterAfter);//弹起

//先Q后E的角色
void Q_E_Down(int selectedCharacterAfter);//按下
void Q_E_Hold(int selectedCharacterAfter);//按住
void Q_E_Up(int selectedCharacterAfter);//弹起

//先E后Q的角色
void E_Q_Down(int selectedCharacterAfter);//按下
void E_Q_Hold(int selectedCharacterAfter);//按住
void E_Q_Up(int selectedCharacterAfter);//弹起

//可莉
void keliDown(int selectedCharacterAfter);//按下
void keliHold(int selectedCharacterAfter);//按住
void keliUp(int selectedCharacterAfter);//弹起

void printCode();
void printSelectedCode();

int main(){
	/*
	if(GetAsyncKeyState(VK_F8)){
		//printf("F8的扫描码：%d\n", MapVirtualKeyA(VK_F8, 0));
	}
	*/
	hYuanShenWindow = FindWindowA("UnityWndClass", "原神");

	printf("F8开关，F9一队(默认)，F10二队，F11三队，F12四队\n------------------------------------------------\n");
	printCode();
	printf("已选择一队:%d,%d,%d,%d\n------------------------------------------------\n", (*pSelectedTeam)[0], (*pSelectedTeam)[1], (*pSelectedTeam)[2], (*pSelectedTeam)[3]);

	while(true){
		if(count % 100000 == 0){
			hForegroundWindow = GetForegroundWindow();

			modifyTeamKeyStateAfter = GetAsyncKeyState(VK_F8);
			if(kaiguanKeyStateBefore && !modifyTeamKeyStateAfter){//正在抬起开关键
				isNeedModifyTeam = !isNeedModifyTeam;
			}
			kaiguanKeyStateBefore = modifyTeamKeyStateAfter;
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

			team1KeyStateAfter = GetAsyncKeyState(VK_F9);
			team2KeyStateAfter = GetAsyncKeyState(VK_F10);
			team3KeyStateAfter = GetAsyncKeyState(VK_F11);
			team4KeyStateAfter = GetAsyncKeyState(VK_F12);
			if(team1KeyStateBefore && !team1KeyStateAfter){
				pSelectedTeam = &team1;
				printCode();
				printf("已选择一队：");
				printSelectedCode();
			}
			else if(team2KeyStateBefore && !team2KeyStateAfter){
				pSelectedTeam = &team2;
				printCode();
				printf("已选择二队：");
				printSelectedCode();
			}
			else if(team3KeyStateBefore && !team3KeyStateAfter){
				pSelectedTeam = &team3;
				printCode();
				printf("已选择三队：");
				printSelectedCode();
			}
			else if(team4KeyStateBefore && !team4KeyStateAfter){
				pSelectedTeam = &team4;
				printCode();
				printf("已选择四队：");
				printSelectedCode();
			}

			team1KeyStateBefore = team1KeyStateAfter;
			team2KeyStateBefore = team2KeyStateAfter;
			team3KeyStateBefore = team3KeyStateAfter;
			team4KeyStateBefore = team4KeyStateAfter;
		}
		count++;

		if(hForegroundWindow != hYuanShenWindow){
			continue;
		}

		nowTime = timeGetTime();

		key1StateAfter = GetAsyncKeyState(0x31);
		key2StateAfter = GetAsyncKeyState(0x32);
		key3StateAfter = GetAsyncKeyState(0x33);
		key4StateAfter = GetAsyncKeyState(0x34);
		mouseSideKey2StateAfter = GetAsyncKeyState(VK_XBUTTON1);

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
		else if(!key2StateBefore && key2StateAfter){
			selectedCharacterAfter = (*pSelectedTeam)[1];
			keyDown(selectedCharacterAfter);
		}
		else if(key2StateBefore && key2StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(key2StateBefore && !key2StateAfter){
			keyUp(selectedCharacterAfter);
		}
		else if(!key3StateBefore && key3StateAfter){
			selectedCharacterAfter = (*pSelectedTeam)[2];
			keyDown(selectedCharacterAfter);
		}
		else if(key3StateBefore && key3StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(key3StateBefore && !key3StateAfter){
			keyUp(selectedCharacterAfter);
		}
		else if(!key4StateBefore && key4StateAfter){
			selectedCharacterAfter = (*pSelectedTeam)[3];
			keyDown(selectedCharacterAfter);
		}
		else if(key4StateBefore && key4StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(key4StateBefore && !key4StateAfter){
			keyUp(selectedCharacterAfter);
		}
		else if(!mouseSideKey2StateBefore && mouseSideKey2StateAfter){
			keyDown(selectedCharacterAfter);
		}
		else if(mouseSideKey2StateBefore && mouseSideKey2StateAfter){
			keyHold(selectedCharacterAfter);
		}
		else if(mouseSideKey2StateBefore && !mouseSideKey2StateAfter){
			keyUp(selectedCharacterAfter);
		}

		key1StateBefore = key1StateAfter;
		key2StateBefore = key2StateAfter;
		key3StateBefore = key3StateAfter;
		key4StateBefore = key4StateAfter;
		mouseSideKey2StateBefore = mouseSideKey2StateAfter;
		selectedCharacterBefore = selectedCharacterAfter;
	}
}

void keyDown(int selectedCharacterAfter){
	switch(selectedCharacterAfter){
	case SelectedCharacter_Keqing:
		keqingDown(selectedCharacterAfter);
		break;

	case SelectedCharacter_Diluke:
		dilukeDown(selectedCharacterAfter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Down(selectedCharacterAfter);
		break;

	case SelectedCharacter1_LongE:
	case SelectedCharacter2_LongE:
	case SelectedCharacter3_LongE:
	case SelectedCharacter4_LongE:
		longE_Down(selectedCharacterAfter);
		break;

	case SelectedCharacter1_Q_E:
	case SelectedCharacter2_Q_E:
	case SelectedCharacter3_Q_E:
	case SelectedCharacter4_Q_E:
		Q_E_Down(selectedCharacterAfter);
		break;

	case SelectedCharacter1_E_Q:
	case SelectedCharacter2_E_Q:
	case SelectedCharacter3_E_Q:
	case SelectedCharacter4_E_Q:
		E_Q_Down(selectedCharacterAfter);
		break;

	case SelectedCharacter_Keli:
		keliDown(selectedCharacterAfter);
		break;
	}
}

void keyHold(int selectedCharacterAfter){
	switch(selectedCharacterAfter){
	case SelectedCharacter_Keqing:
		keqingHold(selectedCharacterAfter);
		break;

	case SelectedCharacter_Diluke:
		dilukeHold(selectedCharacterAfter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Hold(selectedCharacterAfter);
		break;

	case SelectedCharacter1_LongE:
	case SelectedCharacter2_LongE:
	case SelectedCharacter3_LongE:
	case SelectedCharacter4_LongE:
		longE_Hold(selectedCharacterAfter);
		break;

	case SelectedCharacter1_Q_E:
	case SelectedCharacter2_Q_E:
	case SelectedCharacter3_Q_E:
	case SelectedCharacter4_Q_E:
		Q_E_Hold(selectedCharacterAfter);
		break;

	case SelectedCharacter1_E_Q:
	case SelectedCharacter2_E_Q:
	case SelectedCharacter3_E_Q:
	case SelectedCharacter4_E_Q:
		E_Q_Hold(selectedCharacterAfter);
		break;

	case SelectedCharacter_Keli:
		keliHold(selectedCharacterAfter);
		break;
	}
}

void keyUp(int selectedCharacterAfter){
	switch(selectedCharacterAfter){
	case SelectedCharacter_Keqing:
		keqingUp(selectedCharacterAfter);
		break;

	case SelectedCharacter_Diluke:
		dilukeUp(selectedCharacterAfter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Up(selectedCharacterAfter);
		break;

	case SelectedCharacter1_LongE:
	case SelectedCharacter2_LongE:
	case SelectedCharacter3_LongE:
	case SelectedCharacter4_LongE:
		longE_Up(selectedCharacterAfter);
		break;

	case SelectedCharacter1_Q_E:
	case SelectedCharacter2_Q_E:
	case SelectedCharacter3_Q_E:
	case SelectedCharacter4_Q_E:
		Q_E_Up(selectedCharacterAfter);
		break;

	case SelectedCharacter1_E_Q:
	case SelectedCharacter2_E_Q:
	case SelectedCharacter3_E_Q:
	case SelectedCharacter4_E_Q:
		E_Q_Up(selectedCharacterAfter);
		break;

	case SelectedCharacter_Keli:
		keliUp(selectedCharacterAfter);
		break;
	}
}




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

void keqingDown(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		changeKeqingTime = timeGetTime();
	}
	keqingBuzhou = 1;
}

void keqingHold(int selectedCharacterAfter){
	//等待切换硬直时间
	if(nowTime - changeKeqingTime < changeDelay){
		return;
	}

	switch(keqingBuzhou){
	case 1:
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);//按下E键
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);//弹起E键
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
			keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);//按下E键
			keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);//弹起E键
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

void keqingUp(int selectedCharacterAfter){
	if(keqingBuzhou == 4 || keqingBuzhou == 5 || keqingBuzhou == 6){
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	}
}


DWORD changeLong_E_Time = 0;//切换到长按E的角色的时间
DWORD beginLong_E_Time = 0;//按下E键的时间
DWORD long_E_buzhou = 0;
DWORD long_E_A_Time = 0;
void longE_Down(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		changeLong_E_Time = timeGetTime();
	}

	//等待切换硬直时间
	while(nowTime - changeLong_E_Time < changeDelay){
		nowTime = timeGetTime();
	}

	long_E_buzhou = 0;
}


void longE_Hold(int selectedCharacterAfter){
	switch(long_E_buzhou){
	case 0:
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);//按下E键
		beginLong_E_Time = nowTime;
		long_E_A_Time = nowTime;
		long_E_buzhou = 1;
		break;

	case 1:
		if(nowTime - beginLong_E_Time >= 1000){
			keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);//弹起E键
			long_E_buzhou = 2;
		}

		if(nowTime - long_E_A_Time >= 100){
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
			long_E_A_Time = nowTime;
			
		}
		break;

	case 2:
		if(nowTime - beginLong_E_Time >= 1100)	{
			long_E_buzhou = 0;
		}
		break;
	}
}

void longE_Up(int selectedCharacterAfter){
	while(nowTime - beginLong_E_Time < 1000){
		nowTime = timeGetTime();
	}
	keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);//弹起E键
}


int dilukeBuzhou = 1;
DWORD changeDilukeTime = 0;//切换到迪卢克的时间
DWORD diluke_E_or_A_Time = 0;//迪卢克上一次E或者A的时间
DWORD diluke_E_Time = 0;//迪卢克上一次E的时间

void dilukeDown(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		changeDilukeTime = timeGetTime();
		diluke_E_or_A_Time = changeDilukeTime;
		diluke_E_Time = nowTime - 500;
	}
	
}

void dilukeHold(int selectedCharacterAfter){
	//等待切换硬直时间
	if(nowTime - changeDilukeTime < changeDelay){
		return;
	}

	switch(dilukeBuzhou){
	case 1:
		if(nowTime - diluke_E_Time >= 2000){
			keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);//按下E键
			keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);//弹起E键
			diluke_E_Time = nowTime;
		}
		else{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		}
		dilukeBuzhou = 2;
		diluke_E_or_A_Time = nowTime;
		break;

	case 2:
		if(nowTime - diluke_E_or_A_Time >= 100){
			dilukeBuzhou = 1;
		}
		break;
	}
}

void dilukeUp(int selectedCharacterAfter){

}


int E_A_Buzhou = 0;
DWORD change_E_A_Time = 0;//切换到这个角色的时间
DWORD E_Time = 0;//E的时间
DWORD A_Time = 0;//A的时间
void E_A_Down(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		selectedCharacterBefore = selectedCharacterAfter;
		change_E_A_Time = timeGetTime();
	}
	E_A_Buzhou = 0;
}

void E_A_Hold(int selectedCharacterAfter){


	//等待切换硬直时间
	if(nowTime - change_E_A_Time < changeDelay){
		return;
	}

	switch(E_A_Buzhou){
	case 0:
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);//按下E键
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);//弹起E键
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

void E_A_Up(int selectedCharacterAfter){

}


//先Q再E再A
int Q_E_Buzhou = 0;
DWORD change_Q_E_Time = 0;//切换到这个角色的时间
DWORD QE_buzhou1_Time = 0;
DWORD QE_buzhou3_Time = 0;
DWORD QE_buzhou5_Time = 0;
void Q_E_Down(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		selectedCharacterBefore = selectedCharacterAfter;
		change_Q_E_Time = timeGetTime();
	}
	Q_E_Buzhou = 1;
}

void Q_E_Hold(int selectedCharacterAfter){
	//等待切换硬直时间
	if(nowTime - change_Q_E_Time < changeDelay){
		return;
	}

	switch(Q_E_Buzhou){
	case 1:
		keybd_event(Q_KeyVirtualCode, Q_KeyScanCode, 0, 0);
		keybd_event(Q_KeyVirtualCode, Q_KeyScanCode, KEYEVENTF_KEYUP, 0);
		QE_buzhou1_Time = nowTime;
		Q_E_Buzhou = 2;
		break;

	case 2:
		if(nowTime - QE_buzhou1_Time >= 100){
			Q_E_Buzhou = 3;
		}
		break;

	case 3:
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);
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
		if(nowTime - QE_buzhou5_Time >= 50){
			Q_E_Buzhou = 1;
		}
		break;
	}
}

void Q_E_Up(int selectedCharacterAfter){

}


int E_Q_Buzhou = 1;
DWORD change_E_Q_Time = 0;//切换到这个角色的时间
DWORD EQ_buzhou1_Time = 0;
DWORD EQ_buzhou3_Time = 0;
DWORD EQ_buzhou5_Time = 0;
void E_Q_Down(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		selectedCharacterBefore = selectedCharacterAfter;
		change_E_Q_Time = timeGetTime();
	}
	E_Q_Buzhou = 1;
}

void E_Q_Hold(int selectedCharacterAfter){
	//等待切换硬直时间
	if(nowTime - change_E_Q_Time < changeDelay){
		return;
	}

	switch(E_Q_Buzhou){
	case 1:
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);
		EQ_buzhou1_Time = nowTime;
		E_Q_Buzhou = 2;
		break;

	case 2:
		if(nowTime - EQ_buzhou1_Time >= 100){
			E_Q_Buzhou = 3;
		}
		break;

	case 3:
		keybd_event(Q_KeyVirtualCode, Q_KeyScanCode, 0, 0);
		keybd_event(Q_KeyVirtualCode, Q_KeyScanCode, KEYEVENTF_KEYUP, 0);
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

void E_Q_Up(int selectedCharacterAfter){

}


//可莉，有E用E，A第一下+重击
int keliBuzhou = 1;
DWORD changeKeliTime = 0;//切换到这个角色的时间
DWORD keli_E_Time = 0;
DWORD keliFirst_A_Time = 0;
DWORD keliSecond_A_Time = 0;
DWORD keliBuzhou2_Time = 0;
DWORD keliBuzhou5_Time = 0;
DWORD keliBuzhou6_Time = 0;
void keliDown(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		selectedCharacterBefore = selectedCharacterAfter;
		changeKeliTime = timeGetTime();
	}
	keliBuzhou = 1;
}

void keliHold(int selectedCharacterAfter){
	//等待切换硬直时间
	if(nowTime - changeKeliTime < changeDelay){
		return;
	}

	switch(keliBuzhou){
	case 1:
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);
		keli_E_Time = nowTime;
		keliBuzhou = 2;
		break;

	case 2:
		if(nowTime - keli_E_Time >= 100){
			keliBuzhou = 3;
		}
		break;

	case 3:
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, 0, 0);
		keybd_event(E_KeyVirtualCode, E_KeyScanCode, KEYEVENTF_KEYUP, 0);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		keliFirst_A_Time = nowTime;
		keliBuzhou = 4;
		break;

	case 4:
		if(nowTime - keliFirst_A_Time >= 200){
			keliBuzhou2_Time = nowTime;
			keliBuzhou = 5;
		}
		break;

	case 5:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		keliBuzhou5_Time = nowTime;
		keliBuzhou = 6;
		break;

	case 6:
		if(nowTime - keliBuzhou5_Time > 900){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
			keliBuzhou6_Time = nowTime;
			keliBuzhou = 7;
		}
		break;

	case 7:
		if(nowTime - keliBuzhou6_Time >= 100){
			keliBuzhou = 1;
		}
		break;
	}
}

void keliUp(int selectedCharacterAfter){
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
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


