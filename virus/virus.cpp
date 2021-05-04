#include "stdafx.h"

// hi peppy i bypassed all the anti debugger stuff in like 10 minutes lmao

const wchar_t* OSU_EXE = L"osu!.exe";
const wchar_t* BASS_DLL = L"bass_fx.dll";

//double speed = 1147.0; // 1147 is the base speed
double speed = 1.0;

double before = speed;

void checkMultiplier();

// dll entry
void exec()
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	writeSlot((unsigned int)&speed);

	// base address of bass_fx.dll
	MODULEENTRY32 bassDll;
	while (!getModuleFull(GetCurrentProcessId(), BASS_DLL, &bassDll)) // module is only imported once song has been started at least once
	{
		std::cout << "Start a song to begin setup" << std::string(28, '\b');
		Sleep(1000);
	}
	
	std::cout << "\nbass_fx.dll loaded, scanning...\n";

	Sleep(5000); // do not remove, the part we need is not immediately allocated upon module import

	Mods::RateChanger::init(bassDll, &speed);
	//Mods::ManiaBpmScale::init(&speed);
	
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

