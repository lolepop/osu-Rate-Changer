#pragma once
#include "stdafx.h"
#include "ipc.h"

namespace Mods
{
	namespace RateChanger
	{
		void init(MODULEENTRY32 baseModule, IpcState* state);
	}

	namespace ManiaBpmScale
	{
		bool init(IpcState* state);
	}
}
