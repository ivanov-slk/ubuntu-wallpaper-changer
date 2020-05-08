#include <gtest/gtest.h>
#include "../src/uniformstrategy.cpp"
#include "../src/strategycontext.cpp"

TEST(StrategyContextTests, UniformReturnsAllFiles)
{
    std::vector<std::filesystem::path> correct = {
        "../test/resources/dir_tests/file3.txt",
        "../test/resources/dir_tests/file1.txt",
        "../test/resources/dir_tests/file2.txt",
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
    context.set_strategy(new UniformStrategy);
    std::vector<std::filesystem::path> result = context.execute_strategy(Directory{"../test/resources/dir_tests"});
    ASSERT_TRUE(result == correct);
}

TEST(StrategyContextTests, UniformReturnsEmpty)
{
    std::vector<std::filesystem::path> correct;
    StrategyContext context;
    context.set_strategy(new UniformStrategy);
    std::vector<std::filesystem::path> result = context.execute_strategy(Directory{"../test/resources/dir_tests/test_dir2/empty_dir"});
    ASSERT_TRUE(result == correct);
}