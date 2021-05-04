#include "stdafx.h"

namespace Mods::ManiaBpmScale
{
	unsigned char sig[] = "\xDE\xC9\xDD\x1D\x00\x00\x00\x00\xDD\x05\x00\x00\x00\x00\xDD\x5D\xEC";
	char mask[] = "xxxx????xx????xxx";

	unsigned int escapeAddress;
	double* speed;

	unsigned int ptrA;

	// IGNORE
	//#=zN8BjG5Mej$F35o7tim_np3OW9GsUWH60oddwia1yKtIcIo6P37HO4$8=::#=zTJe9KZw=+160 - D8 3D B0D47205        - fdivr dword ptr [0572D4B0]
	//
	//
	//DE C9 DD 1D ? ? ? ? DD 05 ? ? ? ? DD 5D EC
	//
	//
	//#=zN8BjG5Mej$F35o7tim_np3OW9GsUWH60oddwia1yKtIcIo6P37HO4$8=::#=zTJe9KZw=+8B - DEC9                  - fmulp st(1),st(0)
	//#=zN8BjG5Mej$F35o7tim_np3OW9GsUWH60oddwia1yKtIcIo6P37HO4$8=::#=zTJe9KZw=+8D - DD 1D A0655501        - fstp qword ptr [015565A0]
	//#=zN8BjG5Mej$F35o7tim_np3OW9GsUWH60oddwia1yKtIcIo6P37HO4$8=::#=zTJe9KZw=+93 - DD 05 98655501        - fld qword ptr [01556598]
	//#=zN8BjG5Mej$F35o7tim_np3OW9GsUWH60oddwia1yKtIcIo6P37HO4$8=::#=zTJe9KZw=+99 - DD 5D EC              - fstp qword ptr [ebp-14]
	//#=zN8BjG5Mej$F35o7tim_np3OW9GsUWH60oddwia1yKtIcIo6P37HO4$8=::#=zTJe9KZw=+9C - 83 FF 01              - cmp edi,01


	void _declspec(naked) calcBpmScaling()
	{
		if (*speed > 0.f)
		{
			__asm
			{
				// fld [*speed]
				push eax
				mov eax, [speed]

				pop eax

			}
		}

		__asm
		{
			fmulp st(1), st(0)
			fstp qword ptr[ptrA]
			jmp[escapeAddress]
		}

	}

	void init(double* speedPtr)
	{
		speed = speedPtr;

		try
		{
			auto start = std::chrono::high_resolution_clock::now();
			unsigned int patternAddr = findPatternDynamic(sig, mask);
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
			std::cout << "Time taken: " << std::dec << duration.count() << "\n";
			std::cout << "Address of bpm scaling pattern: " << std::hex << patternAddr << "\n";
		}
		catch (const std::exception e)
		{
			std::cout << "wtf: " << e.what();
		}

		//escapeAddress = patternAddr + 8;

		//detour((void*)patternAddr, 8, calcBpmScaling);
	}

}
