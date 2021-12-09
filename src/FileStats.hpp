#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

class FileStats
{
// Methods
public:
    FileStats(std::string Path);

    inline uint64_t get_empty_lines() { return mEmptyLines; } 
    inline uint64_t get_non_empty_lines() { return mNonEmptyLines; } 
private:
    void count_lines();


// Variables
public:

private:
    std::string mPath;
    uint64_t mEmptyLines;
    uint64_t mNonEmptyLines;
};