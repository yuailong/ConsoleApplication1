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
#define SelectedCharacter_E_A 0
#define SelectedCharacter_Diluke 1
#define SelectedCharacter_Keqing 2

bool kaiguan = 1;
int selectedTeam = 1;//0代表第一队，1代表第二队...
int selectedCharacter = SelectedCharacter_E_A;

SHORT kaiguanKeyStateBefore = 0;
SHORT key1StateBefore = 0;
SHORT key2StateBefore = 0;
SHORT key3StateBefore = 0;
SHORT key4StateBefore = 0;
SHORT leftMouseStateBefore = 0;
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
SHORT leftMouseStateAfter = 0;
SHORT team1KeyStateAfter = 0;
SHORT team2KeyStateAfter = 0;
SHORT team3KeyStateAfter = 0;
SHORT team4KeyStateAfter = 0;
SHORT mouseSideKey1StateAfter = 0;

DWORD beginTimeLongE = 0;
DWORD E_A_beginTime = 0;

void KeqingDown();//按下
void KeqingHold();//按住
void KeqingUp();//弹起

void longE_Down();//按下
void longE_Hold();//按住
void longE_Up();//弹起

void dilukeDown();//按下
void dilukeHold();//按住
void dilukeUp();//弹起

void E_A_Down();//按下
void E_A_Hold();//按住
void E_A_Up();//弹起

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
		mouseSideKey1StateAfter = GetAsyncKeyState(VK_XBUTTON1);

		if(team1KeyStateBefore && !team1KeyStateAfter){
			selectedTeam = 0;
		}
		else if(team2KeyStateBefore && !team2KeyStateAfter){
			selectedTeam = 1;
		}
		else if(team3KeyStateBefore && !team3KeyStateAfter){
			selectedTeam = 2;
		}
		else if(team4KeyStateBefore && !team4KeyStateAfter){
			selectedTeam = 3;
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
			if(!mouseSideKey2StateBefore && mouseSideKey1StateAfter){
				KeqingDown();
			}
			else if(mouseSideKey2StateBefore && mouseSideKey1StateAfter){
				KeqingHold();
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey1StateAfter){
				KeqingUp();
			}
			break;

		case SelectedCharacter_Diluke:
			if(!mouseSideKey2StateBefore && mouseSideKey1StateAfter){
				dilukeDown();
			}
			else if(mouseSideKey2StateBefore && mouseSideKey1StateAfter){
				dilukeHold();
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey1StateAfter){
				dilukeUp();
			}
			break;

		case SelectedCharacter_E_A:
			if(!mouseSideKey2StateBefore && mouseSideKey1StateAfter){
				E_A_Down();
			}
			else if(mouseSideKey2StateBefore && mouseSideKey1StateAfter){
				E_A_Hold();
			}
			else if(mouseSideKey2StateBefore && !mouseSideKey1StateAfter){
				E_A_Up();
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
		mouseSideKey2StateBefore = mouseSideKey1StateAfter;
	}
}

void funcForTeam1(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down();
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold();
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up();
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down();
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold();
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up();
	}

	if(!key3StateBefore && key3StateAfter){
		E_A_Down();
	}
	else if(key3StateBefore && key3StateAfter){
		E_A_Hold();
	}
	else if(key3StateBefore && !key3StateAfter){
		E_A_Up();
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

	if(!leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && !leftMouseStateAfter){

	}
}

void funcForTeam2(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down();
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold();
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up();
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down();
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold();
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up();
	}

	if(!key3StateBefore && key3StateAfter){
		KeqingDown();
	}
	else if(key3StateBefore && key3StateAfter){
		KeqingHold();
	}
	else if(key3StateBefore && !key3StateAfter){
		KeqingUp();
	}

	if(!key4StateBefore && key4StateAfter){
		KeqingDown();
	}
	else if(key4StateBefore && key4StateAfter){
		KeqingHold();
	}
	else if(key4StateBefore && !key4StateAfter){
		KeqingUp();
	}

	if(!leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && !leftMouseStateAfter){

	}
}

void funcForTeam3(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down();
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold();
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up();
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down();
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold();
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up();
	}

	if(!key3StateBefore && key3StateAfter){
		E_A_Down();
	}
	else if(key3StateBefore && key3StateAfter){
		E_A_Hold();
	}
	else if(key3StateBefore && !key3StateAfter){
		E_A_Up();
	}

	if(!key4StateBefore && key4StateAfter){
		E_A_Down();
	}
	else if(key4StateBefore && key4StateAfter){
		E_A_Hold();
	}
	else if(key4StateBefore && !key4StateAfter){
		E_A_Up();
	}

	if(!leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && !leftMouseStateAfter){

	}
}

void funcForTeam4(){
	if(!key1StateBefore && key1StateAfter){
		E_A_Down();
	}
	else if(key1StateBefore && key1StateAfter){
		E_A_Hold();
	}
	else if(key1StateBefore && !key1StateAfter){
		E_A_Up();
	}

	if(!key2StateBefore && key2StateAfter){
		E_A_Down();
	}
	else if(key2StateBefore && key2StateAfter){
		E_A_Hold();
	}
	else if(key2StateBefore && !key2StateAfter){
		E_A_Up();
	}

	if(!key3StateBefore && key3StateAfter){
		E_A_Down();
	}
	else if(key3StateBefore && key3StateAfter){
		E_A_Hold();
	}
	else if(key3StateBefore && !key3StateAfter){
		E_A_Up();
	}

	if(!key4StateBefore && key4StateAfter){
		E_A_Down();
	}
	else if(key4StateBefore && key4StateAfter){
		E_A_Hold();
	}
	else if(key4StateBefore && !key4StateAfter){
		E_A_Up();
	}

	if(!leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && leftMouseStateAfter){

	}
	else if(leftMouseStateBefore && !leftMouseStateAfter){

	}
}



#define 步骤_刻晴一段E 1
#define 步骤_刻晴一段E等待后摇 2
#define 步骤_刻晴二段E 3
#define 步骤_刻晴二段E等待后摇 4
#define 步骤_刻晴重击按下鼠标 5
#define 步骤_刻晴重击等待按住鼠标 6
#define 步骤_刻晴重击弹起鼠标 7
#define 步骤_刻晴重击等待后摇 8


#define 刻晴重击按住时间 400
#define 刻晴重击松开鼠标后等待时间 100

int keqingBuzhou = 步骤_刻晴一段E;
DWORD changeKeqingTime = 0;
DWORD keqingFirst_E_Time = 0;
DWORD keqingSecond_E_Time = 0;
DWORD keqing_Down_Time = 0;
DWORD keqing_Up_Time = 0;

void KeqingDown(){
	if(selectedCharacter != SelectedCharacter_Keqing){
		selectedCharacter = SelectedCharacter_Keqing;
		keqingBuzhou = 步骤_刻晴一段E;
		changeKeqingTime = timeGetTime();
	}
}

void KeqingHold(){
	DWORD nowTime = timeGetTime();

	//等待切换硬直时间
	if(nowTime - changeKeqingTime < 250){
		return;
	}

	switch(keqingBuzhou){
	case 步骤_刻晴一段E:
		if(nowTime - keqingFirst_E_Time >= 7500){//E技能冷却完毕
			keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
			keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
			keqingBuzhou = 步骤_刻晴一段E等待后摇;
			keqingFirst_E_Time = nowTime;
			printf("刻晴一段E\n");
		}
		else{
			keqingBuzhou = 步骤_刻晴重击按下鼠标;
			printf("刻晴E冷却\n");
		}
		break;

	case 步骤_刻晴一段E等待后摇:
		if(nowTime - keqingFirst_E_Time > 700){
			keqingBuzhou = 步骤_刻晴二段E;
		}
		break;

	case 步骤_刻晴二段E:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		keqingBuzhou = 步骤_刻晴二段E等待后摇;
		keqingSecond_E_Time = nowTime;
		printf("刻晴二段E\n");
		break;

	case 步骤_刻晴二段E等待后摇:
		if(nowTime - keqingSecond_E_Time > 300){
			keqingBuzhou = 步骤_刻晴重击按下鼠标;
		}
		break;

	case 步骤_刻晴重击按下鼠标:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		keqingBuzhou = 步骤_刻晴重击等待按住鼠标;
		keqing_Down_Time = nowTime;
		printf("刻晴重击按下鼠标\n");
		break;

	case 步骤_刻晴重击等待按住鼠标:
		if(nowTime - keqing_Down_Time >= 刻晴重击按住时间){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
			keqingBuzhou = 步骤_刻晴重击等待后摇;
			keqing_Up_Time = nowTime;
			printf("刻晴松开鼠标\n");
		}
		break;

	case 步骤_刻晴重击等待后摇:
		if(nowTime - keqingFirst_E_Time >= 7500){
			if(nowTime - keqing_Up_Time >= 400){
				keqingBuzhou = 步骤_刻晴一段E;
			}
		}
		else{
			if(nowTime - keqing_Up_Time >= 刻晴重击松开鼠标后等待时间){
				keqingBuzhou = 步骤_刻晴重击按下鼠标;
			}
		}
		
		break;
	}
}

void KeqingUp(){
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//弹起鼠标左键
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


#define 步骤_迪卢克第一次普攻 2
#define 步骤_迪卢克等待第一次普攻后摇时间 3
#define 步骤_迪卢克第一次E 4
#define 步骤_迪卢克等待第一次E后摇时间 5
#define 步骤_迪卢克第二次普攻 6
#define 步骤_迪卢克等待第二次普攻后摇时间 7
#define 步骤_迪卢克第二次E 8
#define 步骤_迪卢克等待第二次E后摇时间 9
#define 步骤_迪卢克第三次普攻 10
#define 步骤_迪卢克等待第三次普攻后摇时间 11
#define 步骤_迪卢克第三次E 12
#define 步骤_迪卢克等待第三次E后摇时间 13
#define 步骤_迪卢克普攻 14
#define 步骤_迪卢克等待普攻后摇时间 15

int dilukeBuzhou = 步骤_迪卢克第一次普攻;
DWORD changeDilukeTime = 0;//切换到迪卢克的时间
DWORD dilukeFirst_A_Time = 0;//迪卢克第一次A的时间
DWORD dilukeFirst_E_time = 0;//迪卢克第一次E的时间
DWORD dilukeSecond_A_Time = 0;//迪卢克第二次A的时间
DWORD dilukeSecond_E_Time = 0;//迪卢克第二次E的时间
DWORD dilukeThird_A_Time = 0;//迪卢克第三次A的时间
DWORD dilukeThird_E_time = 0;//迪卢克第三次E的时间
DWORD diluke_A_Time = 0;//迪卢克A的时间

void dilukeDown(){
	if(selectedCharacter != SelectedCharacter_Diluke){
		selectedCharacter = SelectedCharacter_Diluke;
		changeDilukeTime = timeGetTime();
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
		dilukeBuzhou = 步骤_迪卢克等待第一次普攻后摇时间;
		dilukeFirst_A_Time = nowTime;
		break;

	case 步骤_迪卢克等待第一次普攻后摇时间:
		if(nowTime - dilukeFirst_A_Time >= 450){
			dilukeBuzhou = 步骤_迪卢克第一次E;
		}
		break;

	case 步骤_迪卢克第一次E:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		dilukeBuzhou = 步骤_迪卢克等待第一次E后摇时间;
		dilukeFirst_E_time = nowTime;
		break;

	case 步骤_迪卢克等待第一次E后摇时间:
		if(nowTime - dilukeFirst_E_time >= 3900){//超过3900毫秒秒不用第二次E就进入冷却
			dilukeBuzhou = 步骤_迪卢克普攻;
		}
		else if(nowTime - dilukeFirst_E_time >= 560){//等待第一次E后摇
			dilukeBuzhou = 步骤_迪卢克第二次普攻;
		}
		break;

	case 步骤_迪卢克第二次普攻:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		dilukeBuzhou = 步骤_迪卢克等待第二次普攻后摇时间;
		dilukeSecond_A_Time = nowTime;
		break;

	case 步骤_迪卢克等待第二次普攻后摇时间:
		if(nowTime - dilukeFirst_E_time >= 3900){//超过3900毫秒秒不用第二次E就进入冷却
			dilukeBuzhou = 步骤_迪卢克普攻;
		}
		else if(nowTime - dilukeSecond_A_Time >= 450){//等待第二次A后摇
			dilukeBuzhou = 步骤_迪卢克第二次E;
		}
		break;

	case 步骤_迪卢克第二次E:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		dilukeBuzhou = 步骤_迪卢克等待第二次E后摇时间;
		dilukeSecond_E_Time = nowTime;
		break;

	case 步骤_迪卢克等待第二次E后摇时间:
		if(nowTime - dilukeSecond_E_Time >= 3900){//超过3900毫秒秒不用第三次E就进入冷却
			dilukeBuzhou = 步骤_迪卢克普攻;
		}
		else if(nowTime - dilukeSecond_E_Time >= 760){//等待第二次E后摇
			dilukeBuzhou = 步骤_迪卢克第三次普攻;
		}
		break;

	case 步骤_迪卢克第三次普攻:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		dilukeBuzhou = 步骤_迪卢克等待第三次普攻后摇时间;
		dilukeThird_A_Time = nowTime;
		break;

	case 步骤_迪卢克等待第三次普攻后摇时间:
		if(nowTime - dilukeSecond_E_Time >= 3900){//超过3900毫秒秒不用第三次E就进入冷却
			dilukeBuzhou = 步骤_迪卢克普攻;
		}
		else if(nowTime - dilukeThird_A_Time >= 450){//等待第三次A后摇
			dilukeBuzhou = 步骤_迪卢克第三次E;
		}
		break;

	case 步骤_迪卢克第三次E:
		keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
		keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
		dilukeBuzhou = 步骤_迪卢克等待第三次E后摇时间;
		changeDilukeTime = nowTime;
		break;

	case 步骤_迪卢克等待第三次E后摇时间:
		if(nowTime - dilukeThird_E_time >= 800){
			dilukeBuzhou = 步骤_迪卢克普攻;
		}
		break;

	case 步骤_迪卢克普攻:
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
		if(nowTime - dilukeFirst_E_time >= 10000){//从第一次用E起，超过10秒的话，E冷却完毕
			dilukeBuzhou = 步骤_迪卢克等待第一次普攻后摇时间;
		}
		else{
			dilukeBuzhou = 步骤_迪卢克等待普攻后摇时间;
		}
		diluke_A_Time = nowTime;
		break;

	case 步骤_迪卢克等待普攻后摇时间:
		if(nowTime - dilukeFirst_E_time >= 10000){//从第一次用E起，超过10秒的话，E冷却完毕
			dilukeBuzhou = 步骤_迪卢克第一次普攻;
		}
		else if(nowTime - diluke_A_Time >= 100){
			dilukeBuzhou = 步骤_迪卢克普攻;
		}

		break;
	}
}

void dilukeUp(){

}

int E_A_Buzhou = 0;
void E_A_Down(){
	selectedCharacter = SelectedCharacter_E_A;
	E_A_Buzhou = 0;
	E_A_beginTime = timeGetTime();
}
void E_A_Hold(){
	DWORD nowTime = timeGetTime();
	DWORD time = nowTime - E_A_beginTime;

	switch(E_A_Buzhou){
	case 0:
		if(time >= 20){
			keybd_event(E键虚拟码, E键扫描码, 0, 0);//按下E键
			keybd_event(E键虚拟码, E键扫描码, KEYEVENTF_KEYUP, 0);//弹起E键
			E_A_Buzhou = 1;
			E_A_beginTime = nowTime;
		}
		break;
	case 1:
		if(time >= 20){
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//按下鼠标左键
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开鼠标左键
			E_A_Buzhou = 0;
			E_A_beginTime = nowTime;
		}
		break;
	}
}

void E_A_Up(){

}
