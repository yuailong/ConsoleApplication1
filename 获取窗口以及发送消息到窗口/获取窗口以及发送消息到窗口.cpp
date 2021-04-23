// 获取窗口以及发送消息到窗口.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>


int count = 0;
SHORT walkKeyStateBefore = 0;
SHORT walkKeyStateAfter = 0;

bool isWalk = 0;

int main(){


	HWND hWindow = FindWindowA("UnityWndClass", "原神");
	HWND hWindowSelf = FindWindowA(NULL,"D:\\Code\\ConsoleApplication1\\x64\\Debug\\获取窗口以及发送消息到窗口.exe");
	std::cout << "原神窗口句柄：" << hWindow << std::endl;
	std::cout << "Hello World!\n";

	while(true){
		count++;

		/*
		if(GetAsyncKeyState(0x57)){nn
			printf("W键的扫描码：0x%X\n", MapVirtualKeyA(0x57, 0));
		}
		*/

		walkKeyStateAfter = GetAsyncKeyState(0x4E);//N键

		if(walkKeyStateBefore && !walkKeyStateAfter){//弹起N键
			isWalk = !isWalk;
					
			if(isWalk){//发送按住W
				SwitchToThisWindow(hWindow, false);
				/*
				if(SetForegroundWindow(hWindow)){
					std::cout << "激活原神窗口成功" << std::endl;
				}
				else{
					std::cout << "激活原神窗口失败, error: " << GetLastError() << std::endl;
				}
				*/

				__int64 param = 0x00110001;
				if(PostMessageA(hWindow, WM_KEYDOWN, 0x57, param)){
					std::cout << "按下W键发送成功" << std::endl;
					SwitchToThisWindow(hWindowSelf, false);
					/*
					if(SetForegroundWindow(hWindowSelf)){
						std::cout << "激活自己窗口成功" << std::endl;
					}
					else{
						std::cout << "激活自己窗口失败, error: " << GetLastError() << std::endl;
					}
					*/
				}
				else{
					std::cout << "按下W键发送失败，error: " << GetLastError() << std::endl;
				}
			}
			else{//发送弹起W
				__int64 param = 0xC0110001;
				if(PostMessageA(hWindow, WM_KEYUP, 0x57, param)){
					std::cout << "弹起W键发送成功" << std::endl;
				}
				else{
					std::cout << "弹起W键发送失败，error: " << GetLastError() << std::endl;
				}
			}
		}

		walkKeyStateBefore = walkKeyStateAfter;
	}

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
