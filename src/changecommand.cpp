#pragma once
#include <filesystem>
#include <vector>
#include <map>
#include "commandinterface.h"

class ChangeCommand : public CommandInterface
{
private:
    std::string filename;
    std::string command_template = "gsettings set org.gnome.desktop.background picture-uri ";
    std::string command_template_options = "gsettings set org.gnome.desktop.background picture-options ";
    std::string command_line;
    std::vector<std::pair<std::string, int>> dir_seconds;
    int default_seconds;
    std::map<std::string, std::string> directory_pic_options;
    ChangeParameters change_params;

    int calculate_seconds(std::string check_path)
    {
        if (!dir_seconds.empty())
        {
            std::filesystem::path check_path{filename};
            while (check_path != check_path.root_path())
            {
                std::string parent_dir = check_path.filename();
                for (const std::pair<std::string, int> &dir_pair : dir_seconds)
                {
                    if (parent_dir == dir_pair.first)
                    {
                        return dir_pair.second;
                    }
                }
                check_path = check_path.parent_path();
            }
        }
        return default_seconds;
    }

public:
    ChangeCommand() = default;
    ChangeCommand(const std::string &filename) : filename(filename){};
    ChangeCommand(const std::string &filename,
                  const std::vector<std::pair<std::string, int>> dir_seconds,
                  int default_seconds,
                  std::map<std::string, std::string> dir_pic_options) : filename(filename),
                                                                        dir_seconds(dir_seconds),
                                                                        default_seconds(default_seconds),
                                                                        directory_pic_options(dir_pic_options){};
    void execute() override
    {
        // get the command line
        command_line = command_template + "\"file://" + filename + "\"";
        change_params.command_line = command_line;

        // get the change seconds
        change_params.change_seconds = calculate_seconds(filename);
    };
    ChangeParameters get_change() { return change_params; };
};