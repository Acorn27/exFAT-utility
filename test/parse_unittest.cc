#include "gtest/gtest.h"
#include "lib/parse-command.h"

TEST(pase_argument, AllOptionPresent)
{   
    int argc = 7;
    char* fakeArgv[argc];
    // const_cast to suppress warning
    fakeArgv[0] = const_cast<char*>("exfat");                          
    fakeArgv[1] = const_cast<char*>("-i");                  
    fakeArgv[2] = const_cast<char*>("data.txt");
    fakeArgv[3] = const_cast<char*>("-o");
    fakeArgv[4] = const_cast<char*>("result.txt");
    fakeArgv[5] = const_cast<char*>("-c");
    fakeArgv[6] = nullptr;

    //command* result = parse(argc, fakeArgv);
    //EXPECT_EQ(result->outfile, 1);
    //EXPECT_EQ(result->copy, 1);
    //EXPECT_EQ(result->infileName, "data.txt");
    //EXPECT_EQ(result->outfileName, "result.txt");
    EXPECT_EQ(1,3);
}