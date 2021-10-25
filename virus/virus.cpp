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

	// base address of bass_fx.dll
	MODULEENTRY32 bassDll;
	std::cout << "Start a song to begin setup\n";
	while (!getModuleFull(GetCurrentProcessId(), BASS_DLL, &bassDll)) // module is only imported once song has been started at least once
		Sleep(1000);
	
	std::cout << "bass_fx.dll loaded, scanning...\n";

	Sleep(5000); // do not remove, the part we need is not immediately allocated upon module import

	Mods::RateChanger::init(bassDll, state);
}

void messageHandler(messaging::Msg* msg)
{
	#ifdef _DEBUG
		std::cout << "received message: " << messaging::UiMsg_descriptor()->FindValueByNumber(msg->uimsg())->name() << "\n";
	#endif // DEBUG
	
	msg->set_dllmsg(messaging::DllMsg::RESPONSE);

	switch (msg->uimsg())
	{
	case messaging::UiMsg::SETSPEED:
		if (msg->doubleval() != state->speed)
		{
			state->speed = msg->doubleval();
			if (state->speed > 0.f)
				printf("Speed multiplier: %.2fx\n", state->speed);
			else
				printf("Speed multiplier: Default\n");
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
