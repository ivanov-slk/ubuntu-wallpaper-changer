#pragma once
#include <filesystem>
#include <vector>

#include "directory.cpp"

class StrategyInterface {
 public:
  virtual ~StrategyInterface() = default;

  /**
   * @brief Executes the strategy in a given root directory.
   *
   * @param Directory root_dir - the root directory, where the strategy will be
   * executed.
   *
   * @return std::vector<std::filesystem::path> - a vector of the paths of files
   * somewhere
   * ("where" depends on the strategy implementation) in the directory tree
   * rooted at `root_dir`.
   */
  virtual std::vector<std::filesystem::path> execute(Directory root_dir) = 0;
};