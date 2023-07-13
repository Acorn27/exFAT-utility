#include "gtest/gtest.h"
#include "file-handler.h"
#include <iostream>

// getFileDescriptor with Null arguments
TEST (getFileDescriptor, NullInput)
{   
    int result = getFileDescriptor(NULL, -99);
    EXPECT_EQ(result, -1);
}

// getFileSize with file descriptor = -1
TEST(getFileSize, NullInput)
{
    int result = getFileSize(-1);
    EXPECT_EQ(-1, result);
}

// Print out image metadata with Null arguments
TEST(printMetaData, NullInput)
{
    int result = print_metedata(NULL);
    EXPECT_EQ(-1, result);
}

// Test clean up with Null arguments
TEST(clean_up, NullInput)
{
    int result = clean_up(-1, -1, NULL);
    EXPECT_EQ(-1, result);
}