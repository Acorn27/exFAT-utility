#include "gtest/gtest.h"
#include "lib/parse-command.h"

TEST(pase_argument, AllOptionPresent)
{
    int argc = 4;
    char* argv[] = {"exfat", "-i", "data.txt", "-o", "result.txt", "-c"};
    command* result = parse(argc, argv);
    EXPECT_EQ(result->infile, 1);
    EXPECT_EQ(result->outfile, 1);
    EXPECT_EQ(result->copy, 1);
    EXPECT_EQ(result->infileName, "data.txt");
    EXPECT_EQ(result->outfileName, "result.txt");
}