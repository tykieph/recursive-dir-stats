#include "DirStats.hpp"

namespace fs = std::filesystem;


/************************************************************/
DirStats::DirStats(std::string DirectoryPath, bool Recursive)
    : mPath(DirectoryPath), mRecursive(Recursive)
{
    // check if directory exists
    if (!fs::is_directory(mPath))
    {
        std::string ErrMsg = 
            "Given path doesn't point to"
            " an existing directory!\n";
        std::cerr << ErrMsg << std::endl;
        exit(1);        
    }

    // load all files from specified directory
    if (mRecursive)
        this->load_files_r();
    else
        this->load_files();
}
/************************************************************/
DirStats::~DirStats()
{  
}
/************************************************************/
void DirStats::load_files()
{
    for (const auto &Entry : fs::directory_iterator(mPath))
    {
        std::string Path = Entry.path();
        if (fs::is_regular_file(Path))
            mFiles.emplace_back(FileStats(Path));
    }
}
/************************************************************/
void DirStats::load_files_r()
{
    for (const auto &Entry : fs::recursive_directory_iterator(mPath))
    {
        std::string Path = Entry.path();
        if (fs::is_regular_file(Path))
            mFiles.emplace_back(FileStats(Path));
    }
}
/************************************************************/
void DirStats::print_dir()
{
    for (const auto &Entry : fs::directory_iterator(mPath))
        std::cout << Entry.path() << std::endl; 
}
/************************************************************/
void DirStats::print_dir_r()
{
    for (const auto &Entry : fs::recursive_directory_iterator(mPath))
        std::cout << Entry.path() << std::endl;     
}
/************************************************************/
void DirStats::print_directory_contents()
{
    if (mRecursive)
        this->print_dir_r();
    else
        this->print_dir();
}
/************************************************************/
void DirStats::print_number_of_files()
{
    int N = mFiles.size();

    std::cout << "Number of files in directory: " << N << std::endl;
}
/************************************************************/
void DirStats::print_number_of_lines()
{
    // number of empty lines
    uint64_t EmptyLines     = this->count_empty_lines(); 

    // number of non-empty lines
    uint64_t NonEmptyLines  = this->count_non_empty_lines();

    std::string OutMsg = 
        "Total number of lines: " 
        + std::to_string(EmptyLines + NonEmptyLines) + 
        " (" + std::to_string(EmptyLines) + " empty + "
        + std::to_string(NonEmptyLines) + " non-empty lines)";

    std::cout << OutMsg << std::endl;
}
/************************************************************/
uint64_t DirStats::count_empty_lines()
{
    return std::accumulate(
        mFiles.begin(), mFiles.end(), 0, 
        [](uint64_t Lhs, FileStats &Rhs)
        {
            return Lhs + Rhs.get_empty_lines();    
        });
}
/************************************************************/
uint64_t DirStats::count_non_empty_lines()
{
    return std::accumulate(
        mFiles.begin(), mFiles.end(), 0, 
        [](uint64_t Lhs, FileStats &Rhs)
        {
            return Lhs + Rhs.get_non_empty_lines();    
        });
}
/************************************************************/

/************************************************************/

/************************************************************/