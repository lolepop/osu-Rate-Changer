#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <limits>
#include <TlHelp32.h>
#include <string>
#include <thread>

#include "sigscan.h"
#include "detour.h"
#include "mailslot.h"

void exec();