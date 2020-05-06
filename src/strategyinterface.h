#include <filesystem>
#include <vector>

class StrategyInterface
{
public:
    virtual ~StrategyInterface() = default;
    virtual std::vector<std::filesystem::path> execute(Directory root_dir) = 0;
};