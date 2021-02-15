#include <stdio.h>   
#include <windows.h>

//创建挂起的进程
BOOL  CreateSuspendedProcess(PTCHAR lpApplicationName, PTCHAR szCommandLine, STARTUPINFO* si, PROCESS_INFORMATION* pi){
	BOOL succeed = CreateProcess(
		lpApplicationName, //对象名称，文件路径   
		szCommandLine, //命令行参数    
		NULL,  //进程安全描述符，NULL：进程句柄不允许被继承     
		NULL,  //线程安全描述符，NULL：线程句柄不允许被继承    
		FALSE, //TRUE：继承句柄表里允许被继承的句柄  FALSE：不继承句柄表      
		CREATE_SUSPENDED,    //没有创建标志      
		NULL, //使用父进程环境变量    
		NULL, //使用父进程目录作为当前目录，可以自己设置目录   
		si, //IN参数，STARTUPINFO结构体的详细信息   
		pi //OUT参数，PROCESS_INFORMATION结构体进程信息  
	);

	if(!succeed){
		printf("CreateChildprocess error :%x", GetLastError());
		return 0;
	}

	//在这里可以对进程做些事情，例如提前注入dll

	system("pause");
	//恢复进程
	succeed = ResumeThread(pi->hThread);
	if(succeed != -1){
		printf("成功恢复进程\n");
	}

	return succeed;
}

int  main(){
	//打开32位笔记本程序
	TCHAR str[] = TEXT("C:/Windows/SysWOW64/notepad.exe");
	TCHAR  commandLine[] = TEXT("");

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	//挂起形式开启进程
	bool succeed = CreateSuspendedProcess(str, commandLine, &si, &pi);
	if(succeed){
		printf("succeed");
	}

	//释放进程句柄、线程句柄。释放了也不会马上销毁，只有线程关闭了才会销毁线程句柄，线程关闭了才会关闭进程，才会销毁进程句柄   
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}