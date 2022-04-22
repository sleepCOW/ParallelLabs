#include <iostream>
#include "Common.h"

int main()
{
	HANDLE MessageHandle = TryOpenEvent(GMessageEventName);
	HANDLE EndHandle = TryOpenEvent(GEndEventName);
	WaitForSingleObject(MessageHandle, INFINITE);

	std::cout << "Child Process!" << std::endl;

	WaitForSingleObject(EndHandle, INFINITE);
	
	return 0;
}