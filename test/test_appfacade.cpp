#include <gtest/gtest.h>
#include "../src/appfacade.cpp"

TEST(AppFacadeTests, ReturnCorrectCommand)
{
    std::vector<std::string> correct_commands{
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random1.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random2.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random3.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random4.png\""};

    AppFacade testable{"../test/resources/test_config.cfg"};
    testable.initialize();
    for (int i = 0; i < 3; i++) // kind of redundant
    {
        ChangeParameters result = testable.change_wallpaper();
        ASSERT_TRUE(std::find(correct_commands.begin(), correct_commands.end(), result.command_line) != correct_commands.end());
    }
}

TEST(AppFacadeTests, ReturnCorrectCommandExclusions)
{
    std::vector<std::string> correct_commands{
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random1.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random2.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random3.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random4.png\""};

    AppFacade testable{"../test/resources/appfacade_exclusions_config.cfg"};
    testable.initialize();
    for (int i = 0; i < 3; i++) // kind of redundant
    {
        ChangeParameters result = testable.change_wallpaper();
        ASSERT_TRUE(std::find(correct_commands.begin(), correct_commands.end(), result.command_line) != correct_commands.end());
    }
}

TEST(AppFacadeTests, ReturnCorrectCommandEmptyNoAllowedExtensions)
{
    std::vector<std::string> correct_commands{
        "gsettings set org.gnome.desktop.background picture-uri \"file://\"",
    };

    AppFacade testable{"../test/resources/allowed_extensions_config.cfg"};
    testable.initialize();
    for (int i = 0; i < 3; i++) // kind of redundant
    {
        ChangeParameters result = testable.change_wallpaper();
        ASSERT_TRUE(std::find(correct_commands.begin(), correct_commands.end(), result.command_line) != correct_commands.end());
    }
}

TEST(AppFacadeTests, ReturnCorrectCommandEmpty)
{
    std::vector<std::string> correct_commands{
        "gsettings set org.gnome.desktop.background picture-uri \"file://\"",
    };

    AppFacade testable{"../test/resources/empty_config.cfg"};
    testable.initialize();
    for (int i = 0; i < 3; i++)
    {
        ChangeParameters result = testable.change_wallpaper();
        ASSERT_TRUE(std::find(correct_commands.begin(), correct_commands.end(), result.command_line) != correct_commands.end());
    }
}

TEST(AppFacadeTests, ReturnCorrectCommandDefaultSeconds)
{
    AppFacade testable{"../test/resources/empty_config.cfg"};
    testable.initialize();
    for (int i = 0; i < 3; i++)
    {
        ChangeParameters result = testable.change_wallpaper();
        ASSERT_EQ(30, result.change_seconds);
    }
}

TEST(AppFacadeTests, ReturnCorrectCommandClosestSecondsParent)
{
    AppFacade testable{"../test/resources/appfacade_seconds_config.cfg"};
    testable.initialize();
    for (int i = 0; i < 3; i++)
    {
        ChangeParameters result = testable.change_wallpaper();
        ASSERT_EQ(20, result.change_seconds);
    }
}

TEST(AppFacadeTests, ReturnCorrectCommandPictureOptions)
{
    AppFacade testable{"../test/resources/picture_options_config.cfg"};
    testable.initialize();
    ChangeParameters result = testable.change_wallpaper();
    std::cout << result.command_line_options << '\n';
    ASSERT_EQ("gsettings set org.gnome.desktop.background picture-options scaled", result.command_line_options);
}

TEST(AppFacadeTests, LogsCorrectly)
{
    { // in a separate scope to allow for the output file to be closed
        // initialize logger
        AppFacade testable{"../test/resources/test_config.cfg"};
        testable.initialize();

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
    std::ifstream test_log{"./log.txt"};
    if (test_log.is_open())
    {
        while (std::getline(test_log, test_line))
        {
            test.push_back(test_line);
        }
    }

    ASSERT_TRUE(test == correct);
}

TEST(AppFacadeTests, WeightedStrategyReturnsCorrect)
{
    std::vector<std::string> correct_commands{
        "gsettings set org.gnome.desktop.background picture-uri \"file://\"",
    };

    AppFacade testable{"../test/resources/empty_weighted_config.cfg"};
    testable.initialize();
    for (int i = 0; i < 3; i++)
    {
        ChangeParameters result = testable.change_wallpaper();
        ASSERT_TRUE(std::find(correct_commands.begin(), correct_commands.end(), result.command_line) != correct_commands.end());
    }
}
