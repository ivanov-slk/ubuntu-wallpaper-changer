#include <string>

#include "changecommand.cpp"
#include "configurationparser.cpp"
#include "filepicker.cpp"
#include "strategycontext.cpp"
#include "uniformstrategy.cpp"

/**
 * Acts as sort of a "facade" for the other classes. Provides a simple
 * API for starting the whole "app". 
 */
class AppFacade
{
private:
    std::string config_path;

public:
    AppFacade(const std::string &config_path) : config_path(config_path){};

    std::vector<std::filesystem::path> get_dirfiles(const FolderConfiguration &config)
    {
        // set up strategy and get file vector
        StrategyContext context;
        auto strategy = std::make_unique<UniformStrategy>();
        Directory root_dir{config.path};
        std::vector<std::filesystem::path> files_vector;
        context.set_strategy(std::move(strategy));
        files_vector = context.execute_strategy(root_dir);
        return files_vector;
    }

    /**
     * Organizes and executes the process of generating command line for 
     * changing wallpapers, using all other classes.
     */
    std::string change_wallpaper()
    {
        // parse configuration
        ConfigurationParser parser{config_path};
        FolderConfiguration config = parser.create_configuration();

        // traverse directories and get files
        std::vector<std::filesystem::path> files_vector;
        files_vector = get_dirfiles(config);
        for (auto &p : files_vector)
        {
            std::cout << p << '\n';
        }

        // set up file picker
        FilePicker picker{files_vector};
        string wallpaper_path = picker.pick_random_path().string();

        // set up command
        ChangeCommand command{"gsettings set org.gnome.desktop.background picture-uri ",
                              wallpaper_path};
        command.execute();
        string command_line = command.get_command_line();
        // execute command (should the actual system() call be here or in main()?)
        return command_line;
    }
};