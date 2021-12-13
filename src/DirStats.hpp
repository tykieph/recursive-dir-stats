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
    DirStats(std::string DirectoryPath, bool Recursive, bool MultiThreading);
    ~DirStats();


    void print_directory_contents();
    void print_number_of_files();
    void print_number_of_lines();
    void print_number_of_words();
    void print_number_of_letters();

    uint64_t get_number_of_files();
    uint64_t get_total_number_of_lines();
    uint64_t get_number_of_words();
    uint64_t get_number_of_letters();    
private:
    uint64_t count_empty_lines();
    uint64_t count_non_empty_lines();

    // non-recursive variants
    void load_files();
    void print_dir();

    // recursive variants
    void load_files_r();    
    void print_dir_r();

    bool directory_exists(std::string DirectoryPath);

// Variables
public:
private:
    std::string mPath;
    bool mRecursive;
    bool mMThreading;
    std::vector<FileStats> mFiles;
};
