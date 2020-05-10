#include <gtest/gtest.h>
#include "../src/appfacade.cpp"

TEST(AppFacadeTests, ReturnCorrectCommand)
{
    std::vector<std::string> correct_commands = {
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random1.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random2.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random3.png\"",
        "gsettings set org.gnome.desktop.background picture-uri \"file://../test/resources/dir_tests/test_dir2/random4.png\""};

    AppFacade testable{"../test/resources/test_config.cfg"};
    for (int i = 0; i < 3; i++)
    {
        std::string result = testable.change_wallpaper();
        ASSERT_TRUE(std::find(correct_commands.begin(), correct_commands.end(), result) != correct_commands.end());
    }
}

TEST(AppFacadeTests, ReturnCorrectCommandEmpty)
{
    std::vector<std::string> correct_commands = {
        "gsettings set org.gnome.desktop.background picture-uri \"file://\"",
    };

    AppFacade testable{"../test/resources/empty_config.cfg"};
    for (int i = 0; i < 3; i++)
    {
        std::string result = testable.change_wallpaper();
        ASSERT_TRUE(std::find(correct_commands.begin(), correct_commands.end(), result) != correct_commands.end());
    }
}