#include <string>
#include "commandinterface.h"

using namespace std;

class SystemCommand : public CommandInterface
// Currently this class is quite literal and does not generalize to
// the concept of "system command". Consider refactoring it.
{
private:
    string filename;
    string command_template;
    string command_line;

public:
    SystemCommand() = default;
    SystemCommand(string command_template, string filename) : command_template(command_template), filename(filename){};
    void execute() override
    {
        command_line = command_template + filename;
    };
    string get_command_line() { return command_line; };
};