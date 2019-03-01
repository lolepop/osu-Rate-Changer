#pragma once

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>

extern "C"
{
	__declspec(dllexport) bool inject(DWORD pid, char* dll);
	__declspec(dllexport) unsigned int getProcessId(wchar_t* procName);
	__declspec(dllexport) bool createSlot(int attempt = 0);
	__declspec(dllexport) unsigned int readSlot();

}