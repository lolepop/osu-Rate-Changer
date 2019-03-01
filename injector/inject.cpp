#include "inject.h"

constexpr const wchar_t* MAILSLOTNAME = L"\\\\.\\mailslot\\osuratechanger";
int maxAttempts = 5;

bool inject(DWORD pid, char* dll)
{
	printf("Injecting dll at path: %s into pid: %i\n", dll, pid);

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (!handle)
		return false;

	void* dllStrAlloc = VirtualAllocEx(handle, NULL, strlen(dll), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(handle, dllStrAlloc, dll, strlen(dll), 0);

	void* loadLibraryHook = (void*)&LoadLibraryA;
	HANDLE a = CreateRemoteThread(handle, 0, 0, (DWORD(WINAPI*)(LPVOID))loadLibraryHook, dllStrAlloc, 0, 0);
	WaitForSingleObject(a, INFINITE);
	CloseHandle(a);

	CloseHandle(handle);
	return true;
}

unsigned int getProcessId(wchar_t* procName)
{
	unsigned int pid = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(processEntry);
		if (Process32First(snapshot, &processEntry))
		{
			do
			{
				//std::wcout << processEntry.szExeFile << "\n";

				if (!wcscmp(processEntry.szExeFile, procName))
				{
					std::cout << "\nfound\n";
					pid = (unsigned int)processEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &processEntry));
		}
	}

	std::cout << "pid: " << (pid == 0 ? "failed" : std::to_string(pid)) << "\n";

	return pid;
}

HANDLE ms;

bool createSlot(int attempt)
{
	std::cout << "Mailslot creation ";

	if (attempt > maxAttempts)
	{
		std::cout << "failed, aborting...\n";
		return false;
	}

	ms = CreateMailslotW(MAILSLOTNAME, 0, MAILSLOT_WAIT_FOREVER, 0);


	if (!ms)
	{
		std::cout << "failed, retrying... " << maxAttempts - attempt << " attempts remaining\n";
		Sleep(2000);
		return createSlot(attempt + 1);
	}

	std::cout << "success\n";
	return true;
}

// msdn documentation is complete ass

unsigned int readSlot()
{
	DWORD nextSize;
	DWORD msgNum;

	GetMailslotInfo(ms, 0, &nextSize, &msgNum, 0);

	if (nextSize == MAILSLOT_NO_MESSAGE)
	{
		std::cout << "Waiting for message" << std::string(20, '\b');
		Sleep(500);
		return readSlot();
	}

	std::cout << "\nFilesize: " << nextSize << " Number of messages: " << msgNum << "\n";

	unsigned int a;
	char buffer[4];
	ReadFile(ms, buffer, 4, 0, 0);
	memcpy(&a, buffer, 4);

	std::cout << std::hex << "Address received: " << a << "\n";
	
	CloseHandle(ms);

	return a;
}