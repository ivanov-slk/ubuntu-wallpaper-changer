#include <string>

#include "directory.cpp"
#include "strategycontext.cpp"

/**
 * This class has a directory path field. It is responsible
 * for initializing a root directory, the file selection strategy
 * and the execution of the latter. 
 */
class DirHandler
{
private:
    std::string root_path;
    Directory root_dir;
    StrategyContext context;

public:
    DirHandler(const std::string &root_path) : root_path(root_path)
    {
        root_dir = Directory{root_path};
    }
};