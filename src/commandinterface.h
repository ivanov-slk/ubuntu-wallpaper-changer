#include <string>

class CommandInterface
{
public:
    virtual ~CommandInterface() = default;
    virtual void execute() = 0;
};