#include "YSHotKey.h"

YSHotKey::YSHotKey(const char* name,
				   unsigned char virtualCode,
				   unsigned char scanCode,
				   void(*hotKeyDownCallback)(unsigned char virtualCode),
				   void(*hotKeyHoldCallback)(unsigned char virtualCode),
				   void(*hotKeyUpCallback)(unsigned char virtualCode))
	: name{ name },
	virtualCode{ virtualCode },
	scanCode{ scanCode },
	hotKeyDownCallback{ hotKeyDownCallback },
	hotKeyHoldCallback{ hotKeyHoldCallback },
	hotKeyUpCallback{ hotKeyUpCallback }{

}

void YSHotKey::getHotKeyStateAndCallback(){
	stateAfter = GetAsyncKeyState(virtualCode);
	if(!stateBefore && stateAfter && hotKeyDownCallback){
		hotKeyDownCallback(virtualCode);
	}
	else if(stateBefore && stateAfter && hotKeyHoldCallback){
		hotKeyHoldCallback(virtualCode);
	}
	else if(stateBefore && !stateAfter && hotKeyUpCallback){
		hotKeyUpCallback(virtualCode);
	}
	stateBefore = stateAfter;
}
