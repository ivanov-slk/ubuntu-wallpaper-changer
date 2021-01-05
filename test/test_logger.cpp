#include <gtest/gtest.h>
#include "../src/logger.cpp"

TEST(LoggerTests, LogsCorrectly)
{
    { // in a separate scope to allow for the output file to be closed
        // initialize logger
        Logger testable{"../test/resources/test_log.txt"};

        // write a couple of lines
        testable.log("this is line 1");
        testable.log("this is line 2");
        testable.log("this is line 3");
    }

    // load the correct output
    std::vector<std::string> correct;
    std::string correct_line;
    std::ifstream correct_log{"../test/resources/correct_log.txt"};
    if (correct_log.is_open())
    {
        while (std::getline(correct_log, correct_line))
        {
            correct.push_back(correct_line);
        }
    }
    // load the test output
    std::vector<std::string> test;
    std::string test_line;
    std::ifstream test_log{"../test/resources/test_log.txt"};
    if (test_log.is_open())
    {
        while (std::getline(test_log, test_line))
        {
            test.push_back(test_line);
        }
    }

    ASSERT_TRUE(test == correct);
}