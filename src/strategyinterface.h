#pragma once
#include <filesystem>
#include <vector>

#include "directory.cpp"

class StrategyInterface
{

public:
    virtual ~StrategyInterface() = default;
    virtual std::vector<std::filesystem::path> execute(Directory root_dir)  = 0;
};