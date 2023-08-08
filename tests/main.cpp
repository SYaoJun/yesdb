#include "gtest/gtest.h"
int add(int a, int b) {
    return a+b;
}
TEST(SampleTest, SampleTest) {

    EXPECT_EQ(13, add(6, 7));
}