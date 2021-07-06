#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "Ws2_32.lib")

#include <windows.h>
#include <iostream>
#include <limits>
#include <TlHelp32.h>
#include <string>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <set>
#include <ppl.h>
#include <nngpp\nngpp.h>
#include <nngpp\protocol\pair0.h>

#include "sigscan.h"
#include "detour.h"
#include "mailslot.h"
#include "mods.h"
#include "ipc.h"
#include "msg.pb.h"

void exec();