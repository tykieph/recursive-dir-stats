#include "gtest/gtest.h"

#include "../src/FileStats.hpp"

namespace fs = std::filesystem;

/************************************************************/
class FileStatsTest : public ::testing::Test
{
protected:
    void SetUp(std::string FileName)
    {
        mPath = fs::current_path();
        mPath += fs::path("/tests/Data/" + FileName);

        mFileStats.reset(new FileStats(mPath));
    }

protected:
    std::shared_ptr<FileStats> mFileStats;    

    std::string mPath; // path to a testing data
};
/************************************************************/
TEST_F(FileStatsTest, EmptyFile)
{
    SetUp("FileStats_test_data0.txt");

    const uint64_t EmptyLines       = 0;
    const uint64_t NonEmptyLines    = 0;
    const uint64_t Words            = 0;
    const uint64_t Letters          = 0;

    EXPECT_EQ(mFileStats->get_empty_lines(), EmptyLines);
    EXPECT_EQ(mFileStats->get_non_empty_lines(), NonEmptyLines);
    EXPECT_EQ(mFileStats->get_words(), Words);
    EXPECT_EQ(mFileStats->get_letters(), Letters);
}
/************************************************************/
TEST_F(FileStatsTest, LoremIpsum1234Words)
{
    SetUp("FileStats_test_data1.txt");

    const uint64_t EmptyLines       = 14;
    const uint64_t NonEmptyLines    = 15;
    const uint64_t Words            = 1234;
    const uint64_t Letters          = 7227;

    EXPECT_EQ(mFileStats->get_empty_lines(), EmptyLines);
    EXPECT_EQ(mFileStats->get_non_empty_lines(), NonEmptyLines);
    EXPECT_EQ(mFileStats->get_words(), Words);
    EXPECT_EQ(mFileStats->get_letters(), Letters);    
}
/************************************************************/
TEST_F(FileStatsTest, SingleWord)
{
    SetUp("FileStats_test_data2.txt");

    const uint64_t EmptyLines       = 0;
    const uint64_t NonEmptyLines    = 1;
    const uint64_t Words            = 1;
    const uint64_t Letters          = 7227;

    EXPECT_EQ(mFileStats->get_empty_lines(), EmptyLines);
    EXPECT_EQ(mFileStats->get_non_empty_lines(), NonEmptyLines);
    EXPECT_EQ(mFileStats->get_words(), Words);
    EXPECT_EQ(mFileStats->get_letters(), Letters);    
}
/************************************************************/

/************************************************************/