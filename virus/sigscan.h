#pragma once
#include "stdafx.h"

//DWORD FindPattern(unsigned int startAddr, unsigned char pattern[]);
unsigned int findPattern(unsigned int startAddr, unsigned char pattern[]);
unsigned int isModuleLoaded(DWORD pid, const wchar_t* module);
