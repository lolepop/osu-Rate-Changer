#include "stdafx.h"

namespace Mods::RateChanger
{
	unsigned char speedSig[] = "\xDD\x56\x48\xDC\x05";
	char speedMask[] = "xxxxx";

	unsigned int escapeAddress;
	double* speed;

	void _declspec(naked) setSpeed() // function that replaces original
	{
		if (*speed > 0.f)
		{
			__asm
			{
				// fld [*speed]
				push eax
				mov eax, [speed]
				fld qword ptr[eax]
				pop eax

				fstp qword ptr[esi + 0x40]
			}
		}

		__asm
		{
			fild dword ptr[ebp + 0x0C]
			fmul qword ptr[esi + 0x40]

			jmp [escapeAddress]
		}

	}

	void init(unsigned int baseModule, double* speedPtr)
	{
		speed = speedPtr;

		// reuse the same pattern
		unsigned int patternAddr = findPattern(baseModule, speedSig, speedMask) - 6;
		std::cout << "Address of pattern: " << std::hex << patternAddr << "\n";

		escapeAddress = patternAddr + 6;

		detour((void*)patternAddr, 6, setSpeed);
	}

}

