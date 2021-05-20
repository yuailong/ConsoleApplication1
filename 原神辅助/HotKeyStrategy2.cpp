#include "HotKeyStrategy2.h"
#include "main.h"
#include "YSHotKey.h"
#include "YSDiluke.h"
#include "YSKeqing.h"
#include "YSKeli.h"
#include "YSLongE.h"
#include "YS_E_A.h"
#include "YS_Q_E.h"
#include "YS_E_Q.h"



void keyDownCallback2(unsigned char virtualCode){
	switch(virtualCode){
	case VirtualCode_1:
		selectedCharacterCodeAfter = (*pSelectedTeam)[0];
		break;

	case VirtualCode_2:
		selectedCharacterCodeAfter = (*pSelectedTeam)[1];
		break;

	case VirtualCode_3:
		selectedCharacterCodeAfter = (*pSelectedTeam)[2];
		break;

	case VirtualCode_4:
		selectedCharacterCodeAfter = (*pSelectedTeam)[3];
		break;
	}

	switch(selectedCharacterCodeAfter){
	case SelectedCharacter_Keqing:
		keqingDown(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Diluke:
		dilukeDown(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Down(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_LongE:
	case SelectedCharacter2_LongE:
	case SelectedCharacter3_LongE:
	case SelectedCharacter4_LongE:
		longE_Down(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_Q_E:
	case SelectedCharacter2_Q_E:
	case SelectedCharacter3_Q_E:
	case SelectedCharacter4_Q_E:
		Q_E_Down(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_E_Q:
	case SelectedCharacter2_E_Q:
	case SelectedCharacter3_E_Q:
	case SelectedCharacter4_E_Q:
		E_Q_Down(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Keli:
		keliDown(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Youla:
		longE_Down(selectedCharacterCodeAfter);
		break;
	}

	selectedCharacterCodeBefore = selectedCharacterCodeAfter;
}

void keyHoldCallback2(unsigned char virtualCode){
	switch(selectedCharacterCodeAfter){
	case SelectedCharacter_Keqing:
		keqingHold(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Diluke:
		dilukeHold(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Hold(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_LongE:
	case SelectedCharacter2_LongE:
	case SelectedCharacter3_LongE:
	case SelectedCharacter4_LongE:
		longE_Hold(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_Q_E:
	case SelectedCharacter2_Q_E:
	case SelectedCharacter3_Q_E:
	case SelectedCharacter4_Q_E:
		Q_E_Hold(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_E_Q:
	case SelectedCharacter2_E_Q:
	case SelectedCharacter3_E_Q:
	case SelectedCharacter4_E_Q:
		E_Q_Hold(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Keli:
		keliHold(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Youla:
		longE_Hold(selectedCharacterCodeAfter);
		break;
	}
}

void keyUpCallback2(unsigned char virtualCode){
	switch(selectedCharacterCodeAfter){
	case SelectedCharacter_Keqing:
		keqingUp(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Diluke:
		dilukeUp(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_E_A:
	case SelectedCharacter2_E_A:
	case SelectedCharacter3_E_A:
	case SelectedCharacter4_E_A:
		E_A_Up(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_LongE:
	case SelectedCharacter2_LongE:
	case SelectedCharacter3_LongE:
	case SelectedCharacter4_LongE:
		longE_Up(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_Q_E:
	case SelectedCharacter2_Q_E:
	case SelectedCharacter3_Q_E:
	case SelectedCharacter4_Q_E:
		Q_E_Up(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter1_E_Q:
	case SelectedCharacter2_E_Q:
	case SelectedCharacter3_E_Q:
	case SelectedCharacter4_E_Q:
		E_Q_Up(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Keli:
		keliUp(selectedCharacterCodeAfter);
		break;

	case SelectedCharacter_Youla:
		longE_Up(selectedCharacterCodeAfter);
		break;
	}
}