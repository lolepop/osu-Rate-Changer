#include "stdafx.h"

// tested only with stable build but makes use of a common dll so it should work with the different versions

unsigned char speedSig[] = "\xD9\x56\x34\xD8\x05";
const wchar_t* bass_dll = L"bass_fx.dll";

float speed = 1147.0f; // 1147 is the base speed

float before = speed;
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
	orig = *(unsigned int*)(baseModule + 0xC1F8);

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
			printf("Speed multiplier: %.2fx\n", speed / 1147.0f);
		}
		Sleep(1000);
	}
}

void _declspec(naked) setSpeed() // function that replaces original
{
	__asm
	{
		push ebx
		mov ebx, [speed]
		mov [esi + 0x34], ebx
		pop ebx

		fadd dword ptr [orig]

		jmp [back]
	}
}