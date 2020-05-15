#include <string>

class CommandInterface
{
public:
    virtual ~CommandInterface() = default;
    virtual void execute() = 0;
};

struct ChangeParameters
{
    std::string command_line;
    int change_seconds;
};