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

TEST(ChangeCommandTests, ReturnsSeconds)
{
    std::vector<std::pair<std::string, int>> change_seconds_vector{{"dir1", 10}, {"dir2", 20}, {"exist", 5}};
    ChangeCommand testable{"gsettings set org.gnome.desktop.background picture-uri ",
                           "/this/path/does/not/exist/1 (2).jpg",
                           change_seconds_vector,
                           30};
    testable.execute();
    ChangeParameters result = testable.get_change();
    ASSERT_EQ(5, result.change_seconds);
}

TEST(ChangeCommandTests, ReturnsSecondsParent)
{
    std::vector<std::pair<std::string, int>> change_seconds_vector{{"dir1", 10}, {"dir2", 20}, {"not", 5}};
    ChangeCommand testable{"gsettings set org.gnome.desktop.background picture-uri ",
                           "/this/path/does/not/exist/1 (2).jpg",
                           change_seconds_vector,
                           30};
    testable.execute();
    ChangeParameters result = testable.get_change();
    ASSERT_EQ(5, result.change_seconds);
}

TEST(ChangeCommandTests, ReturnsSecondsClosestParent)
{
    std::vector<std::pair<std::string, int>> change_seconds_vector{{"dir1", 10}, {"not", 20}, {"does", 5}};
    ChangeCommand testable{"gsettings set org.gnome.desktop.background picture-uri ",
                           "/this/path/does/not/exist/1 (2).jpg",
                           change_seconds_vector,
                           30};
    testable.execute();
    ChangeParameters result = testable.get_change();
    ASSERT_EQ(20, result.change_seconds);
}

TEST(ChangeCommandTests, ReturnsSecondsDefault)
{
    std::vector<std::pair<std::string, int>> change_seconds_vector{{"dir1", 10}, {"dir2", 20}, {"dir3", 5}};
    ChangeCommand testable{"gsettings set org.gnome.desktop.background picture-uri ",
                           "/this/path/does/not/exist/1 (2).jpg",
                           change_seconds_vector,
                           30};
    testable.execute();
    ChangeParameters result = testable.get_change();
    ASSERT_EQ(30, result.change_seconds);
}