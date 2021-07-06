#include "stdafx.h"

namespace Mods::ManiaBpmScale
{
	unsigned char sig[] = "\xDE\xC9\xDD\x1D\x00\x00\x00\x00\xDD\x05\x00\x00\x00\x00\xDD\x5D\xEC";
	char mask[] = "xxxx????xx????xxx";

	unsigned int escapeAddress;
	bool* bpmScaleFix;
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
		if (*bpmScaleFix && *speed > 0.f)
		{
			__asm
			{
				fstp st(0)

				push eax
				mov eax, [speed]
				fld qword ptr[eax]
				pop eax
			}
		}

		__asm
		{
			fmulp st(1), st(0)
			
			push eax
			mov eax, [ptrA]
			fstp qword ptr[eax]
			pop eax

			jmp[escapeAddress]
		}

	}

	bool init(IpcState* state)
	{
		static bool isInitialised = false;

		if (isInitialised)
			return true;

		std::cout << "Attempting to hook bpm scale function\n";

		speed = &state->speed;
		bpmScaleFix = &state->bpmScaleFix;

		try
		{
			//auto start = std::chrono::high_resolution_clock::now();
			unsigned int patternAddr = findPatternDynamic(sig, mask);
			//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
			//std::cout << "Time taken: " << std::dec << duration.count() << "\n";

			if (patternAddr == 0)
			{
				std::cout << "Failed to hook bpm scale function, make sure you have started a map in mania\n";
				return false;
			}

			std::cout << "Address of bpm scaling pattern: " << std::hex << patternAddr << "\n";

			escapeAddress = patternAddr + 8;
			ptrA = *(unsigned int*)(patternAddr + 4);
			std::cout << "\n ptrA: " << ptrA << "\n";

			detour((void*)patternAddr, 8, calcBpmScaling);

			isInitialised = true;
		}
		catch (const std::exception e)
		{
			std::cout << "wtf: " << e.what();
			return false;
		}

		std::cout << "Hooked bpm scale function\n";


		return true;

	}

}
