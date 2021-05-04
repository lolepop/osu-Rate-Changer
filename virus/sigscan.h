#pragma once
#include "stdafx.h"

//DWORD FindPattern(unsigned int startAddr, unsigned char pattern[]);
unsigned int findPattern(unsigned int startAddr, unsigned char pattern[], char mask[]);
unsigned int findPatternDynamic(unsigned char pattern[], char mask[], unsigned int currAddress, unsigned int maxAddress);
MODULEENTRY32 getModuleFull(DWORD pid, const wchar_t* module);
unsigned int getModule(DWORD pid, const wchar_t* module);
