#include <iostream>
#include "A.h"
#pragma comment(lib, "生成静态库.lib")

int main(){
	int a = add(4, 4);
	int b = sub(5, 1);
	printf("test: a=%d, b=%d\n", a, b);
	return 0;
}