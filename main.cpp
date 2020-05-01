#include <iostream>
#include <unistd.h>
#include <string>

#include <check_tests.cpp>

using namespace std;
int main()
{
    string template_command = "gsettings set org.gnome.desktop.background picture-uri file://";
    string base_directory = "/home/slav/Изображения/Бележки/O'Pyle, J., Karynch, M. - Find out anything from anyone, anytime/";

    string command;

    for (int i = 0; i < 100; i++)
    {
        command = template_command + base_directory + to_string(i) + ".png\"";
        cout << testable() << '\n';
        // system(command.c_str());
        // sleep(5);
    }
    return 0;
}