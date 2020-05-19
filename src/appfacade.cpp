#include <unistd.h>

#include "changecommand.cpp"
#include "configurationparser.cpp"
#include "filepicker.cpp"
#include "strategycontext.cpp"
#include "uniformstrategy.cpp"
#include "weightedstrategy.cpp"
#include "logger.cpp"

/**
 * Acts as sort of a "facade" for the other classes. Provides a simple
 * API for starting the whole "app". 
 */
class AppFacade
{
private:
    std::string config_path;
    FolderConfiguration config;
    StrategyContext context;
    Logger logger{"./log.txt"};
    std::unique_ptr<StrategyInterface> strategy;

public:
    AppFacade(const std::string &config_path) : config_path(config_path)
    {
        // parse configuration
        ConfigurationParser parser{config_path};
        config = parser.create_configuration();

        // set up strategy (uniform strategy is default, although configuration parser throws on invalid policy)
        if ((config.policy == "uniform") || config.policy.empty())
        {
            strategy = std::make_unique<UniformStrategy>();
            context.set_strategy(std::move(strategy));
        }
        else
        {
        std:
            strategy = std::make_unique<WeightedStrategy>(config.directory_priorities);
            context.set_strategy(std::move(strategy));
        }
    };

    /**
     * Execute the strategy-related directory traversal.
     * @param Folderconfiguration - the parsed configuration.
     * 
     * @returns std::vector<std::filesystem::path> - a (potentially empty) vector of paths
     */
    std::vector<std::filesystem::path> get_dirfiles()
    {
        Directory root_dir{config.path, config.directory_exclusions, config.file_allowed_extensions};
        std::vector<std::filesystem::path> files_vector;
        files_vector = context.execute_strategy(root_dir);
        return files_vector;
    }

    /**
     * Organizes and executes the process of generating command line for 
     * changing wallpapers, using all other classes.
     * 
     * @returns std::string 
     */
    ChangeParameters change_wallpaper()
    {
        // traverse directories and get files
        std::vector<std::filesystem::path> files_vector;
        files_vector = get_dirfiles();

        // set up file picker
        FilePicker picker{files_vector};
        std::string wallpaper_path = picker.pick_random_path().string();

        // set up command
        ChangeCommand command{"gsettings set org.gnome.desktop.background picture-uri ",
                              wallpaper_path,
                              config.directory_seconds,
                              config.seconds_before_change};
        command.execute();
        ChangeParameters params = command.get_change();
        return params;
    }

    /**
     * Starts the application.
     */
    void start()
    {
        while (true)
        {
            ChangeParameters params = change_wallpaper();
            logger.log(params.command_line);
            system(params.command_line.c_str());
            sleep(params.change_seconds);
        }
    }

    /**
     * Logs the executed command line.
     * 
     * @param const std::string& command_line
     */
    void log(const std::string &command_line)
    {
        logger.log(command_line);
    }
};