#pragma once
#include "commandinterface.h"

class ChangeCommand : public CommandInterface
{
private:
    std::string filename;
    std::string command_template;
    std::string command_line;
    ChangeParameters change_params;

public:
    ChangeCommand() = default;
    ChangeCommand(const std::string &command_template, const std::string &filename) : command_template(command_template), filename(filename){};
    void execute() override
    {
        command_line = command_template + "\"file://" + filename + "\"";
        change_params.command_line = command_line;
    };
    ChangeParameters get_change() { return change_params; };
};