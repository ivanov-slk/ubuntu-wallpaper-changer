#include "../src/systemcommand.cpp"
#include <gtest/gtest.h>

TEST(SystemCommandTests, ReturnsEmpty)
{
    SystemCommand testable;
    testable.execute();
    ASSERT_EQ("", testable.get_command_line());
}

TEST(SystemCommandTests, ReturnsMock)
{
    SystemCommand testable{"execute ", "this"};
    testable.execute();
    // Consider refactoring this in SystemCommand - does not generalize.
    ASSERT_EQ("execute this", testable.get_command_line());
}

TEST(SystemCommandTests, ReturnsCommand)
{
    SystemCommand testable{"gsettings set org.gnome.desktop.background picture-uri \"file://",
                           "/this/path/does/not/exist/1 (2).jpg\""};
    testable.execute();
    ASSERT_EQ("gsettings set org.gnome.desktop.background picture-uri \"file:///this/path/does/not/exist/1 (2).jpg\"", testable.get_command_line());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
