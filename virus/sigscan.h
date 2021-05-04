#pragma once
#include "stdafx.h"

//DWORD FindPattern(unsigned int startAddr, unsigned char pattern[]);
unsigned int findPattern(MODULEENTRY32 module, unsigned char pattern[], char mask[]);
unsigned int findPatternDynamic(unsigned char pattern[], char mask[], unsigned int currAddress = 0, unsigned int maxAddress = UINT_MAX);
bool getModuleFull(DWORD pid, const wchar_t* module, MODULEENTRY32* out);
unsigned int getModule(DWORD pid, const wchar_t* module);
