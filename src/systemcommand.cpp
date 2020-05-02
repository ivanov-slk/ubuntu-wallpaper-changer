#include <string>
#include "commandinterface.h"

using namespace std;

class SystemCommand : public CommandInterface
{
private:
    string filename;
    string command_template;
    string command_line;

public:
    SystemCommand() = default;
    SystemCommand(string filename, string command_template) : filename(filename), command_template(command_template){};
    void execute() override
    {
        command_line = command_template + "\"file://" + filename + "\"";
    };
    string get_command_line() { return command_line; };
};