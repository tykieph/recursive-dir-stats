#pragma once

#include <filesystem>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>

#include "FileStats.hpp"


class DirStats
{
// Methods
public:
    DirStats(std::string DirectoryPath, bool Recursive);
    ~DirStats();

    void print_directory_contents();
    void print_number_of_files();
    void print_number_of_lines();
private:
    uint64_t count_empty_lines();
    uint64_t count_non_empty_lines();

    // non-recursive variants
    void load_files();
    void print_dir();

    // recursive variants
    void load_files_r();    
    void print_dir_r();


// Variables
public:
private:
    std::string mPath;
    bool mRecursive;
    std::vector<FileStats> mFiles;
};
