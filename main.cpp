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
    AppFacade wallpaper_changer{"./config.cfg"};
    try
    {
        wallpaper_changer.initialize();
        wallpaper_changer.start();
    }
    catch (const std::exception &exc)
    {
        wallpaper_changer.log("=============== Exception caught. ===============");
        wallpaper_changer.log(exc.what());
        throw;
    }
    catch (...)
    {
        wallpaper_changer.log("========== Unknown exception caught. ==========");
        throw;
    }
    return 0;
}