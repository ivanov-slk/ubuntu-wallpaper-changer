#include <string>
#include "commandinterface.h"

using namespace std;

class SystemCommand : public CommandInterface
{
private:
    string filename;
    string command_template = "gsettings set org.gnome.desktop.background picture-uri ";

public:
    SystemCommand() = default;
    SystemCommand(string filename) : filename(filename){};
    string execute() override
    {
        string command_line;
        command_line = command_template + "\"file://" + filename + "\"";
        return command_line.c_str();
    };
};