#include <gtest/gtest.h>

#include "../src/uniformstrategy.cpp"

TEST(UniformStrategyTests, ReturnsAllFiles) {
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
  UniformStrategy testable;
  std::vector<std::filesystem::path> result =
      testable.execute(Directory("../test/resources/dir_tests"));
  std::sort(result.begin(), result.end(),
            std::greater<std::filesystem::path>());
  std::sort(correct.begin(), correct.end(),
            std::greater<std::filesystem::path>());  // lazyness...
  ASSERT_TRUE(result == correct);
}

TEST(UniformStrategyTests, ReturnsCache) {
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
  UniformStrategy testable;
  std::vector<std::filesystem::path> result =
      testable.execute(Directory("../test/resources/dir_tests"));
  std::sort(result.begin(), result.end(),
            std::greater<std::filesystem::path>());
  std::vector<std::filesystem::path> cache =
      testable.execute(Directory("../test/resources/dir_tests"));
  std::sort(cache.begin(), cache.end(), std::greater<std::filesystem::path>());
  std::sort(correct.begin(), correct.end(),
            std::greater<std::filesystem::path>());  // lazyness...
  ASSERT_TRUE(result == cache);
  ASSERT_TRUE(cache == correct);
  ASSERT_TRUE(result == correct);
}

TEST(UniformStrategyTests, ReturnsEmpty) {
  std::vector<std::filesystem::path> correct;
  UniformStrategy testable;
  std::vector<std::filesystem::path> result = testable.execute(
      Directory("../test/resources/dir_tests/test_dir2/empty_dir"));
  ASSERT_TRUE(result == correct);
}