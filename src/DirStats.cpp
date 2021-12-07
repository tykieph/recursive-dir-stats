#include "DirStats.hpp"

namespace fs = std::filesystem;


/************************************************************/
DirStats::DirStats(std::string DirectoryPath, bool Recursive)
    : mPath(DirectoryPath), mRecursive(Recursive)
{

}
/************************************************************/
DirStats::~DirStats()
{  
}
/************************************************************/
void DirStats::print_dir()
{
    for (const auto &Entry : fs::directory_iterator(mPath))
        std::cout << Entry.path() << std::endl; 
}
/************************************************************/
void DirStats::print_dir_rec()
{
    for (const auto &Entry : fs::recursive_directory_iterator(mPath))
        std::cout << Entry.path() << std::endl;     
}
/************************************************************/
void DirStats::print_directory_contents()
{
    if (mRecursive)
        this->print_dir_rec();
    else
        this->print_dir();
}
/************************************************************/