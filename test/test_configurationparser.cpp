#include <gtest/gtest.h>
#include "../src/configurationparser.cpp"

TEST(ConfigurationParserTests, ReturnsExceptionOnNonexistentPath)
{
    ConfigurationParser testable{"nonexistent/path"};
    ASSERT_THROW(testable.create_configuration(), FileIOException);
}

TEST(ConfigurationParserTests, ReturnsCorrectPath)
{
    ConfigurationParser testable{"../test/resources/basic_config.cfg"}; // assumes we are in build/
    FolderConfiguration folder_config = testable.create_configuration();
    cout << folder_config.path;
    // ASSERT_EQ(0, std::filesystem::path{"this/does/not/exist"}.compare(folder_config.path));
}
