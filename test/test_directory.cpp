#include <gtest/gtest.h>
#include "../src/directory.cpp"

TEST(DirectoryTests, ReturnsRootPath)
{
    Directory testable{"../test/resources/dir_tests"}; // assumes we are in build/
    std::filesystem::path result = testable.get_root_path();
    std::filesystem::path correct = std::filesystem::path("../test/resources/dir_tests");
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsDirectories)
{
    Directory testable{"../test/resources/dir_tests"}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_subdirs();
    std::vector<std::filesystem::path> correct{
        /** 
         * Filesystem iterator returns non-sorted (alphabetically) values.
         * Here, it is not a problem, since alphabetical order does not
         * matter, but consider sorting if needed.
         */
        "../test/resources/dir_tests/test_dir2",
        "../test/resources/dir_tests/test_dir1",
        "../test/resources/dir_tests/test_dir3"};
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsDirectoriesWithExclusions)
{
    std::vector<std::string> exclusions{"test_dir3"};
    std::vector<std::string> allowed_extensions;
    Directory testable{"../test/resources/dir_tests", exclusions, allowed_extensions}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_subdirs();
    std::vector<std::filesystem::path> correct{
        /** 
         * Filesystem iterator returns non-sorted (alphabetically) values.
         * Here, it is not a problem, since alphabetical order does not
         * matter, but consider sorting if needed.
         */
        "../test/resources/dir_tests/test_dir2",
        "../test/resources/dir_tests/test_dir1"};
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsDirectoriesWithExclusionsEmpty)
{
    std::vector<std::string> exclusions{"test_dir3", "test_dir1", "test_dir2"};
    std::vector<std::string> allowed_extensions;
    Directory testable{"../test/resources/dir_tests", exclusions, allowed_extensions}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_subdirs();
    std::vector<std::filesystem::path> correct;
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsFiles)
{
    Directory testable{"../test/resources/dir_tests"}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_files();
    std::vector<std::filesystem::path> correct{
        /** 
         * Filesystem iterator returns non-sorted (alphabetically) values.
         * Here, it is not a problem, since alphabetical order does not
         * matter, but consider sorting if needed.
         */
        "../test/resources/dir_tests/file3.jpeg",
        "../test/resources/dir_tests/file2.png",
        "../test/resources/dir_tests/file1.txt",
        "../test/resources/dir_tests/file4.txt"};
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsFilesAllowedExtensions)
{
    std::vector<std::string> allowed_extensions{".png", ".jpeg"};
    std::vector<std::string> exclusions;
    Directory testable{"../test/resources/dir_tests", exclusions, allowed_extensions}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_files();
    std::vector<std::filesystem::path> correct{
        /** 
         * Filesystem iterator returns non-sorted (alphabetically) values.
         * Here, it is not a problem, since alphabetical order does not
         * matter, but consider sorting if needed.
         */
        "../test/resources/dir_tests/file3.jpeg",
        "../test/resources/dir_tests/file2.png",
    };
    ASSERT_TRUE(result == correct);
}

TEST(DirectoryTests, ReturnsFilesAllowedExtensionsEmpty)
{
    std::vector<std::string> allowed_extensions{".fake", ".none"};
    std::vector<std::string> exclusions;
    Directory testable{"../test/resources/dir_tests", exclusions, allowed_extensions}; // assumes we are in build/
    std::vector<std::filesystem::path> result = testable.get_files();
    std::vector<std::filesystem::path> correct;
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