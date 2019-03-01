#include "stdafx.h"

constexpr const wchar_t* MAILSLOTNAME = L"\\\\.\\mailslot\\osuratechanger";

//HANDLE ms;
int maxAttempts = 5;

bool writeSlot(unsigned int addr, int attempt)
{
	HANDLE ms = CreateFileW(MAILSLOTNAME, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	std::cout << "Mailslot write ";

	if (attempt > maxAttempts)
	{
		std::cout << "failed, aborting...\n";
		return false;
	}

	unsigned char a[4];
	memcpy(a, &addr, 4);

	if (!WriteFile(ms, a, 4, 0, 0))
	{
		std::cout << "failed, retrying... " << maxAttempts - attempt << " attempts remaining\n";
		Sleep(2000);
		return writeSlot(addr, attempt + 1);
	}

	std::cout << "success\n";
	return true;

}