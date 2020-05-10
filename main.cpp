#include <iostream>
#include <unistd.h>
#include <string>
#include <csignal>

#include <appfacade.cpp>

using namespace std;

void signal_handler(int signal)
// Useful (and used) only for SIGINT and SIGTERM. If other signals need
// to be caught, std::exit might not be the best course of action. (?)
{
    cout << "Signal caught: " << signal << ". Exiting..." << '\n';
    exit(signal);
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    AppFacade wallpaper_changer{"test/resources/real_config.cfg"};
    while (true)
    {
        string command_line = wallpaper_changer.change_wallpaper();
        cout << command_line << '\n';
        system(command_line.c_str());
        sleep(30);
    }
    return 0;
}