#include <gtest/gtest.h>
#include "../src/configurationparser.cpp"

// TODO: add tests for incorrect directory settings

TEST(ConfigurationParserTests, ReturnsCorrectConfig)
{
    ConfigurationParser testable{"../test/resources/test_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    ASSERT_EQ(0, std::filesystem::path{"../test/resources/dir_tests/test_dir2"}.compare(folder_config.path));
    ASSERT_EQ(30, folder_config.seconds_before_change);
}

TEST(ConfigurationParserTests, ReturnsCorrectConfigComments)
{
    ConfigurationParser testable{"../test/resources/comment_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    ASSERT_EQ(0, std::filesystem::path{"../test/resources/dir_tests/test_dir2"}.compare(folder_config.path));
}

TEST(ConfigurationParserTests, ReturnsCorrectConfigSpace)
{
    ConfigurationParser testable{"../test/resources/space_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    ASSERT_EQ(0, std::filesystem::path{"../test/resources/dir_tests/test_dir2"}.compare(folder_config.path));
}

TEST(ConfigurationParserTests, ReturnsCorrectExclusions)
{
    ConfigurationParser testable{"../test/resources/exclusions_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    std::vector<std::string> correct{"exclude1", "exclude2", "exclude3"};
    ASSERT_EQ(folder_config.directory_exclusions, correct);
}

TEST(ConfigurationParserTests, ReturnsCorrectExtensions)
{
    ConfigurationParser testable{"../test/resources/extensions_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    std::vector<std::string> correct{".txt", ".png", ".jpeg"};
    ASSERT_EQ(folder_config.file_allowed_extensions, correct);
}

TEST(ConfigurationParserTests, ReturnsCorrectPriorities)
{
    ConfigurationParser testable{"../test/resources/priorities_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    std::vector<std::pair<std::string, int>> correct{
        {"folder2", 5}, {"folder3", 10}, {"folder1", 16}};
    ASSERT_EQ(folder_config.directory_priorities, correct);
}

TEST(ConfigurationParserTests, ReturnsCorrectSeconds)
{
    ConfigurationParser testable{"../test/resources/seconds_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    std::vector<std::pair<std::string, int>> correct{
        {"folder3", 5}, {"folder1", 10}, {"folder2", 16}};
    ASSERT_EQ(folder_config.directory_seconds, correct);
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
