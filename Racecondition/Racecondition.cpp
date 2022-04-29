#include <iostream>
#include "windows.h"
#include "processthreadsapi.h"

int Count = 10; // Ping - Pong message count
constexpr size_t PING_ID = 0;
constexpr size_t PONG_ID = 1;
constexpr size_t THREAD_COUNT = 2;

struct PingPongParam
{
	int Counter = 0;
	HANDLE MutexHandle;
};

DWORD WINAPI Ping(LPVOID ThreadParam)
{
	PingPongParam* Params = (PingPongParam*)ThreadParam;
	int& i = Params->Counter;
	HANDLE MutexHandle = Params->MutexHandle;

    while (i < Count)
    {
        if (i % 2 == 0)
        {
			std::cout << "Ping\n";
			WaitForSingleObject(MutexHandle, INFINITE);
			++i;
            ReleaseMutex(MutexHandle);
        }
    }

    return 0;
}

DWORD WINAPI Pong(LPVOID ThreadParam)
{
    PingPongParam* Params = (PingPongParam*)ThreadParam;
    int& i = Params->Counter;
    HANDLE MutexHandle = Params->MutexHandle;

	while (i < Count)
	{
		if (i % 2 == 1)
		{
			std::cout << "Pong\n";
			WaitForSingleObject(MutexHandle, INFINITE);
			++i;
			ReleaseMutex(MutexHandle);
		}
	}

    return 0;
}

bool CheckWinHandle(HANDLE Handle)
{
    if (!Handle)
    {
        std::cout << "Handle invalid, error = " << GetLastError() << std::endl;
        return false;
    }
    return true;
}

int main()
{
    PingPongParam ThreadParam;
    ThreadParam.MutexHandle = CreateMutex(nullptr, false, nullptr);
    if (!CheckWinHandle(ThreadParam.MutexHandle))
    {
        return -1;
    }
    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);

    HANDLE ThreadArr[THREAD_COUNT];
    ThreadArr[PING_ID] = CreateThread(nullptr, SystemInfo.dwPageSize, &Ping, &ThreadParam, NULL, nullptr);
    ThreadArr[PONG_ID] = CreateThread(nullptr, SystemInfo.dwPageSize, &Pong, &ThreadParam, NULL, nullptr);

    if (!CheckWinHandle(ThreadArr[PING_ID]) || !CheckWinHandle(ThreadArr[PONG_ID]))
    {
        return -1;
    }

    WaitForMultipleObjects(THREAD_COUNT, ThreadArr, true, INFINITE);
    for (HANDLE Handle : ThreadArr)
    {
        CloseHandle(Handle);
    }
    CloseHandle(ThreadParam.MutexHandle);

    return 0;
}