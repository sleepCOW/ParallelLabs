// Benchmark.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

int main()
{
    // create child process - receiver of data

    // chrono start
    // create large chunk of random data (specify with argument?)
    // or use some existing large file (don't wanna use a file)
    // chrono end

    // create pipe
    // chrono start
    // send all the data
    // ALSO CHRONO ON RECEIVER
    // chrono end
    // Close all pipe handles

	// create shared memory
	// chrono start
	// send all the data (use sync for memory)
	// ALSO CHRONO ON RECEIVER
	// chrono end
	// Close all pipe handles

	// create socket
	// chrono start
	// send all the data
	// ALSO CHRONO ON RECEIVER
	// chrono end
	// Close all pipe handles

	// Receive how many time passed from child



    std::cout << "Hello World!\n";
}