#include <iostream>
#include "windows.h"

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
    return 0;
}