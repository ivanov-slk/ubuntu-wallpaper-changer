#include <gtest/gtest.h>
#include "../src/uniformstrategy.cpp"
#include "../src/weightedstrategy.cpp"
#include "../src/strategycontext.cpp"

TEST(StrategyContextTests, UniformReturnsAllFiles)
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
    StrategyContext context;
    auto strategy = std::make_unique<UniformStrategy>();
    Directory test_dir{"../test/resources/dir_tests"};
    context.set_strategy(std::move(strategy));
    std::vector<std::filesystem::path> result = context.execute_strategy(test_dir);
    std::sort(result.begin(), result.end(), std::greater<std::filesystem::path>());
    std::sort(correct.begin(), correct.end(), std::greater<std::filesystem::path>()); // lazyness...
    ASSERT_TRUE(result == correct);
}

TEST(StrategyContextTests, UniformReturnsEmpty)
{
    std::vector<std::filesystem::path> correct;
    StrategyContext context;
    auto strategy = std::make_unique<UniformStrategy>();
    context.set_strategy(std::move(strategy));
    std::vector<std::filesystem::path> result = context.execute_strategy(Directory{"../test/resources/dir_tests/test_dir2/empty_dir"});
    ASSERT_TRUE(result == correct);
}

TEST(StrategyContextTests, WeightedReturnsAllFiles)
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
    StrategyContext context;
    auto strategy = std::make_unique<WeightedStrategy>(input_dir_priorities);
    context.set_strategy(std::move(strategy));
    std::vector<std::filesystem::path> result = context.execute_strategy(Directory("../test/resources/dir_tests/test_dir3"));

    // result should be the files in one of the three vectors
    std::sort(result.begin(), result.end(), std::greater<std::filesystem::path>());
    std::sort(correct1.begin(), correct1.end(), std::greater<std::filesystem::path>()); // lazyness...
    std::sort(correct2.begin(), correct2.end(), std::greater<std::filesystem::path>());
    std::sort(correct3.begin(), correct3.end(), std::greater<std::filesystem::path>());
    ASSERT_TRUE((result == correct1) || (result == correct2) || (result == correct3));
}

TEST(StrategyContextTests, WeightedReturnsEmpty)
{
    std::vector<std::filesystem::path> correct;
    StrategyContext context;
    std::vector<std::pair<std::filesystem::path, int>> input_dir_priorities;
    auto strategy = std::make_unique<WeightedStrategy>(input_dir_priorities);
    context.set_strategy(std::move(strategy));
    std::vector<std::filesystem::path> result = context.execute_strategy(Directory{"../test/resources/dir_tests/test_dir2/empty_dir"});
    ASSERT_TRUE(result == correct);
}