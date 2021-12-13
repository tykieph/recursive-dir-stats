// #include "gtest/gtest.h"

// #include "../src/DirStats.hpp"

// namespace fs = std::filesystem;

// /************************************************************/
// class DirStatsTest : public ::testing::Test
// {
// protected:
//     void SetUp(std::string DirName)
//     {
//         mPath = fs::current_path();
//         mPath += fs::path("/tests/Data/" + DirName);

//         mDirStats.reset(new DirStats(mPath, false, false));
//         mDirStatsR.reset(new DirStats(mPath, true, false));
//         mDirStatsMT.reset(new DirStats(mPath, false, true));
//         mDirStatsRMT.reset(new DirStats(mPath, true, true));
//     }

// protected:
//     std::shared_ptr<DirStats> mDirStats;    // non-recursive
//     std::shared_ptr<DirStats> mDirStatsR;   // recursive
//     std::shared_ptr<DirStats> mDirStatsMT;  // non-recursive + multi-threading
//     std::shared_ptr<DirStats> mDirStatsRMT; // recursive + multi-threading

//     std::string mPath; // path to a testing data
// };
// /************************************************************/
// TEST_F(DirStatsTest, EmptyDirectory)
// {
//     SetUp("DirStats_test_data0");

//     const uint64_t CountFiles = 0;

//     EXPECT_EQ(mDirStats->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsR->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsMT->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsRMT->get_number_of_files(), CountFiles);
// }
// /************************************************************/
// TEST_F(DirStatsTest, CountingFiles)
// {
//     SetUp("DirStats_test_data1");

//     const uint64_t CountFiles = 456;

//     EXPECT_EQ(mDirStats->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsR->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsMT->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsRMT->get_number_of_files(), CountFiles);    
// }
// /************************************************************/
// TEST_F(DirStatsTest, CountingFilesRec)
// {
//     SetUp("DirStats_test_data2");

//     const uint64_t CountFiles       = 0;
//     const uint64_t CountFilesRec    = 26;

//     EXPECT_EQ(mDirStats->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsR->get_number_of_files(), CountFilesRec);

//     EXPECT_EQ(mDirStatsMT->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsRMT->get_number_of_files(), CountFilesRec);    
// }
// /************************************************************/
// TEST_F(DirStatsTest, CountingFilesWithMultipleDirs)
// {
//     SetUp("DirStats_test_data3");

//     const uint64_t CountFiles       = 26*4;
//     const uint64_t CountFilesRec    = CountFiles + 10*4*4;

//     EXPECT_EQ(mDirStats->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsR->get_number_of_files(), CountFilesRec);

//     EXPECT_EQ(mDirStatsMT->get_number_of_files(), CountFiles);

//     EXPECT_EQ(mDirStatsRMT->get_number_of_files(), CountFilesRec); 
// }
// /************************************************************/
// TEST_F(DirStatsTest, CountingFilesAndFileStats)
// {
//     SetUp("DirStats_test_data4");

//     const uint64_t CountFiles       = 3;
//     const uint64_t CountFilesRec    = CountFiles + 2;

//     const uint64_t CountLines       = 29;
//     const uint64_t CountWords       = 1234;
//     const uint64_t CountLetters     = 7227;

//     EXPECT_EQ(mDirStats->get_number_of_files(), CountFiles);
//     EXPECT_EQ(mDirStats->get_total_number_of_lines(), CountLines  * CountFiles);
//     EXPECT_EQ(mDirStats->get_number_of_words(), CountWords * CountFiles);
//     EXPECT_EQ(mDirStats->get_number_of_letters(), CountLetters * CountFiles);

//     EXPECT_EQ(mDirStatsR->get_number_of_files(), CountFilesRec);
//     EXPECT_EQ(mDirStatsR->get_total_number_of_lines(), CountLines * CountFilesRec);
//     EXPECT_EQ(mDirStatsR->get_number_of_words(), CountWords * CountFilesRec);
//     EXPECT_EQ(mDirStatsR->get_number_of_letters(), CountLetters * CountFilesRec);

//     EXPECT_EQ(mDirStatsMT->get_number_of_files(), CountFiles);
//     EXPECT_EQ(mDirStatsMT->get_total_number_of_lines(), CountLines * CountFiles);
//     EXPECT_EQ(mDirStatsMT->get_number_of_words(), CountWords * CountFiles);
//     EXPECT_EQ(mDirStatsMT->get_number_of_letters(), CountLetters * CountFiles);

//     EXPECT_EQ(mDirStatsRMT->get_number_of_files(), CountFilesRec);
//     EXPECT_EQ(mDirStatsRMT->get_total_number_of_lines(), CountLines * CountFilesRec); 
//     EXPECT_EQ(mDirStatsRMT->get_number_of_words(), CountWords * CountFilesRec);
//     EXPECT_EQ(mDirStatsRMT->get_number_of_letters(), CountLetters * CountFilesRec);    
// }
// /************************************************************/

// /************************************************************/