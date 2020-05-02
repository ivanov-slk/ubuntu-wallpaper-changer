#include "../src/systemcommand.cpp"
#include <gtest/gtest.h>

TEST(SystemCommandTests, ReturnsEmpty)
{
    SystemCommand testable;
    testable.execute();
    ASSERT_EQ(""s, testable.get_command_line());
}

TEST(SystemCommandTests, ReturnsCommand)
{
    SystemCommand testable{"execute ", "this"};
    testable.execute();
    // Consider refactoring this in SystemCommand - does not generalize.
    ASSERT_EQ("execute file://this"s, testable.get_command_line());
}

TEST(SystemCommandTests, ReturnsCommand)
{
    SystemCommand testable{"gsettings set org.gnome.desktop.background picture-uri  ",
                           "/home/slav/Изображения/Wallpapers/1 (2).jpg"};
    testable.execute();
    ASSERT_EQ("gsettings set org.gnome.desktop.background picture-uri file:///home/slav/Изображения/Wallpapers/1 (2).jpg"s, testable.get_command_line());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
