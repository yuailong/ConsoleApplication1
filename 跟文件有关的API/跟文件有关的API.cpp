#include <stdio.h> 
#include <windows.h> 
#include <locale.h> 
int main(){
    setlocale(LC_ALL, "");
    TCHAR modulePath[256];
    GetModuleFileName(NULL, modulePath, 256);//得到当前模块的路径 
    TCHAR projectPath[1000];
    GetCurrentDirectory(1000, projectPath);//得到当前项目路径 
    wprintf(L"当前模块路径：%s\n当前项目路径：%s\n", modulePath, projectPath);
    return 0;
}