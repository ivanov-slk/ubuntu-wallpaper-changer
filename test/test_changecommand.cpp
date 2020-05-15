#include <gtest/gtest.h>
#include "../src/changecommand.cpp"

TEST(ChangeCommandTests, ReturnsEmpty)
{
    ChangeCommand testable;
    testable.execute();
    ChangeParameters result = testable.get_change();
    ASSERT_EQ("\"file://\"", result.command_line);
}

TEST(ChangeCommandTests, ReturnsCommand1)
{
    ChangeCommand testable{"set ", "path"};
    testable.execute();
    ChangeParameters result = testable.get_change();
    ASSERT_EQ("set \"file://path\"", result.command_line);
}

TEST(ChangeCommandTests, ReturnsCommand2)
{
    ChangeCommand testable{"gsettings set org.gnome.desktop.background picture-uri ",
                           "/this/path/does/not/exist/1 (2).jpg"};
    testable.execute();
    ChangeParameters result = testable.get_change();
    ASSERT_EQ("gsettings set org.gnome.desktop.background picture-uri \"file:///this/path/does/not/exist/1 (2).jpg\"", result.command_line);
}
