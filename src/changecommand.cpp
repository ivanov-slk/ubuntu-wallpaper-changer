#pragma once
#include <string>
#include "commandinterface.h"

using namespace std;

class ChangeCommand : public CommandInterface
{
private:
    string filename;
    string command_template;
    string command_line;

public:
    ChangeCommand() = default;
    ChangeCommand(string command_template, string filename) : command_template(command_template), filename(filename){};
    void execute() override
    {
        command_line = command_template + filename;
    };
    string get_command_line() { return command_line; };
};