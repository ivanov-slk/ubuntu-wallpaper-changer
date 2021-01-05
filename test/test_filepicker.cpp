#include <gtest/gtest.h>
#include "../src/filepicker.cpp"

TEST(FilePickerTests, ReturnRandomFromMany)
{
    std::vector<std::filesystem::path> test_paths{
        "path/test/first",
        "path/test/second",
        "path/test/third"};
    FilePicker testable{test_paths};
    std::filesystem::path result = testable.pick_random_path();
    ASSERT_TRUE(std::find(test_paths.begin(), test_paths.end(), result) != test_paths.end());
}

TEST(FilePickerTests, ReturnRandomFromOne)
{
    std::vector<std::filesystem::path> test_paths{"path/test/first"};
    FilePicker testable{test_paths};
    std::filesystem::path result = testable.pick_random_path();
    ASSERT_EQ(std::filesystem::path{"path/test/first"}, result);
}

TEST(FilePickerTests, ReturnEmptyStringFromEmptyVector)
{
    std::vector<std::filesystem::path> test_paths;
    FilePicker testable{test_paths};
    std::filesystem::path result = testable.pick_random_path();
    std::filesystem::path correct;
    ASSERT_EQ(correct, result);
}