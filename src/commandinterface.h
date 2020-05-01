#include <string>

class CommandInterface
{
public:
    virtual ~CommandInterface(){};
    virtual std::string execute() = 0;
};