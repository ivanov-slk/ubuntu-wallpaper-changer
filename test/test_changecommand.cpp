#include <gtest/gtest.h>
#include "../src/changecommand.cpp"

TEST(ChangeCommandTests, ReturnsEmpty)
{
    ChangeCommand testable;
    testable.execute();
    ASSERT_EQ("\"file://\"", testable.get_command_line());
}

TEST(ChangeCommandTests, ReturnsCommand1)
{
    ChangeCommand testable{"set ", "path"};
    testable.execute();
    ASSERT_EQ("set \"file://path\"", testable.get_command_line());
}

TEST(ChangeCommandTests, ReturnsCommand2)
{
    ChangeCommand testable{"gsettings set org.gnome.desktop.background picture-uri ",
                           "/this/path/does/not/exist/1 (2).jpg"};
    testable.execute();
    ASSERT_EQ("gsettings set org.gnome.desktop.background picture-uri \"file:///this/path/does/not/exist/1 (2).jpg\"", testable.get_command_line());
}
