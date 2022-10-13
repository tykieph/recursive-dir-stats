cmake_minimum_required(VERSION 3.13)

set (CMAKE_CXX_STANDARD 17)

project(recursive-dir-stats)

include(FetchContent)
FetchContent_Declare(gtest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1)
FetchContent_GetProperties(gtest)

if (NOT gtest_POPULATED)
    FetchContent_Populate(gtest)
    add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BUILD_DIR})
endif()

find_package(Threads REQUIRED)

add_executable(dir-stats 
    src/main.cpp
    src/DirStats.cpp
    src/FileStats.cpp)
target_include_directories(dir-stats PUBLIC include)
target_link_libraries(dir-stats pthread)

add_executable(tests
    tests/test.cpp
    src/DirStats.cpp
    src/FileStats.cpp    
    tests/DirStats_test.cpp
    tests/FileStats_test.cpp)
target_include_directories(tests PUBLIC include)    
target_link_libraries(tests pthread gtest_main gmock_main)