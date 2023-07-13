#include "gtest/gtest.h"
#include "parse-command.h"
#include <iostream>

TEST(pase_argument, AllOptionPresent)
{   

    // mock argv[]
    char arg0[] = "exfat";
    char arg1[] = "-i";
    char arg2[] = "data.txt";
    char arg3[] = "-o";
    char arg4[] = "result.txt";
    char arg5[] = "-c";
    char arg6[] = "-v";
    char* argv[] = { &arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], &arg5[0], &arg6[0], NULL };

    // mock argv
    int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

    command* result = parse(argc, argv);
    
    EXPECT_FALSE(result == nullptr);
    EXPECT_EQ(result->copy, 1);
    EXPECT_EQ(result->verify, 1);
    EXPECT_EQ(result->help, 0);
    EXPECT_EQ(result->extract, 0);
    EXPECT_EQ(strcmp(result->infileName,"data.txt"), 0);
    EXPECT_EQ(strcmp(result->outfileName,"result.txt"), 0);
    
    clean_up(result);
}