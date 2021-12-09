#include "FileStats.hpp"

namespace fs = std::filesystem;

/************************************************************/
FileStats::FileStats(std::string Path)
    : mPath(Path)
{
    mEmptyLines     = 0;
    mNonEmptyLines  = 0;

    this->count_lines();
}
/************************************************************/
void FileStats::count_lines()
{
    std::ifstream File(mPath, std::ios::binary);

    if (File.bad())
        return; 

    while (!File.eof())
    {
        std::string Line;
        std::getline(File, Line);

        if (Line.empty())
            this->mEmptyLines++;
        else
            this->mNonEmptyLines++;
    }

    File.close();
}
/************************************************************/

/************************************************************/

/************************************************************/