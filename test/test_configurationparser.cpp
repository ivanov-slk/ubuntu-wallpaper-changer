#include <gtest/gtest.h>
#include "../src/configurationparser.cpp"

TEST(ConfigurationParserTests, ReturnsCorrectConfig)
{
    ConfigurationParser testable{"../test/resources/test_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    ASSERT_EQ(0, std::filesystem::path{"../test/resources/dir_tests/test_dir2"}.compare(folder_config.path));
    ASSERT_EQ(30, folder_config.seconds_before_change);
}

TEST(ConfigurationParserTests, ThrowsExceptionOnNonexistentPath)
{
    ConfigurationParser testable{"nonexistent/path"};
    ASSERT_THROW(testable.create_configuration(), FileIOException);
}

TEST(ConfigurationParserTests, ThrowsIncorrectPath)
{
    ConfigurationParser testable{"../test/resources/basic_config.cfg"}; // assumes we are in build/
    ASSERT_THROW(testable.create_configuration(), ConfigurationParsingException);
}

TEST(ConfigurationParserTests, ThrowsIncorrectSeconds1)
{
    ConfigurationParser testable{"../test/resources/bad_seconds_config.cfg"}; // assumes we are in build/
    ASSERT_THROW(testable.create_configuration(), ConfigurationParsingException);
}

TEST(ConfigurationParserTests, ThrowsIncorrectSeconds2)
{
    ConfigurationParser testable{"../test/resources/bad_seconds_config2.cfg"}; // assumes we are in build/
    ASSERT_THROW(testable.create_configuration(), ConfigurationParsingException);
}