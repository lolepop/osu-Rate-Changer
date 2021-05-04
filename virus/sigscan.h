#pragma once
#include "stdafx.h"

//DWORD FindPattern(unsigned int startAddr, unsigned char pattern[]);
unsigned int findPattern(unsigned int startAddr, unsigned char pattern[], char mask[]);
unsigned int findPatternDynamic(unsigned char pattern[], char mask[], unsigned int currAddress = 0, unsigned int maxAddress = UINT_MAX);
MODULEENTRY32 getModuleFull(DWORD pid, const wchar_t* module);
unsigned int getModule(DWORD pid, const wchar_t* module);
