#include <iostream>
#include "Common.h"

// Goal of the program:
// 1. Root process creates a child process
// 2. Root process prints greetings with PID
// 3. Root process signalizing it finished the job using sync object (Event, Semaphore, Mutex)
// 4. Child process waits until sync object is signalized
// 5. Child process prints greetings with PID
// 6. Root process waits for user input before closing Child (again using sync object)
int main()
{
	STARTUPINFOW StartupInfo;
	PROCESS_INFORMATION ProcessInformation;
	memset(&StartupInfo, 0, sizeof(STARTUPINFO));
	memset(&ProcessInformation, 0, sizeof(PROCESS_INFORMATION));

	// Note: Multi processing on windows is much slower compared to UNIX based systems
	// Consider using Multi Threading instead
	if (!CreateProcess(GChildName, nullptr, nullptr, nullptr, true, CREATE_NEW_CONSOLE, nullptr, nullptr, &StartupInfo, &ProcessInformation))
	{
		std::cout << "CreateProcess Error " << GetLastError();
		return -1;
	}

	HANDLE MessageHandle = TryOpenEvent(GMessageEventName);
	HANDLE EndHandle = TryOpenEvent(GEndEventName);

	std::cout << "Root Process!" << std::endl;
	SetEvent(MessageHandle);

	system("pause");
	SetEvent(EndHandle);

	CloseHandle(ProcessInformation.hProcess);
	CloseHandle(MessageHandle);
	CloseHandle(EndHandle);
	return 0;
}