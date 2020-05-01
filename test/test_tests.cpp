#include "../src/check_tests.cpp"
#include <gtest/gtest.h>

TEST(CheckTestsWork, ReturnsOne)
{
    ASSERT_EQ(1, testable());
}

TEST(CheckTestsWork, ReturnsOneAgain)
{
    ASSERT_NE(2, testable());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
