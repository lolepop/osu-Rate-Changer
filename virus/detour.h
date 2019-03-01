#pragma once
#include "stdafx.h"

void detour(void* targetAddr, int overrideLen, void* detourFunc);
