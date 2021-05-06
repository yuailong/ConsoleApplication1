#include "YSHotKey.h"

YSHotKey::YSHotKey(const char* name,
				   unsigned char virtualCode,
				   unsigned char scanCode,
				   void(*hotKeyDownCallback)(),
				   void(*hotKeyHoldCallback)(),
				   void(*hotKeyUpCallback)())
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
		hotKeyDownCallback();
	}
	else if(stateBefore && stateAfter && hotKeyHoldCallback){
		hotKeyHoldCallback();
	}
	else if(stateBefore && !stateAfter && hotKeyUpCallback){
		hotKeyUpCallback();
	}
	stateBefore = stateAfter;
}
