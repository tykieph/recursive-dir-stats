#include "FileStats.hpp"

namespace fs = std::filesystem;

/************************************************************/
FileStats::FileStats(std::string Path)
    : mPath(Path)
{
    mEmptyLines     = 0;
    mNonEmptyLines  = 0;
    mWords          = 0;
    mLetters        = 0;

    this->init();
}
/************************************************************/
void FileStats::init()
{
    if (!fs::is_regular_file(mPath))
        return;

    std::ifstream File(mPath, std::ios::binary);

    if (File.bad())
        return; 

    if (File.is_open())
    {
        std::string Line;
        while (std::getline(File, Line))
        {
            if (Line.empty())
            {
                mEmptyLines++;
            }
            else
            {
                mNonEmptyLines++;    

                // count words
                mWords += this->count_words(Line);

                // count letters
                mLetters += this->count_letters(Line);
            }
        }
    }

    File.close();
}
/************************************************************/
uint64_t FileStats::count_words(std::string &Line)
{
    std::stringstream Stream(Line);
    std::string Word;
    
    uint64_t Counter = 0;
    while (Stream >> Word)
        Counter++;

    return Counter;
}
/************************************************************/
uint64_t FileStats::count_letters(std::string &Line)
{
    uint64_t Counter = 0;
    for (size_t i = 0; i < Line.size(); i++)
    {
        if (!isspace(Line[i]))
            Counter++;    
    }

    return Counter;
}
/************************************************************/