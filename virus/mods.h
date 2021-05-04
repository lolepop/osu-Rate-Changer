#pragma once
#include "stdafx.h"

namespace Mods
{
	namespace RateChanger
	{
		void init(MODULEENTRY32 baseModule, double* speedPtr);
	}

	namespace ManiaBpmScale
	{
		void init(double* speedPtr);
	}
}
