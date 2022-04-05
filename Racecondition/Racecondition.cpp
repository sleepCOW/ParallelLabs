#include <iostream>
#include "windows.h"
#include "processthreadsapi.h"

int Count = 10;
constexpr size_t PING_ID = 0;
constexpr size_t PONG_ID = 1;
constexpr size_t THREAD_COUNT = 2;

DWORD WINAPI Ping(LPVOID ThreadParam)
{
    int& i = *(int*)ThreadParam;
    while (i < Count)
    {
        std::cout << "Ping\n";
        ++i;
    }

    return 0;
}

DWORD WINAPI Pong(LPVOID ThreadParam)
{
    int& i = *(int*)ThreadParam;
    while (i < Count)
    {
	std::cout << "Pong\n";
        ++i;
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
    int i = 0;
    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);

    HANDLE ThreadArr[THREAD_COUNT];
    ThreadArr[PING_ID] = CreateThread(nullptr, SystemInfo.dwPageSize, &Ping, &i, 0, nullptr);
    ThreadArr[PONG_ID] = CreateThread(nullptr, SystemInfo.dwPageSize, &Pong, &i, 0, nullptr);
    
    if (!CheckWinHandle(ThreadArr[PING_ID]) || !CheckWinHandle(ThreadArr[PONG_ID]))
    {
        return -1;
    }

    WaitForMultipleObjects(THREAD_COUNT, ThreadArr, true, INFINITE);
    for (HANDLE Handle : ThreadArr)
    {
        CloseHandle(Handle);
    }

    return 0;
}
