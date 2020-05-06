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
    std::string change_wallpaper()
    {
        // parse configuration
        ConfigurationParser parser{config_path};
        FolderConfiguration config = parser.create_configuration();
        // set up folder handler

        // set up file picker
        FilePicker picker{std::filesystem::path(config.path)};
        string wallpaper_path = picker.pick_random_path().string();
        // set up command
        ChangeCommand command{"gsettings set org.gnome.desktop.background picture-uri \"file://",
                              wallpaper_path};
        command.execute();
        string command_line = command.get_command_line();
        // execute command (should the actual system() call be here or in main()?)
        return command_line;
    };
};