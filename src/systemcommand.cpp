#include <string>
#include "commandinterface.h"

using namespace std;

class SystemCommand : public CommandInterface
{
private:
    string filename;
    string command_template = "gsettings set org.gnome.desktop.background picture-uri ";
    string command_line;

public:
    SystemCommand() = default;
    SystemCommand(string filename) : filename(filename){};
    void execute() override
    {
        command_line = command_template + "\"file://" + filename + "\"";
    };
    string get_command_line() { return command_line; };
};