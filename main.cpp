#include <iostream>
#include <unistd.h>
#include <string>

#include <changecommand.cpp>

using namespace std;

int main()
{
    ChangeCommand system_command{"gsettings set org.gnome.desktop.background picture-uri file://",
                                 "/home/slav/Изображения/Wallpapers/1 (2).jpg"};
    system_command.execute();
    cout << system_command.get_command_line() << '\n';
    // string template_command = "gsettings set org.gnome.desktop.background picture-uri file://";
    // string base_directory = "/home/slav/Изображения/Бележки/O'Pyle, J., Karynch, M. - Find out anything from anyone, anytime/";

    // string command;
    // for (int i = 0; i < 100; i++)
    // {
    //     command = template_command + base_directory + to_string(i) + ".png\"";
    //     cout << command << '\n';
    //     // system(command.c_str());
    //     // sleep(5);
    // }
    return 0;
}