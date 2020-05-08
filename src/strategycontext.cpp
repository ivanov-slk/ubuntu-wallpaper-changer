#include "strategyinterface.h"

/**
 * Implemented as in https://refactoring.guru/design-patterns/strategy/cpp/example
 * I'd like to know whether this can be implemented without pointers.
 */
class StrategyContext
{
private:
    StrategyInterface *strategy;

public:
    explicit StrategyContext(StrategyInterface *strategy = nullptr) : strategy(strategy) {}
    ~StrategyContext() { delete this->strategy; }
    void set_strategy(StrategyInterface *new_strategy)
    {
        delete this->strategy;
        strategy = new_strategy;
    }

    std::vector<std::filesystem::path> execute_strategy(Directory dir) const
    {
        std::vector<std::filesystem::path> result = this->strategy->execute(dir);
        return result;
    }
};