#include "stdafx.h"

// hi peppy i bypassed all the anti debugger stuff in like 10 minutes lmao

unsigned char speedSig[] = "\xDD\x56\x48\xDC\x05";
const wchar_t* bass_dll = L"bass_fx.dll";

//double speed = 1147.0; // 1147 is the base speed
double speed = 1.0;

double before = speed;
unsigned int escapeAddress;

void setSpeed();
void checkMultiplier();

// dll entry
void exec()
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	writeSlot((unsigned int)&speed);

	unsigned int baseModule = 0;

	while (!(baseModule = isModuleLoaded(GetCurrentProcessId(), bass_dll))) // module is only imported once song has been started at least once
	{
		std::cout << "Start a song to begin setup" << std::string(28, '\b');
		Sleep(1000);
	}
	
	std::cout << "\nModule loaded, scanning...\n";

	Sleep(5000); // do not remove, the part we need is not immediately allocated upon module import

	// reuse the same pattern
	unsigned int patternAddr = findPattern(baseModule, speedSig) - 6;
	std::cout << "Address of pattern: " << std::hex << patternAddr << "\n";

	escapeAddress = patternAddr + 6;

	detour((void*)patternAddr, 6, setSpeed);

	std::cout << "Speed address: " << &speed << "\n";

	std::thread(checkMultiplier).detach();
}

void checkMultiplier()
{
	while (true)
	{
		if (speed != before)
		{
			before = speed;

			if (speed > 0.f)
				printf("Speed multiplier: %.2fx\n", speed);
			else
				printf("Speed multiplier: Default\n");
		}
		Sleep(1000);
	}
}

void _declspec(naked) setSpeed() // function that replaces original
{
	if (speed > 0.f)
	{
		__asm
		{
			fld qword ptr[speed]
			fstp qword ptr[esi + 0x40]
		}
	}

	__asm
	{
		fild dword ptr[ebp + 0x0C]
		fmul qword ptr[esi + 0x40]

		jmp[escapeAddress]
	}

}
