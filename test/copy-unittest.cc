#include "gtest/gtest.h"
#include "copy-image.h"
#include <iostream>

TEST (copyImageTest, invalidArguments)
{
    int result = copy(NULL, NULL);
    EXPECT_EQ(1, result);
}
