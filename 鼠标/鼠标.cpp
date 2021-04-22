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

#define 切换硬直时间 250


//当前角色
#define SelectedCharacter_Diluke 101		//迪卢克
#define SelectedCharacter_Keqing 102		//刻晴
#define SelectedCharacter_Qin 103			//琴
#define SelectedCharacter1_E_A 1001			//在1号位的，短按E的角色
#define SelectedCharacter2_E_A 1002			//在2号位的，短按E的角色
#define SelectedCharacter3_E_A 1003			//在3号位的，短按E的角色
#define SelectedCharacter4_E_A 1004			//在4号位的，短按E的角色
#define SelectedCharacter1_LongE 1101		///在1号位的，长按E的角色
#define SelectedCharacter2_LongE 1102		///在2号位的，长按E的角色
#define SelectedCharacter3_LongE 1103		///在3号位的，长按E的角色
#define SelectedCharacter4_LongE 1104		///在4号位的，长按E的角色


bool kaiguan = 1;
int selectedCharacterBefore = SelectedCharacter1_E_A;
int selectedCharacterAfter = SelectedCharacter1_E_A;
int team1[4] = { SelectedCharacter1_E_A, SelectedCharacter2_E_A, SelectedCharacter3_E_A, SelectedCharacter_Diluke };
int team2[4] = { SelectedCharacter1_E_A, SelectedCharacter_Qin, SelectedCharacter_Keqing, SelectedCharacter4_LongE };
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

void keyDown(int selectedCharacterAfter);
void keyHold(int selectedCharacterAfter);
void keyUp(int selectedCharacterAfter);

//刻晴
void keqingDown(int selectedCharacterAfter);//按下
void keqingHold(int selectedCharacterAfter);//按住
void keqingUp(int selectedCharacterAfter);//弹起

//琴
void qinDown(int selectedCharacterAfter);
void qinHold(int selectedCharacterAfter);
void qinUp(int selectedCharacterAfter);

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

void keyDown(int selectedCharacterAfter){
	switch(selectedCharacterAfter){
	case SelectedCharacter_Keqing:
		keqingDown(selectedCharacterAfter);
		break;

	case SelectedCharacter_Diluke:
		dilukeDown(selectedCharacterAfter);
		break;

	case SelectedCharacter_Qin:
		qinDown(selectedCharacterAfter);
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

	case SelectedCharacter_Qin:
		qinHold(selectedCharacterAfter);
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

	case SelectedCharacter_Qin:
		qinUp(selectedCharacterAfter);
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
	}
}





#define 刻晴步骤1_E 1
#define 刻晴步骤2_等待50毫秒 2
#define 刻晴步骤3_按下左键 3
#define 刻晴步骤4_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒 4
#define 刻晴步骤5_如果重击完毕则弹起鼠标跳到第7步_否则E 5
#define 刻晴步骤6_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒回到第5步 6
#define 刻晴步骤7_等待50毫秒回到第3步 7


#define 刻晴重击按住时间 400
#define 刻晴重击松开鼠标后等待时间 100

int keqingBuzhou = 刻晴步骤1_E;
DWORD changeKeqingTime = 0;//切换到刻晴的时间
DWORD keqing_E_Time = 0;
DWORD keqing_MouseDown_Time = 0;
DWORD keqing_MouseUp_Time = 0;

void keqingDown(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		changeKeqingTime = timeGetTime();
	}
	keqingBuzhou = 刻晴步骤1_E;
}

void keqingHold(int selectedCharacterAfter){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeKeqingTime < 切换硬直时间){
		return;
	}

	switch(keqingBuzhou){
	case 刻晴步骤1_E:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		keqing_E_Time = nowTime;
		keqingBuzhou = 刻晴步骤2_等待50毫秒;
		break;

	case 刻晴步骤2_等待50毫秒:
		if(nowTime - keqing_E_Time >= 50){
			keqingBuzhou = 刻晴步骤3_按下左键;
		}
		break;

	case 刻晴步骤3_按下左键:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		keqing_MouseDown_Time = nowTime;
		keqingBuzhou = 刻晴步骤4_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒;
		break;

	case 刻晴步骤4_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒:
		if(nowTime - keqing_MouseDown_Time >= 刻晴重击按住时间){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
			keqing_MouseUp_Time = nowTime;
			keqingBuzhou = 刻晴步骤7_等待50毫秒回到第3步;
		}
		else if(nowTime - keqing_MouseDown_Time > 50){
			keqingBuzhou = 刻晴步骤5_如果重击完毕则弹起鼠标跳到第7步_否则E;
		}
		break;

	case 刻晴步骤5_如果重击完毕则弹起鼠标跳到第7步_否则E:
		if(nowTime - keqing_MouseDown_Time >= 刻晴重击按住时间){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
			keqing_MouseUp_Time = nowTime;
			keqingBuzhou = 刻晴步骤7_等待50毫秒回到第3步;
		}
		else{
			keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
			keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
			keqing_E_Time = nowTime;
			keqingBuzhou = 刻晴步骤6_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒回到第5步;
		}
		break;

	case 刻晴步骤6_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒回到第5步:
		if(nowTime - keqing_MouseDown_Time >= 刻晴重击按住时间){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
			keqing_MouseUp_Time = nowTime;
			keqingBuzhou = 刻晴步骤7_等待50毫秒回到第3步;
		}
		else if(nowTime - keqing_E_Time >= 50){
			keqingBuzhou = 刻晴步骤5_如果重击完毕则弹起鼠标跳到第7步_否则E;
		}
		break;

	case 刻晴步骤7_等待50毫秒回到第3步:
		if(nowTime - keqing_MouseUp_Time >= 刻晴重击松开鼠标后等待时间){
			keqingBuzhou = 刻晴步骤3_按下左键;
		}
		break;
	}
}

void keqingUp(int selectedCharacterAfter){
	if(keqingBuzhou == 刻晴步骤4_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒 || keqingBuzhou == 刻晴步骤5_如果重击完毕则弹起鼠标跳到第7步_否则E || keqingBuzhou == 刻晴步骤6_如果重击完毕则弹起鼠标跳到第7步_否则等待50毫秒回到第5步){
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	}
}




#define 琴步骤1_按下鼠标 1
#define 琴步骤2_等待重击按住鼠标 2
#define 琴步骤3_弹起鼠标 3
#define 琴步骤4_等待100毫秒 4

DWORD changeQinTime = 0;
DWORD qinBuzhou = qinBuzhou = 琴步骤1_按下鼠标;;
DWORD qin_Buzhou1_Time = 0;
DWORD qin_Buzhou3_Time = 0;

void qinDown(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		changeQinTime = timeGetTime();
		qinBuzhou = 琴步骤1_按下鼠标;
	}
}

void qinHold(int selectedCharacterAfter){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeQinTime < 切换硬直时间){
		return;
	}

	switch(qinBuzhou){
	case 琴步骤1_按下鼠标:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		qin_Buzhou1_Time = nowTime;
		qinBuzhou = 琴步骤2_等待重击按住鼠标;
		break;

	case 琴步骤2_等待重击按住鼠标:
		if(nowTime - qin_Buzhou1_Time >= 400){
			qinBuzhou = 琴步骤3_弹起鼠标;
		}
		break;

	case 琴步骤3_弹起鼠标:
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
		qin_Buzhou3_Time = nowTime;
		qinBuzhou = 琴步骤4_等待100毫秒;
		break;

	case 琴步骤4_等待100毫秒:
		if(nowTime - qin_Buzhou3_Time >= 100){
			qinBuzhou = 琴步骤1_按下鼠标;
		}
		break;
	}
}

void qinUp(int selectedCharacterAfter){
	DWORD nowTime = timeGetTime();
	while(nowTime - qin_Buzhou1_Time < 400){
		nowTime = timeGetTime();
	}
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
	qin_Buzhou3_Time = nowTime;
}



DWORD longE_buzhou = 0;
DWORD changeLong_E_Time = 0;//切换到长按E的角色的时间
DWORD beginLong_E_Time = 0;//按下E键的时间
void longE_Down(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		longE_buzhou = 0;//刚切换到这个角色时从第0步开始
		changeLong_E_Time = timeGetTime();
	}
}

void longE_Hold(int selectedCharacterAfter){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeLong_E_Time < 切换硬直时间){
		return;
	}

	switch(longE_buzhou){
	case 0:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		beginLong_E_Time = nowTime;
		while(nowTime - beginLong_E_Time < 400){
			nowTime = timeGetTime();
		}
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		while(nowTime - beginLong_E_Time < 500){
			nowTime = timeGetTime();
		}
		longE_buzhou = 0;
		break;
	}
}

void longE_Up(int selectedCharacterAfter){

}


#define 步骤_迪卢克第一次普攻 1
#define 步骤_迪卢克等待50毫秒 2
#define 步骤_迪卢克E或者A 3

int dilukeBuzhou = 步骤_迪卢克E或者A;
DWORD changeDilukeTime = 0;//切换到迪卢克的时间
DWORD diluke_E_or_A_Time = 0;//迪卢克上一次E或者A的时间
DWORD diluke_E_time = 0;//迪卢克上一次E的时间

void dilukeDown(int selectedCharacterAfter){
	if(selectedCharacterBefore != selectedCharacterAfter){
		changeDilukeTime = timeGetTime();
		diluke_E_or_A_Time = changeDilukeTime;
	}
}

void dilukeHold(int selectedCharacterAfter){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeDilukeTime < 切换硬直时间){
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
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - change_E_A_Time < 切换硬直时间){
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

void E_A_Up(int selectedCharacterAfter){

}
