#include "stdafx.h"

void detour(void* targetAddr, int overrideLen, void* detourFunc)
{
	VirtualProtect(targetAddr, overrideLen, PAGE_EXECUTE_READWRITE, 0);
	memset(targetAddr, 0x90, overrideLen);

	// relative detoured function address
	unsigned int jmpAddr = (unsigned int)detourFunc - ((unsigned int)targetAddr + 5);

	// jmp [jmpAddr]
	unsigned char ass[5];
	ass[0] = 0xE9;
	memcpy(&ass[1], &jmpAddr, 4);
	memcpy(targetAddr, ass, 5);

}