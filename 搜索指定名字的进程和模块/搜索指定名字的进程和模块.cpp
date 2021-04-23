#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

//根据进程名，获取进程PID，找不到就返回0
DWORD getProcessID(LPCTSTR lpProcessName){
	DWORD PID = 0;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapShot == INVALID_HANDLE_VALUE){
		printf("获得进程快照失败,Last Error:%d", GetLastError());
		return 0;
	}

	PROCESSENTRY32 pe32;//进程入口对象
	pe32.dwSize = sizeof(PROCESSENTRY32);//填充进程入口对象大小
	Process32First(hSnapShot, &pe32);
	//遍历进程列表
	do{
		if(lstrcmp(pe32.szExeFile, lpProcessName) == 0){
			PID = pe32.th32ProcessID;
			break;
		}
	} while(Process32Next(hSnapShot, &pe32));

	CloseHandle(hSnapShot);
	return PID;
}

//根据PID和模块名，获取模块句柄，找不到就返回NULL
HMODULE myGetHModuleHandle(DWORD PID, LPCTSTR lpModuleName){
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	if(hSnapShot == INVALID_HANDLE_VALUE){
		printf("获得模块快照失败,Last Error:%d\n", GetLastError());
		return NULL;
	}

	MODULEENTRY32 mo32;//模块入口对象
	ZeroMemory(&mo32, sizeof(MODULEENTRY32));
	mo32.dwSize = sizeof(MODULEENTRY32);//填充进程入口对象大小
	Module32First(hSnapShot, &mo32);
	//遍历模块列表
	do{
		if(lstrcmp(mo32.szModule, lpModuleName) == 0){
			CloseHandle(hSnapShot);
			return mo32.hModule;
			break;
		}
	} while(Module32Next(hSnapShot, &mo32));

	CloseHandle(hSnapShot);
	return NULL;//返回 
}

int main(){
	//进程名
	LPCTSTR str = L"YuanShen.exe";
	//获取进程的PID
	DWORD PID = getProcessID(str);
	printf("PID:%d\n", PID);
	//获取一个进程中的指定模块名字的模块句柄
	HMODULE hModule = myGetHModuleHandle(PID, L"YuanShen.exe");
	printf("HMODULE:%x\n", (DWORD)hModule);
	return 0;
}