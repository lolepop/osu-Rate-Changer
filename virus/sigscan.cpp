#include "stdafx.h"

//unsigned int findPattern(unsigned int startAddr, unsigned char pattern[], char mask[])
//{
//	unsigned int patternSize = strlen(mask);
//	
//	for (unsigned int i = startAddr; i < UINT_MAX; i++)
//	{
//		if (mask[0] != '?' && *(unsigned char*)i == pattern[0])
//		{
//			bool a = true;
//			unsigned int v = 1;
//
//			for (v; v < patternSize; v++)
//			{
//				// bootleg overflow protection
//				if (mask[v] != '?' && (i + v) > i && *(unsigned char*)(i + v) != pattern[v])
//				{
//					a = false;
//					break;
//				}
//			}
//
//			if (a)
//				return (startAddr + i);
//
//			//i += v - 1;
//		}
//	}
//
//	return 0;
//}

unsigned int findPattern(MODULEENTRY32 module, unsigned char pattern[], char mask[])
{
	auto a = (unsigned int)module.modBaseAddr;
	return findPatternDynamic(pattern, mask, a, a + module.dwSize);
}

// scan all allocated regions in process
unsigned int findPatternDynamic(unsigned char pattern[], char mask[], unsigned int currAddress, unsigned int maxAddress)
{
	int patternSize = strlen(mask);
	MODULEENTRY32 dll;
	getModuleFull(GetCurrentProcessId(), L"virus.dll", &dll);
	unsigned int dllStart = (unsigned int)dll.modBaseAddr;
	unsigned int dllEnd = dllStart + (unsigned int)dll.modBaseSize;

	//unsigned int currAddress = 0;
	MEMORY_BASIC_INFORMATION pageInfo;
	int matchCount = 0; // number of characters in pattern matched
	std::queue<unsigned int> firstCharQueue; // optimisation: offset address of first character matches
	std::set<unsigned int> checkedOffsets;

	//MEMORY_BASIC_INFORMATION currentDllInfo;
	//VirtualQueryEx(GetCurrentProcess(), &findPatternDynamic, &currentDllInfo, sizeof(MEMORY_BASIC_INFORMATION));
	
	bool firstRun = true;
	auto procHandle = GetCurrentProcess();
	do
	{
		if (firstRun || currAddress >= (unsigned int)pageInfo.BaseAddress + pageInfo.RegionSize)
		{
			firstRun = false;
			matchCount = 0;

			std::queue<unsigned int> tmp;
			std::swap(firstCharQueue, tmp); // flush queue

			// dont read the injected dll memory
			if (currAddress >= dllStart && currAddress <= dllEnd)
			{
				currAddress = dllEnd + 1;
				continue;
			}

			if (VirtualQueryEx(procHandle, (LPCVOID)currAddress, &pageInfo, sizeof(MEMORY_BASIC_INFORMATION)) != sizeof(MEMORY_BASIC_INFORMATION))
				break;
			unsigned int n = (unsigned int)pageInfo.BaseAddress + pageInfo.RegionSize;

			if ((pageInfo.State & MEM_COMMIT) && (pageInfo.Protect & (PAGE_EXECUTE_READWRITE | PAGE_READWRITE)) && !(pageInfo.Protect & (PAGE_NOACCESS | PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE))) // is readable without virtualprotect
			{
				#ifdef DEBUG
					std::cout << "a: " << pageInfo.BaseAddress << "\n";
					std::cout << "b: " << pageInfo.RegionSize << "\n";
					std::cout << "c: " << pageInfo.AllocationBase << "\n";
					std::cout << "d: " << pageInfo.AllocationProtect << "\n";
					std::cout << "e: " << pageInfo.Protect << "\n";
					std::cout << "f: " << pageInfo.Type << "\n\n";
				#endif
			}
			else
			{
				if (currAddress > n)
					return 0;
				currAddress = n;
				continue;
			}

		}

		auto addressByte = *(unsigned char*)(currAddress);
		bool match = addressByte == pattern[matchCount];
		if ((match && matchCount == 0) || addressByte == pattern[0])
		{
			if (checkedOffsets.find(currAddress) == checkedOffsets.end())
			{
				firstCharQueue.push(currAddress);
				checkedOffsets.insert(currAddress);
			}
		}

		if (mask[matchCount] == '?' || match) // subsequent chars
		{
			if (++matchCount == patternSize)
				return currAddress - patternSize + 1;
		}
		else
		{
			matchCount = 0;
			if (!firstCharQueue.empty())
			{
				currAddress = firstCharQueue.front();
				firstCharQueue.pop();
				continue;
			}
		}

		currAddress++;

	} while (currAddress < maxAddress || currAddress > 0);

	return 0;
}

bool getModuleFull(DWORD pid, const wchar_t* module, MODULEENTRY32* out)
{
	unsigned int baseAddr = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);

	MODULEENTRY32 moduleEntry;
	bool flag = false;
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(snapshot, &moduleEntry))
		{
			do
			{
				if (!wcscmp(moduleEntry.szModule, module))
				{
					flag = true;
					*out = moduleEntry;
					break;
				}
			} while (Module32Next(snapshot, &moduleEntry));
		}
	}
	CloseHandle(snapshot);
	return flag;
}

unsigned int getModule(DWORD pid, const wchar_t* module)
{
	MODULEENTRY32 r;
	return getModuleFull(pid, module, &r) ? (unsigned int)r.modBaseAddr : -1;
}