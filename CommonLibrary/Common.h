#pragma once

#include "windows.h"
#include "synchapi.h"

// Globals
const TCHAR* GMessageEventName = TEXT("MyEvent");
const TCHAR* GEndEventName = TEXT("EndEvent");
const TCHAR* GChildName = TEXT("C:\\University\\Parallel\\Racecondition\\Debug\\ChildProcess.exe");

bool CheckWinHandle(HANDLE Handle)
{
	if (!Handle)
	{
		std::cout << "Handle invalid, error = " << GetLastError() << std::endl;
		return false;
	}
	return true;
}

// Tries to open existing Event via OpenEvent
// if Event not existing creating new one with specified name
HANDLE TryOpenEvent(const TCHAR* EventName, bool bInheritHandle = true)
{
	HANDLE EventHandle = OpenEvent(NULL, bInheritHandle, EventName);
	if (!EventHandle)
	{
		EventHandle = CreateEvent(nullptr, true, false, EventName);
	}
	return EventHandle;
}