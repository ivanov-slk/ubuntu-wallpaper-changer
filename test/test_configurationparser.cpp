#include <gtest/gtest.h>
#include "../src/configurationparser.cpp"

TEST(ConfigurationParserTests, ReturnsPath)
{
    ConfigurationParser testable;
    testable.read_config_file();
    FolderConfiguration folder_config = testable.create_configuration();
    ASSERT_EQ("/nonexistent/path", folder_config.path);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}