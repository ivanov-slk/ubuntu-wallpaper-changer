#include <string>

#include "changecommand.cpp"
#include "configurationparser.cpp"
#include "filepicker.cpp"

/**
 * Acts as sort of a "facade" for the other classes. Provides a simple
 * API for starting the whole "app". 
 */
class AppFacade
{
private:
    const std::string config_path;

public:
    AppFacade(const std::string &config_path) : config_path(config_path){};

    /**
     * Organizes and executes the process of generating command line for 
     * changing wallpapers, using all other classes.
     */
    std::string change_wallpaper(){
        // parse configuration

        // set up file picker

        // set up command

        // execute command (should the actual system() call be here or in main()?)
    };
};