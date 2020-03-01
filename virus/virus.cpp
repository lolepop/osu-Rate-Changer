#include "stdafx.h"

// tested only with stable build but makes use of a common dll so it should work with the different versions

unsigned char speedSig[] = "\xDD\x56\x48\xDC\x05";
const wchar_t* bass_dll = L"bass_fx.dll";

double speed = 1147.0; // 1147 is the base speed

double before = speed;
unsigned int back;
unsigned int orig; // fadd dword ptr [bass_fx.dll + 0xC1F8]

void setSpeed();
void checkMultiplier();

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

	unsigned int patternAddr = findPattern(baseModule, speedSig);
	std::cout << "Address of pattern: " << std::hex << patternAddr << "\n";

	back = patternAddr + 9;
	orig = *(unsigned int*)(baseModule + 0xE100);

	detour((void*)patternAddr, 9, setSpeed);

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
				printf("Speed multiplier: %.2fx\n", speed / 1147.0f);
			else
				printf("Speed multiplier: Default\n");
		}
		Sleep(1000);
	}
}

void _declspec(naked) setSpeed() // function that replaces original
{
	__asm
	{
		fst qword ptr [esi + 0x48]
	}

	if (speed > 0.f)
	{
		__asm
		{
			fld qword ptr [speed]
			fst qword ptr [esi+0x48]
		}
	}

	
	__asm
	{
		fadd dword ptr [orig]

		jmp [back]
	}
}