#include <iostream>
#include <unistd.h>
#include <string>
#include <csignal>

#include <appfacade.cpp>

using namespace std;

void signal_handler(int signal)
// Useful (and used) only for SIGINT and SIGTERM. If other signals need
// to be caught, std::exit might not be the best course of action.
{
    cout << "Signal caught: " << signal << ". Exiting..." << '\n';
    exit(signal);
}

int main()
{
    // ChangeCommand system_command{"gsettings set org.gnome.desktop.background picture-uri file://",
    //                              "/home/slav/Изображения/Wallpapers/1 (2).jpg"};
    // system_command.execute();
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    AppFacade wallpaper_changer{"test/resources/real_config.cfg"};
    while (true)
    {
        string command_line = wallpaper_changer.change_wallpaper();
        cout << command_line << '\n';
        system(command_line.c_str());
        sleep(5);
    }
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