/**
 * Testing strategy:
 * 1. create_subdirs_with_priorities():
 * - test overlap with directory_priorities;
 * - test no overlap with directory_priorities;
 * - test empty directory_priorities;
 * - test no subdirectories;
 * 2. normalize_priorities():
 * - test non-empty subdirs_with_priorities;
 * - test empty subdirs_with_priorities;
 * 3. pick_directory():
 * - threshold set to 0.5 (fixed) only if `testing`
 * flag is passed as an argument to pick_directory;
 * - test empty normalized_priorities;
 * - test non-empty unique normalized_priorities;
 * - test non-empty duplicated normalized_priorities
 */

#include <gtest/gtest.h>
#include "../src/weightedstrategy.cpp"

TEST(WeightedStrategyTests, SubdirsOverlap)
{
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities{
        {"dir1", 1}, {"dir2", 2}, {"dir3", 3}};
    std::vector<std::filesystem::path> test_input{
        "/path/dir2", "/path/other_dir", "/path/dir3"};
    std::vector<std::pair<std::filesystem::path, int>> correct{
        {"/path/other_dir", 1}, {"/path/dir2", 2}, {"/path/dir3", 3}};
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, int>> result = testable.create_subdirs_with_priorities(test_input);
    ASSERT_EQ(result, correct);
}

TEST(WeightedStrategyTests, SubdirsNoOverlap)
{
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities{
        {"dir1", 1}, {"dir2", 2}, {"dir3", 3}};
    std::vector<std::filesystem::path> test_input{
        "/path/other_dir1", "/path/other_dir2", "/path/other_dir3"};
    std::vector<std::pair<std::filesystem::path, int>> correct{
        {"/path/other_dir1", 1}, {"/path/other_dir2", 1}, {"/path/other_dir3", 1}};
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, int>> result = testable.create_subdirs_with_priorities(test_input);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, SubdirsPrioritiesEmpty)
{
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities;
    std::vector<std::filesystem::path> test_input{
        "other_dir1", "other_dir2", "other_dir3"};
    std::vector<std::pair<std::filesystem::path, int>> correct{
        {"other_dir1", 1}, {"other_dir2", 1}, {"other_dir3", 1}};
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, int>> result = testable.create_subdirs_with_priorities(test_input);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, SubdirsSubdirsEmpty)
{
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities{
        {"dir1", 1}, {"dir2", 2}, {"dir3", 3}};
    std::vector<std::filesystem::path> test_input;
    std::vector<std::pair<std::filesystem::path, int>> correct;
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, int>> result = testable.create_subdirs_with_priorities(test_input);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, NormalizationNonEmpty)
{
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities;
    std::vector<std::pair<std::filesystem::path, int>> test_input{
        {"/path/dir1", 50}, {"/path/dir2", 20}, {"/path/dir3", 30}};
    std::vector<std::pair<std::filesystem::path, float>> correct{
        {"/path/dir1", 0.5}, {"/path/dir2", 0.7}, {"/path/dir3", 1.0}};
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, float>> result = testable.normalize_priorities(test_input);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, NormalizationEmpty)
{
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities{
        {"dir1", 1}, {"dir2", 2}, {"dir3", 3}};
    std::vector<std::pair<std::filesystem::path, float>> correct;
    std::vector<std::pair<std::filesystem::path, int>> test_input;
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, float>> result = testable.normalize_priorities(test_input);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, PickDirectoryPriorities1)
{
    std::vector<std::pair<std::filesystem::path, float>> normalized_priorities{
        {"dir1", 0.51}, {"dir2", 0.55}, {"dir3", 0.75}, {"dir4", 1.0}};
    std::filesystem::path correct{"dir1"};
    std::vector<std::pair<std::filesystem::path, int>> input_directories;
    WeightedStrategy testable{input_directories};
    std::filesystem::path result = testable.pick_directory(normalized_priorities, true);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, PickDirectoryPriorities2)
{
    std::vector<std::pair<std::filesystem::path, float>> normalized_priorities{
        {"dir1", 0.15}, {"dir2", 0.25}, {"dir3", 0.6}, {"dir4", 1.0}};
    std::filesystem::path correct{"dir3"};
    std::vector<std::pair<std::filesystem::path, int>> input_directories;
    WeightedStrategy testable{input_directories};
    std::filesystem::path result = testable.pick_directory(normalized_priorities, true);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, PickDirectoryEmptyPriorities)
{
    std::vector<std::pair<std::filesystem::path, float>> normalized_priorities;
    std::filesystem::path correct;
    std::vector<std::pair<std::filesystem::path, int>> input_directories;
    WeightedStrategy testable{input_directories};
    std::filesystem::path result = testable.pick_directory(normalized_priorities, true);
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, ReturnsAllFiles)
{
    std::vector<std::filesystem::path> correct1 = {
        "../test/resources/dir_tests/test_dir3/test_file1.txt",
        "../test/resources/dir_tests/test_dir3/test_file2.txt"};
    std::vector<std::filesystem::path> correct2{
        "../test/resources/dir_tests/test_dir3/subdir2/3file.txt",
        "../test/resources/dir_tests/test_dir3/subdir2/2file.txt",
        "../test/resources/dir_tests/test_dir3/subdir2/1file.txt"};
    std::vector<std::filesystem::path> correct3{
        "../test/resources/dir_tests/test_dir3/subdir1/2file.txt",
        "../test/resources/dir_tests/test_dir3/subdir1/1file.txt"};
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities{
        {"subdir2", 5}};
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::filesystem::path> result = testable.execute(Directory("../test/resources/dir_tests/test_dir3"));

    // result should be the files in one of the three vectors
    ASSERT_TRUE((result == correct1) || (result == correct2) || (result == correct3));
}

TEST(WeightedStrategyTests, ConfirmProportions)
{
    std::vector<std::filesystem::path> correct1 = {
        "../test/resources/dir_tests/test_dir3/test_file1.txt",
        "../test/resources/dir_tests/test_dir3/test_file2.txt"};
    std::vector<std::filesystem::path> correct2{
        "../test/resources/dir_tests/test_dir3/subdir2/3file.txt",
        "../test/resources/dir_tests/test_dir3/subdir2/2file.txt",
        "../test/resources/dir_tests/test_dir3/subdir2/1file.txt"};
    std::vector<std::filesystem::path> correct3{
        "../test/resources/dir_tests/test_dir3/subdir1/2file.txt",
        "../test/resources/dir_tests/test_dir3/subdir1/1file.txt"};
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities{
        {"test_dir3", 7}, {"subdir2", 2}};
    WeightedStrategy testable{input_dir_priorities};
    // results per directory
    std::vector<std::filesystem::path> result_test_dir3;
    std::vector<std::filesystem::path> result_subdir1;
    std::vector<std::filesystem::path> result_subdir2;
    for (int i = 0; i < 1000; i++)
    {
        std::vector<std::filesystem::path> result = testable.execute(Directory("../test/resources/dir_tests/test_dir3"));
        std::string directory = result[0].parent_path().filename().string();
        if (directory == "test_dir3")
        {
            result_test_dir3.push_back(directory);
        }
        else if (directory == "subdir1")
        {
            result_subdir1.push_back(directory);
        }
        else if (directory == "subdir2")
        {
            result_subdir2.push_back(directory);
        }
    }
    ASSERT_TRUE((result_test_dir3.size() <= 800) && (result_test_dir3.size() >= 600));
    ASSERT_TRUE((result_subdir2.size() <= 300) && (result_subdir2.size() >= 100));
    ASSERT_TRUE((result_subdir1.size() <= 200) && (result_subdir1.size() > 0));
}

TEST(WeightedStrategyTests, RecursionWorks)
{
    std::vector<std::filesystem::path> correct = {
        "../test/resources/dir_tests/file3.jpeg",
        "../test/resources/dir_tests/file2.png",
        "../test/resources/dir_tests/file1.txt",
        "../test/resources/dir_tests/file4.txt",
        "../test/resources/dir_tests/test_dir3/test_file1.txt",
        "../test/resources/dir_tests/test_dir3/test_file2.txt",
        "../test/resources/dir_tests/test_dir3/subdir2/3file.txt",
        "../test/resources/dir_tests/test_dir3/subdir2/2file.txt",
        "../test/resources/dir_tests/test_dir3/subdir2/1file.txt",
        "../test/resources/dir_tests/test_dir3/subdir1/2file.txt",
        "../test/resources/dir_tests/test_dir3/subdir1/1file.txt",
        "../test/resources/dir_tests/test_dir1/somea.png",
        "../test/resources/dir_tests/test_dir1/somec.png",
        "../test/resources/dir_tests/test_dir1/someb.png",
        "../test/resources/dir_tests/test_dir2/random3.png",
        "../test/resources/dir_tests/test_dir2/random2.png",
        "../test/resources/dir_tests/test_dir2/random4.png",
        "../test/resources/dir_tests/test_dir2/random1.png"};
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities;
    WeightedStrategy testable{input_dir_priorities};
    int number_of_empty_dir_hits = 0;
    for (int i = 0; i < 10; i++) // ensure we don't hit "empty_dir" accidentally
    {
        std::vector<std::filesystem::path> result = testable.execute(Directory("../test/resources/dir_tests"));
        if (!result.empty())
        {
            ASSERT_TRUE(std::find(correct.begin(), correct.end(), result[0]) != correct.end());
        }
        else
        {
            number_of_empty_dir_hits++;
        }
    }
    // Seems pretty improbable to hit empty_dir 10 times in a row, eh?
    ASSERT_TRUE(number_of_empty_dir_hits < 10);
}

TEST(WeightedStrategyTests, ReturnsEmpty)
{
    std::vector<std::filesystem::path> correct;
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities;
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::filesystem::path> result = testable.execute(Directory("../test/resources/dir_tests/test_dir2/empty_dir"));
    ASSERT_TRUE(result == correct);
}