#include <iostream>
#include <Windows.h>

//unsigned char sig[] = "\xDE\xC9\xDD\x1D\x00\x00\x00\x00\xDD\x05\x00\x00\x00\x00\xDD\x5D\xEC";

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    LoadLibrary(L"virus.dll");
    std::cout << "Hello World!\n";
    return MessageBox(NULL, L"hello, world", L"caption", 0);
}