#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

class FileStats
{
// Methods
public:  
    FileStats(std::string Path);

    inline uint64_t get_empty_lines() const { return mEmptyLines; } 
    inline uint64_t get_non_empty_lines() const { return mNonEmptyLines; } 
    inline uint64_t get_words() const { return mWords; }
    inline uint64_t get_letters() const { return mLetters; }
private:
    void init();

    uint64_t count_words(std::string &Line);
    uint64_t count_letters(std::string &Line);

// Variables
public:

private:
    std::string mPath;
    uint64_t mEmptyLines;
    uint64_t mNonEmptyLines;
    uint64_t mWords;
    uint64_t mLetters;
};