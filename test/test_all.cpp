#include <gtest/gtest.h>
#include "test_configurationparser.cpp"
#include "test_changecommand.cpp"

// TODO: this is probably not the best way to run the tests... consider refactoring.

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
