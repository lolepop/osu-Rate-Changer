#include "stdafx.h"

// hi peppy i bypassed all the anti debugger stuff in like 10 minutes lmao

const wchar_t* OSU_EXE = L"osu!.exe";
const wchar_t* BASS_DLL = L"bass_fx.dll";

//double speed = 1147.0; // 1147 is the base speed
Ipc* ipc;
IpcState* state = new IpcState();

void messageHandler(messaging::Msg* msg);

// dll entry
void exec()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	ipc = new Ipc(&messageHandler);
	ipc->start();

	//writeSlot((unsigned int)&speed);

	// base address of bass_fx.dll
	MODULEENTRY32 bassDll;
	while (!getModuleFull(GetCurrentProcessId(), BASS_DLL, &bassDll)) // module is only imported once song has been started at least once
	{
		std::cout << "Start a song to begin setup" << std::string(28, '\b');
		Sleep(1000);
	}
	
	std::cout << "\nbass_fx.dll loaded, scanning...\n";

	Sleep(5000); // do not remove, the part we need is not immediately allocated upon module import

	Mods::RateChanger::init(bassDll, state);
	//Mods::ManiaBpmScale::init(state);
	
	//std::cout << "Speed address: " << &speed << "\n";

	//std::thread(checkMultiplier).detach();
}

void messageHandler(messaging::Msg* msg)
{
	std::cout << "received message: " << msg->uimsg() << "\n";
	msg->set_dllmsg(messaging::DllMsg::RESPONSE);

	switch (msg->uimsg())
	{
	case messaging::UiMsg::SETSPEED:
		if (msg->doubleval() != state->speed)
		{
			state->speed = msg->doubleval();
			if (state->speed > 0.f)
				printf("\nSpeed multiplier: %.2fx\n", state->speed);
			else
				printf("\nSpeed multiplier: Default\n");
		}
		break;
	case messaging::UiMsg::SETBPMSCALE:
		if (Mods::ManiaBpmScale::init(state))
			state->bpmScaleFix = msg->boolval();
		else
			msg->set_boolval(false);
		break;
	default:
		return;
	}

	ipc->send(msg);

}

//void checkMultiplier()
//{
//	while (true)
//	{
//		if (speed != before)
//		{
//			before = speed;
//
//			if (speed > 0.f)
//				printf("Speed multiplier: %.2fx\n", speed);
//			else
//				printf("Speed multiplier: Default\n");
//		}
//		Sleep(1000);
//	}
//}

