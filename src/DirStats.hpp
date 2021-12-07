#pragma once

#include <filesystem>
#include <string>
#include <iostream>


class DirStats
{
// Methods
public:
    DirStats(std::string DirectoryPath, bool Recursive);
    ~DirStats();

    void print_directory_contents();
private:
    void print_dir();
    void print_dir_rec();

// Variables
public:
private:
    std::string mPath;
    bool mRecursive;
};
