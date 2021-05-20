#pragma once
#include <windows.h>
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
#define SelectedCharacter_Youla 7001        //优菈

extern DWORD changeDelay; //切换硬直时间
extern int selectedCharacterCodeBefore;
extern int selectedCharacterCodeAfter;
extern int(*pSelectedTeam)[4];
extern DWORD nowTime;