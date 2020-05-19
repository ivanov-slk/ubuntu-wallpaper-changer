#pragma once
#include <filesystem>
#include <vector>
#include <iostream>
#include "commandinterface.h"

class ChangeCommand : public CommandInterface
{
private:
    std::string filename;
    std::string command_template;
    std::string command_line;
    std::vector<std::pair<std::string, int>> dir_seconds;
    int default_seconds;
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
    ChangeCommand(const std::string &command_template, const std::string &filename) : command_template(command_template), filename(filename){};
    ChangeCommand(const std::string &command_template,
                  const std::string &filename,
                  const std::vector<std::pair<std::string, int>> dir_seconds,
                  int default_seconds) : command_template(command_template),
                                         filename(filename),
                                         dir_seconds(dir_seconds),
                                         default_seconds(default_seconds){};
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