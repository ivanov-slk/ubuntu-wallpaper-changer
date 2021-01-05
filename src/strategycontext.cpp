#pragma once
#include "strategyinterface.h"

/**
 * I'd like to know whether this can be implemented without pointers.
 */
class StrategyContext {
 private:
  std::unique_ptr<StrategyInterface> strategy;

 public:
  // StrategyContext(const StrategyInterface &strategy) : strategy(strategy) {}
  // ~StrategyContext() { delete this->strategy; }
  void set_strategy(std::unique_ptr<StrategyInterface> new_strategy) {
    // delete this->strategy;
    strategy = std::move(new_strategy);
  }

  std::vector<std::filesystem::path> execute_strategy(Directory dir) const {
    std::vector<std::filesystem::path> result = strategy->execute(dir);
    return result;
  }
};