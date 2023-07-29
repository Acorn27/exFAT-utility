#include "gtest/gtest.h"
#include "verify-image.h"
#include <iostream>

char imageName[] = "images/exfat.img";

// test for null argument
TEST (verify_image, invalidArguments)
{
    int result = verify_image(NULL);
    EXPECT_EQ(1, result);
}

// expected pass by using unmodified/new generated image
// TEST(verify_image, expectedPassed)
// {
//     std::cout << "Create a fresh image first before run this test" << std::endl;
//     int result = verify_image(imageName);
//     EXPECT_EQ(1, result);
// }

// TEST(verify_image, expectedFailed)
// {   
//     // expected failed by modify backup region of image
//     modified_image(imageName);
//     int result = verify_image(imageName);
//     EXPECT_EQ(0, result);
// }