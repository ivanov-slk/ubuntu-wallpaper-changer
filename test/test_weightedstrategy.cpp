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
 * 3. execute():
 * - Due to randomness is hard to test. Test with
 * checking a few possible outcomes and assert that
 * the result is either of them.
 * - Another option: run 100 tests and assert that
 * the outcome proportion is similar to the expected.
 */

#include <gtest/gtest.h>
#include "../src/weightedstrategy.cpp"

TEST(WeightedStrategyTests, SubdirsOverlap)
{
    std::vector<std::pair<std::string, int>> input_dir_priorities{
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
    std::vector<std::pair<std::string, int>> input_dir_priorities{
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
    std::vector<std::pair<std::string, int>> input_dir_priorities;
    std::vector<std::filesystem::path> test_input{
        "other_dir1", "other_dir2", "other_dir3"};
    std::vector<std::pair<std::filesystem::path, int>> correct{
        {"other_dir1", 1}, {"other_dir2", 1}, {"other_dir3", 1}};
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, int>> result = testable.create_subdirs_with_priorities(test_input);
    for (auto const &test_pair : result)
    {
        std::cout << test_pair.first << " " << test_pair.second << '\n';
    }
    ASSERT_TRUE(result == correct);
}

TEST(WeightedStrategyTests, SubdirsSubdirsEmpty)
{
    std::vector<std::pair<std::string, int>> input_dir_priorities{
        {"dir1", 1}, {"dir2", 2}, {"dir3", 3}};
    std::vector<std::filesystem::path> test_input;
    std::vector<std::pair<std::filesystem::path, int>> correct;
    WeightedStrategy testable{input_dir_priorities};
    std::vector<std::pair<std::filesystem::path, int>> result = testable.create_subdirs_with_priorities(test_input);
    ASSERT_TRUE(result == correct);
}

// TEST(WeightedStrategyTests, ReturnsAllFiles)
// {
//     std::vector<std::filesystem::path> correct = {
//         "../test/resources/dir_tests/file3.jpeg",
//         "../test/resources/dir_tests/file2.png",
//         "../test/resources/dir_tests/file1.txt",
//         "../test/resources/dir_tests/file4.txt",
//         "../test/resources/dir_tests/test_dir3/test_file1.txt",
//         "../test/resources/dir_tests/test_dir3/test_file2.txt",
//         "../test/resources/dir_tests/test_dir3/subdir2/3file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir2/2file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir2/1file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir1/2file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir1/1file.txt",
//         "../test/resources/dir_tests/test_dir1/somea.png",
//         "../test/resources/dir_tests/test_dir1/somec.png",
//         "../test/resources/dir_tests/test_dir1/someb.png",
//         "../test/resources/dir_tests/test_dir2/random3.png",
//         "../test/resources/dir_tests/test_dir2/random2.png",
//         "../test/resources/dir_tests/test_dir2/random4.png",
//         "../test/resources/dir_tests/test_dir2/random1.png"};

//     std::vector<std::pair<std::string, int>> input_dir_priorities;
//     WeightedStrategy testable{input_dir_priorities};
//     std::vector<std::filesystem::path> result = testable.execute(Directory("../test/resources/dir_tests"));
//     ASSERT_TRUE(result == correct);
// }

// TEST(WeightedStrategyTests, ReturnsCache)
// {
//     std::vector<std::filesystem::path> correct = {
//         "../test/resources/dir_tests/file3.jpeg",
//         "../test/resources/dir_tests/file2.png",
//         "../test/resources/dir_tests/file1.txt",
//         "../test/resources/dir_tests/file4.txt",
//         "../test/resources/dir_tests/test_dir3/test_file1.txt",
//         "../test/resources/dir_tests/test_dir3/test_file2.txt",
//         "../test/resources/dir_tests/test_dir3/subdir2/3file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir2/2file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir2/1file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir1/2file.txt",
//         "../test/resources/dir_tests/test_dir3/subdir1/1file.txt",
//         "../test/resources/dir_tests/test_dir1/somea.png",
//         "../test/resources/dir_tests/test_dir1/somec.png",
//         "../test/resources/dir_tests/test_dir1/someb.png",
//         "../test/resources/dir_tests/test_dir2/random3.png",
//         "../test/resources/dir_tests/test_dir2/random2.png",
//         "../test/resources/dir_tests/test_dir2/random4.png",
//         "../test/resources/dir_tests/test_dir2/random1.png"};

//     std::vector<std::pair<std::string, int>> input_dir_priorities;
//     WeightedStrategy testable{input_dir_priorities};
//     std::vector<std::filesystem::path> result = testable.execute(Directory("../test/resources/dir_tests"));
//     std::vector<std::filesystem::path> cache = testable.execute(Directory("../test/resources/dir_tests"));
//     ASSERT_TRUE(result == cache);
//     ASSERT_TRUE(cache == correct);
//     ASSERT_TRUE(result == correct);
// }

// TEST(WeightedStrategyTests, ReturnsEmpty)
// {
//     std::vector<std::filesystem::path> correct;
//     std::vector<std::pair<std::string, int>> input_dir_priorities;
//     WeightedStrategy testable{input_dir_priorities};
//     std::vector<std::filesystem::path> result = testable.execute(Directory("../test/resources/dir_tests/test_dir2/empty_dir"));
//     ASSERT_TRUE(result == correct);
// }