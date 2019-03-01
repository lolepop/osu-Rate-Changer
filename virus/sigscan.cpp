#include "stdafx.h"

unsigned int findPattern(unsigned int startAddr, unsigned char pattern[])
{
	unsigned int patternSize = sizeof(pattern);

	for (unsigned int i = 0; i < UINT_MAX; i++)
	{
		if (*(unsigned char*)(startAddr + i) == pattern[0])
		{
			bool a = true;
			unsigned int v = 1;

			for (v; v < patternSize; v++)
			{
				if (*(unsigned char*)(startAddr + i + v) != pattern[v])
				{
					a = false;
					break;
				}
			}

			if (a)
				return (startAddr + i);

			i += v - 1;
		}
	}

	return 0;
}

unsigned int isModuleLoaded(DWORD pid, const wchar_t* module)
{
	unsigned int baseAddr = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);

	if (snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(snapshot, &moduleEntry))
		{
			do
			{
				if (!wcscmp(moduleEntry.szModule, module))
				{
					baseAddr = (unsigned int)moduleEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(snapshot, &moduleEntry));
		}
	}
	CloseHandle(snapshot);
	return baseAddr;
}