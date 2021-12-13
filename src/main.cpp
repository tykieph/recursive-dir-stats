/*************************************************************


Create the application that will analyze and show statistics 
of specified directory that will handle recursive directories. 
It should print number of files and total number of lines 
(might as well count non-empty and empty lines). 
Provide unit tests for solutions.

- Application should use multithreading (keep in mind 
system limitations, you might need to control number of 
concurrent calls, e.g., use thread pool).

- Use std::filesystem

- Use GTest for Unit Tests

- As a bonus, you could also count words and letters and 
provide performance benchmarks (e.g., measure the impact of 
using the different number of threads).


**************************************************************/

#include <iostream>
#include <string>
#include <filesystem>
#include <getopt.h>
#include <chrono>
#include <utility>
#include <thread>

#include "ThreadPool.hpp"
#include "DirStats.hpp"

#ifdef RUN_TESTS

#include "gtest/gtest.h"

#endif

namespace fs = std::filesystem;

typedef std::chrono::high_resolution_clock::time_point TPoint;
#define TDuration(time) std::chrono::duration_cast<std::chrono::nanoseconds>(time).count()
#define TNow() std::chrono::high_resolution_clock::now()


int main(int argc, char **argv)
{
    std::string Path = "";
    bool Recursive = false, MThreading = false, Err = false;

    int opt;
    while ((opt = getopt(argc, argv, "p:rm")) != -1)
    {
        if (opt == 'p')
            Path = optarg;
        else if (opt == 'r')
            Recursive = true;
        else if (opt == 'm')
            MThreading = true;            
        else
            Err = true;
    }
    
    if (Err || Path == "")
    {
        std::string ErrMsg = 
            "Usage: " + std::string(argv[0]) + 
            " -p <path>"
            " -r <recursive>";

        std::cerr << ErrMsg << std::endl;
        exit(1);
    }


    TPoint Start = TNow();

    std::unique_ptr<DirStats> Stats(new DirStats(Path, Recursive, MThreading, 0));
    
    // Stats->print_number_of_files();
    // Stats->print_number_of_lines();
    // Stats->print_number_of_words();
    // Stats->print_number_of_letters();

    TPoint End = TNow();
    double ElapsedTime = TDuration(End - Start) / 1000000000.0;

    std::string FinalMsg = 
        "Program execution took " 
        + std::to_string(ElapsedTime) + " seconds.";
    std::cout << FinalMsg << std::endl;
    
#ifdef RUN_TESTS
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
#else
    return 0;
#endif
}