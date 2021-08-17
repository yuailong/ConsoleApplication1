#include <iostream>
#include <windows.h>


int main()
{
    // {10C99CC1-AED1-4817-A4CE-3E2D7204CCE8}
    static const GUID IID_YS =
    { 0x10c99cc1, 0xaed1, 0x4817, { 0xa4, 0xce, 0x3e, 0x2d, 0x72, 0x4, 0xcc, 0xe8 } };

    std::cout << "Hello World!\n";
}
