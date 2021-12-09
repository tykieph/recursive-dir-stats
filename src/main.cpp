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

#include "DirStats.hpp"

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    std::string Path = "";
    bool Recursive = false, Err = false;

    int opt;
    while ((opt = getopt(argc, argv, "p:r:")) != -1)
    {
        if (opt == 'p')
            Path = optarg;
        else if (opt == 'r')
            Recursive = atoi(optarg);
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

    std::unique_ptr<DirStats> Stats(new DirStats(Path, Recursive));
    Stats->print_directory_contents();
    Stats->print_number_of_files();
    Stats->print_number_of_lines();



    return 0;
}