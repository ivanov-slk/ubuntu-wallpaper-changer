#include <gtest/gtest.h>
#include "../src/directory.cpp"

TEST(DirectoryTests, ReturnsFiles)
{
    Directory testable{"../test/resources/dir_tests"}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_subdirs();
    std::vector<std::filesystem::path> correct{
        /** 
         * Filesystem iterator returns non-sorted (alphabetically) values.
         * Here, it is not a problem, since alphabetical order does not
         * matter, but consider sorting if needed.
         */
        "../test/resources/dir_tests/test_dir3",
        "../test/resources/dir_tests/test_dir1",
        "../test/resources/dir_tests/test_dir2"};
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsDirectories)
{
    Directory testable{"../test/resources/dir_tests"}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_files();
    std::vector<std::filesystem::path> correct{
        /** 
         * Filesystem iterator returns non-sorted (alphabetically) values.
         * Here, it is not a problem, since alphabetical order does not
         * matter, but consider sorting if needed.
         */
        "../test/resources/dir_tests/file3.txt",
        "../test/resources/dir_tests/file1.txt",
        "../test/resources/dir_tests/file2.txt",
        "../test/resources/dir_tests/file4.txt"};
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsEmptyNoFiles)
{
    Directory testable{"../test/resources/dir_tests/test_dir2/empty_dir"}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_files();
    std::vector<std::filesystem::path> correct;
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsEmptyNoDirs)
{
    Directory testable{"../test/resources/dir_tests/test_dir3/subdir2"}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_subdirs();
    std::vector<std::filesystem::path> correct;
    ASSERT_TRUE(result == correct);
}